#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"


//  ОПИСАНИЕ:
//    Пример подсчета внешних импульсов на входе ETR.
//    Таймер1 генерирует импульсы, которые подаются на вход ETR Таймера2.
//    В прерываниях таймеров по периоду: 
//      - Таймер1 переключается светодиод1, 
//      - Таймер2 переключается светодиод2.
//  В коде можно поменять настройки фильтров, частоты сэмплирования и прочего 
//  для изучения их влияния на периоды мигания светодиодов.
//
//  В 1986ВК214 без подключения налюдается беспорядочное мигание светодиода (из-за наводок или утечек).
//  При подключении TIM1_CH1 к TIM2_ETR мигания ожидаемо упорядочиваются.
//  В 1986ВК234 вывод TIM2_ETR подключен в светодиоду LED3, поэтому на нем удобно наблюдать период сигнала ETR. LED2 мигает с периодом LED2_PERIOD.

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);


TestInterface TI_PWM_CountETR = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Empty,
  .funcExec       = Test_Empty,
  .funcMainLoop   = Test_Empty,  
  .funcHandlerTim1 = Test_HandleTim1IRQ,
  .funcHandlerTim2 = Test_HandleTim2IRQ,
  .funcHandlerTim3 = Test_Empty,
  .funcHandlerTim4 = Test_Empty,
};

#ifdef USE_MDR1986VK234
  #define TIM_PWM             MDR_TIMER1ex
  #define TIM_PWM_CH          MDR_TIMER1_CH3
  #define TIM_PWM_PIN_CH      _pinTim1_CH3
  #define TIM_PWM_START_MSK   TIM1_StartMsk

  #define TIM_ETR             MDR_TIMER2ex
  #define TIM_ETR_PIN         _pinTim2_ETR
  #define TIM_ETR_START_MSK   TIM2_StartMsk

#else
  #define TIM_PWM             MDR_TIMER1ex
  #define TIM_PWM_CH          MDR_TIMER1_CH1
  #define TIM_PWM_PIN_CH      _pinTim1_CH1
  #define TIM_PWM_START_MSK   TIM1_StartMsk

  #define TIM_ETR             MDR_TIMER2ex
  #define TIM_ETR_PIN         _pinTim2_ETR
  #define TIM_ETR_START_MSK   TIM2_StartMsk
#endif


#define LED2_PERIOD   4

static const MDR_Timer_cfgBRKETR  cfgBRKETR = {
  .Bits.BRK_INV = MDR_Off, 
  .Bits.ETR_INV = MDR_Off, 
  .Bits.ETR_PSC = MDR_TIM_BRKETR_ETR_div1,
  .Bits.ETR_Filter = MDR_TIM_FLTR_TIM_CLK
};

static const MDR_Timer_CfgCountETR  cfgETR = {  
  .cfgPeriod.clockBRG   = TIM_BRG_LED,
  .cfgPeriod.period     = LED2_PERIOD,
  .cfgPeriod.startValue = 0,
  .cfgPeriod.periodUpdateImmediately = MDR_Off,
  
  .cfgIRQ.SelectIRQ   = TIM_FL_CNT_ARR,
  .cfgIRQ.priorityIRQ = 0,
  .cfgIRQ.activateNVIC_IRQ = true,
   
  .selFrontETR = TIM_FrontRise,  
  .countDir    = TIM_CountUp,
  .clockDTS    = TIM_FDTS_TimClk_div1
};

static void Test_Init(void)
{     
  //  To LCD
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Count ETR", 3);
  
#elif defined (LCD_CONFLICT)
  //  LCD conflicts with Timers channel
  //  Show Test index and LCD Off
  MDRB_LCD_Print("10");  
  MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
  MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
  
  MDR_LCD_DeInit();
#else
  MDRB_LCD_Print("10");
#endif
  
  MDRB_LED_Init(MDRB_LED_1 | MDRB_LED_2);
  MDRB_LED_Set (MDRB_LED_1 | MDRB_LED_2, 0);
  
  //  Timer1_CH1 - Pulse output for ETR, show period with LED1
  MDR_Timer_InitPeriod(TIM_PWM, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
  MDR_TimerPulse_InitPulse(TIM_PWM_CH, TIM_PERIOD_LED, 50);
  MDR_TimerCh_InitPinGPIO(&TIM_PWM_PIN_CH,  MDR_PIN_FAST);
     
  //  Timer2 Count ETR and, show period with LED2
  MDR_Timer_InitCountETR(TIM_ETR, &cfgETR);
  MDR_Timer_InitBRKETR(TIM_ETR, cfgBRKETR);
  MDR_TimerCh_InitPinGPIO(&TIM_ETR_PIN, MDR_PIN_FAST);
    
  // Sync Start
  MDR_Timer_StartSync(TIM_PWM_START_MSK | TIM_ETR_START_MSK);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&TIM_PWM_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&TIM_ETR_PIN);

  MDR_Timer_StopSync(TIM_PWM_START_MSK | TIM_ETR_START_MSK);
  MDR_Timer_DeInit(TIM_PWM);
  MDR_Timer_DeInit(TIM_ETR);
  
  LED_Uninitialize();  
}

static void Test_HandleTim1IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER1, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_1);  
}

static void Test_HandleTim2IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_2);
}

static void Test_Empty(void)
{
}
