#include "timerService.h"
#include <time.h>
#include "base/BitBanding.h"
#include "base/gpio.h"
#include "base/clocker.h"
#include "base/ISR.h"

#ifdef HEAP_SIZE
    extern uint8_t heap[HEAP_SIZE];
#endif

#define LED_ON(a) GPIOB->BSRRH = 1 << (5+a)
#define LED_OFF(a) GPIOB->BSRRL = 1<<(5+a)
#define LED_TG(a) GPIOB->ODR ^= 1<<(5+a)


#define LED1 0
#define LED2 1

/******************************************************************
    Приватные структуры и прототипы
******************************************************************/

TS::timeT TStime;


static struct
{
    TS::Task_t tasks[20]; // Сортированные задачи
    uint8_t tasksNum;
    void (*secondTick)(void); // Функция, вызываемая каждую секунду
    void (*minuteTick)(void); // Функция, вызываемая каждую секунду
} timeSrvs;


/******************************************************************
    Функция инициализации таймерной службы
******************************************************************/
void TS::init(void (*secondTick)(void),void (*minuteTick)(void))
{
  //Инициализация переменных
    timeSrvs.tasksNum = 0;
    timeSrvs.secondTick = secondTick;
    timeSrvs.minuteTick = minuteTick;

    TStime.sec = 0;
    TStime.minute = 0;
    TStime.hr = 0;

  //Инициализация таймера.
    RCCEnable(RCC->APB1ENR,RCC_APB1ENR_TIM2EN);
    TS::timer->CR1 = TIM_CR1_CEN;
    TS::timer->PSC = (72000/2) - 1;//32000 делитель
    //TS::timer->PSC = (72000/12) - 1;//32000 делитель
    TS::timer->ARR = 0xFFFF;


  //Отладка таймера (PB1-ch4)
    DBGMCU->CR |= DBGMCU_CR_DBG_TIM2_STOP;
   /* IOSetup<IOB,1,IO_outAFPP2MHz>();
    TS::timer->CCMR2 = TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_0 ;
    TS::timer->CCER = TIM_CCER_CC4E ;
    TS::timer->CCR4 = 0x1;*/

  //Установка секундного прерывания
    TS::timer->CCR1=4000;
    makeBBPeriph(&(TS::timer->DIER),TIM_DIER_CC1IE) = 1;//Enable interrupt
    TS::timer->SR = 0;
    NVIC_EnableIRQ(timIRQn);
  //Запуск таймера синхронно с тиком секундного таймера RTC
/*    uint16_t old_tr = RTC->TR;
    while (RTC->TR == old_tr);
    TIM_Cmd(TIM2, ENABLE);
    RTC_GetTime(RTC_Format_BIN, &timeSrvs.currentTime);
    TIM_SetCompare1(TIM2, 1000);
    TIM_SetCompare2(TIM2, 60000 - 1000*timeSrvs.currentTime.RTC_Seconds);
    TIM_ITConfig(TIM2,TIM_IT_CC1|TIM_IT_CC2,ENABLE);

    RTC_DateTypeDef currentDate;
    RTC_GetDate(RTC_Format_BIN, &currentDate);

    struct tm tm;
    tm.tm_sec   = timeSrvs.currentTime.RTC_Seconds;
    tm.tm_min   = timeSrvs.currentTime.RTC_Minutes;
    tm.tm_hour  = timeSrvs.currentTime.RTC_Hours;
    tm.tm_mday  = currentDate.RTC_Date;
    tm.tm_mon   = currentDate.RTC_Month -1;
    tm.tm_year  = 100 + currentDate.RTC_Year;
    tm.tm_wday  = currentDate.RTC_WeekDay;

    timeSrvs.timestamp = mktime(&tm);*/
}

/****************************************************************
    Добавление задачи
*****************************************************************/
void TS::addTask(uint16_t mtime, void (*function)(uint32_t),uint32_t argument)
{
  // Отключаем срабатывание прерывания
    __disable_irq();

    if(timeSrvs.tasksNum > 0)
    {
        //считаем время до срабатывания текущей задачи
        timeSrvs.tasks[timeSrvs.tasksNum-1].mtime = TIM2->CCR3 - TIM2->CNT;

        uint16_t mtime0 = 0;
        uint8_t taskNum = timeSrvs.tasksNum;
        while (taskNum >0)
        {
            if(mtime0 + timeSrvs.tasks[taskNum-1].mtime > mtime)
            {
                timeSrvs.tasks[taskNum-1].mtime -= mtime - mtime0;
                break;
            }
            mtime0 += timeSrvs.tasks[taskNum-1].mtime;
            taskNum--;
        }
        mtime -= mtime0;
        timeSrvs.tasks[timeSrvs.tasksNum].function = function;
        timeSrvs.tasks[timeSrvs.tasksNum].mtime = mtime;
        timeSrvs.tasks[timeSrvs.tasksNum].argument = argument;

        while(taskNum<timeSrvs.tasksNum)
        {
            TS::Task_t unsortedTask = timeSrvs.tasks[taskNum];
            timeSrvs.tasks[taskNum] = timeSrvs.tasks[timeSrvs.tasksNum];
            timeSrvs.tasks[timeSrvs.tasksNum] = unsortedTask;
            taskNum++;
        }
        TIM2->CCR3 = TIM2->CNT + timeSrvs.tasks[timeSrvs.tasksNum].mtime;
        timeSrvs.tasksNum++;
    }
    else
    {
        timeSrvs.tasks[timeSrvs.tasksNum].function = function;
        timeSrvs.tasks[timeSrvs.tasksNum].mtime = mtime;
        timeSrvs.tasks[timeSrvs.tasksNum].argument = argument;
        timeSrvs.tasksNum++;
        TIM2->CCR3 = mtime + TIM2->CNT;
        makeBBPeriph(&(TS::timer->DIER),TIM_DIER_CC3IE) = 1;//Enable interrupt
    }
    __enable_irq();
}
/****************************************************************
    Рабочее прерывание
*****************************************************************/

/*

    void (*secondTick)(void); // Функция, вызываемая каждую секунду
    void (*minuteTick)(void); // Функция, вызываемая каждую секунду*/
static inline void minuteEvent()
{
  // Работаем с внутренними часами
    uint8_t tmp = TStime.minute+1;
    if(tmp >= 60)
    {
        tmp -= 60;
        TStime.hr++;
        if (TStime.hr >23)
            TStime.hr=0;
    }
    TStime.minute = tmp;
  // Отрабатываем минутное задание
    if(timeSrvs.minuteTick)
        timeSrvs.minuteTick();
}

void ISR::TIM2_IRQ(void)
{
  // Секундное прерывание
    if (TS::timer->SR & TIM_SR_CC1IF)
    {

        //TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
        TS::timer->SR = ~TIM_SR_CC1IF;
        TStime.timestamp++;
        if(TStime.sec == 59)
        {
            TStime.sec =0;
            if(timeSrvs.secondTick)
                timeSrvs.secondTick();
            minuteEvent();
        }
        else
        {
            TStime.sec++;
            if(timeSrvs.secondTick)
                timeSrvs.secondTick();
        }
        TS::timer->CCR1+=1000;
        return;
    }
  // Прерывание таймерной службы
    if (TS::timer->SR & TIM_SR_CC3IF)
    {
        TS::timer->SR  = ~TIM_SR_CC3IF;
        TS::Task_t currentTask = timeSrvs.tasks[timeSrvs.tasksNum -1];
        currentTask.function(currentTask.argument);
        if(timeSrvs.tasksNum > 1)
        {
            timeSrvs.tasksNum--;
            TIM2->CCR3 += timeSrvs.tasks[timeSrvs.tasksNum-1].mtime;
        }
        else
        {
            timeSrvs.tasksNum = 0;
            makeBBPeriph(&(TS::timer->DIER),TIM_DIER_CC3IE) = 0;//Disable interrupt
        }
    }
}
/******************************************************************
    Функция установки текущего времени
******************************************************************/
int32_t timeSet(uint32_t timestamp)
{
    /*int32_t ret = timeSrvs.timestamp - timestamp;
    timeSrvs.timestamp = timestamp;
    struct tm tm;
    tm = *gmtime((time_t*) &timestamp);
    timeSrvs.currentTime.RTC_Seconds = tm.tm_sec;
    timeSrvs.currentTime.RTC_Minutes = tm.tm_min;
    timeSrvs.currentTime.RTC_Hours   = tm.tm_hour;
    RTC_DateTypeDef currentDate;
    currentDate.RTC_Date             = tm.tm_mday;
    currentDate.RTC_Month            = tm.tm_mon + 1;
    currentDate.RTC_Year             = tm.tm_year -100;
    currentDate.RTC_WeekDay          = tm.tm_wday;
    TIM2->CCR1 = TIM2->CNT + 1000; // secount tick
    TIM2->CCR2 = TIM2->CNT + ((60 - tm.tm_sec) * 1000);// Minute tick
    if(timeSrvs.minuteTick)
        timeSrvs.minuteTick();
    if(timeSrvs.secondTick)
        timeSrvs.secondTick();
    RTC_SetTime(RTC_Format_BIN, &timeSrvs.currentTime);
    RTC_SetDate(RTC_Format_BIN, &currentDate);
    return ret;*/
    return 0;
}
