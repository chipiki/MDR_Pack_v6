#include <MDRB_UART_Debug.h>

#include <stdio.h>

//======================  Выбор пинов ======================
#if defined(USE_BOARD_VE1) || defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE1.h  / MDRB_1986VE3.h
  #if UART_DEBUG_IND == 1
    const MDR_UART_TypeEx * UART_DBG = MDR_UART1ex;
  
    static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PC3_Port, MDRB_UART1_TX_PC3_Ind, MDRB_UART1_TX_PC3_Func};
    static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PC4_Port, MDRB_UART1_RX_PC4_Ind, MDRB_UART1_RX_PC4_Func};    
                                     
  #elif UART_DEBUG_IND == 2
    const MDR_UART_TypeEx * UART_DBG = MDR_UART2ex;
                                       
    static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART2_TX_PD13_Port, MDRB_UART2_TX_PD13_Ind, MDRB_UART2_TX_PD13_Func};
    static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART2_RX_PD14_Port, MDRB_UART2_RX_PD14_Ind, MDRB_UART2_RX_PD14_Func};

  #endif

    
#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  //  см. MDRB_1986VE91.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART2ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART2_TX_PF1_Port, MDRB_UART2_TX_PF1_Ind, MDRB_UART2_TX_PF1_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART2_RX_PF0_Port, MDRB_UART2_RX_PF0_Ind, MDRB_UART2_RX_PF0_Func};
  
#elif defined(USE_BOARD_VE92)
  //  см. MDRB_1986VE92.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART2ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART2_TX_PF1_Port, MDRB_UART2_TX_PF1_Ind, MDRB_UART2_TX_PF1_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART2_RX_PF0_Port, MDRB_UART2_RX_PF0_Ind, MDRB_UART2_RX_PF0_Func};
  
#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART1ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PB5_Port, MDRB_UART1_TX_PB5_Ind, MDRB_UART1_TX_PB5_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PB6_Port, MDRB_UART1_RX_PB6_Ind, MDRB_UART1_RX_PB6_Func};
  
#elif defined(USE_BOARD_VC1)
  //  см. MDRB_1901VС1.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART3ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART3_TX_PF1_Port, MDRB_UART3_TX_PF1_Ind, MDRB_UART3_TX_PF1_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART3_RX_PF0_Port, MDRB_UART3_RX_PF0_Ind, MDRB_UART3_RX_PF0_Func};                                      

#elif defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  //  см. MDRB_1986VE4.h / MDRB_1986VK214.h / MDRB_1986VK234.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART1ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PB0_Port, MDRB_UART1_TX_PB0_Ind, MDRB_UART1_TX_PB0_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PB1_Port, MDRB_UART1_RX_PB1_Ind, MDRB_UART1_RX_PB1_Func};    

#elif defined(USE_BOARD_VE8)
  //  см. MDRB_1986VE8.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART1ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PE15_Port, MDRB_UART1_TX_PE15_Ind, MDRB_UART1_TX_PE15_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PE16_Port, MDRB_UART1_RX_PE16_Ind, MDRB_UART1_RX_PE16_Func};
    
#elif defined(USE_BOARD_VK014)
  //  см. MDRB_1986VE8.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART1ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PE15_Port, MDRB_UART1_TX_PE15_Ind, MDRB_UART1_TX_PE15_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PE16_Port, MDRB_UART1_RX_PE16_Ind, MDRB_UART1_RX_PE16_Func};  
  
#elif defined(USE_BOARD_ESila)
  //  см. MDRB_ESila.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART1ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PB1_Port, MDRB_UART1_TX_PB1_Ind, MDRB_UART1_TX_PB1_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PB0_Port, MDRB_UART1_RX_PB0_Ind, MDRB_UART1_RX_PB0_Func};  
    
#endif

  
#define _CFG_UART_DBG_DEF_EX(opt, irq)  { .cfgBase.WordLength    = MDR_UART_WordLen8,  \
                                          .cfgBase.Parity        = UART_Parity_Off,    \
                                          .cfgBase.useFIFO       = MDR_On,             \
                                          .cfgBase.Options.Value = opt,                \
                                          .pCfgIRQ     = irq,                          \
                                          .pCfgDMA     = NULL,                         \
                                          .pCfgIrDA    = NULL,                         \
                                          . pCfgModem  = NULL                          \
                                          }


#define _CFG_UART_DBG_DEF       _CFG_UART_DBG_DEF_EX(0, NULL)  
  
  
// Простейшая настройка UART для выводы сообщений наружу, RX выключен  
void MDR_UART_DBG_Init(bool isCPUbyPLL)
{
  MDR_UART_DBG_InitEx(UART_DEBUG_BAUD_DEF, isCPUbyPLL, false);
}

// Простейшая настройка UART_DBG с опциональным разрешением RX
void MDR_UART_DBG_InitEx(uint32_t baudRate, bool isCPUbyPLL, bool RX_Enable)
{
  MDR_UART_Cfg cfgUART = _CFG_UART_DBG_DEF;
  if (!RX_Enable)
    cfgUART.cfgBase.Options.Value = MDR_UART_OPT_DisRX;
  
  MDR_UART_DBG_InitCfg(&cfgUART, baudRate, isCPUbyPLL);
}  

//  Настройка UART_DBG с разрешением прерываний
void MDR_UART_DBG_InitIrq(uint32_t baudRate, bool isCPUbyPLL, uint32_t selEvents, MDR_UART_EventFIFO levelFIFO)
{ 
  //  Конфигурация
  MDR_UART_CfgIRQ cfgIRQ = { .SelEventIRQ.Value = selEvents,
                             .Rx_FIFO_Event = levelFIFO,
                             .Tx_FIFO_Event = levelFIFO
                           };
  MDR_UART_Cfg cfgUART = _CFG_UART_DBG_DEF_EX(0, &cfgIRQ);

  //  Инициалиазация
  MDR_UART_DBG_InitCfg(&cfgUART, baudRate, isCPUbyPLL);
	//	Разрешение прерываний с приоритетом 0
  MDR_UARTex_NVIC_EnableIRQ(UART_DBG, 0);                           
}  

//  Настройка UART_DBG с заданием конфигурации
void MDR_UART_DBG_InitCfg(MDR_UART_Cfg *cfgUART, uint32_t baudRate, bool isCPUbyPLL)
{
  uint32_t UART_ClockHz;
  MDR_UART_cfgBaud cfgBaud;
  MDR_UART_CfgPinsGPIO pinsGPIO;

//--------    UART_Clock On -------------
#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP  
  if (isCPUbyPLL)
    MDR_UARTex_SetUartClock(UART_DBG, MDR_Div128P_div1, MDR_PER_PLLCPUo);
  else
    MDR_UARTex_SetUartClock(UART_DBG, MDR_Div128P_div1, MDR_PER_CPU_C1);
  
#elif defined (MDR_TIM_CLOCK_FROM_PER_CLOCK)
  UNUSED(isCPUbyPLL);  
  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
  MDR_UARTex_SetUartClock(UART_DBG, MDR_Div128P_div1);  
  
#elif defined (MDR_CLK_LIKE_VE8)  
  UNUSED(isCPUbyPLL);  
  MDR_UARTex_SetUartClock(UART_DBG, MDR_Div128P_div1, MDR_RST_ASYNC_IN_MAX_CLK);
  
#else
  UNUSED(isCPUbyPLL);
  MDR_UARTex_SetUartClock(UART_DBG, MDR_Div128P_div1);
#endif
//---------------------------------------

  //  Baud Rate
  UART_ClockHz = MDR_UARTex_GetUartClockHz(UART_DBG, true);  
  MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
  
  //  Uart Init
  MDR_UARTex_InitByBaud(UART_DBG, cfgUART, &cfgBaud);
  
  //  Init Pins
  pinsGPIO.pPinTX = &_pinTX_UART;
  if ((cfgUART->cfgBase.Options.Value & MDR_UART_OPT_DisRX) == 0)  
    pinsGPIO.pPinRX = &_pinRX_UART;
  else
    pinsGPIO.pPinRX = NULL;
  MDR_UART_InitPinsGPIO(&pinsGPIO, MDR_PIN_FAST);
  
#if UART_DEBUG_SHOW_WELLCOME    
  double baudError = MDR_UART_CalcBaudError(&cfgBaud, baudRate, UART_ClockHz);
  //  Wellcome
  printf("Wellcome to UART DebugOut!\n");
  printf("BaudRate: %d\n",  baudRate);
  printf("BaudError: %f\n", baudError);
#endif
}


void MDR_UART_DBG_Finit(void)
{
  MDR_UARTex_DeInit(UART_DBG);
}

void MDR_UART_DBG_ChangeRate(uint32_t baudRate)
{
  uint32_t UART_ClockHz;
  MDR_UART_cfgBaud cfgBaud;

  //  Baud Rate
  UART_ClockHz = MDR_UARTex_GetUartClockHz(UART_DBG, true);  
  MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
  
#if UART_DEBUG_SHOW_WELLCOME
  double baudError = MDR_UART_CalcBaudError(&cfgBaud, baudRate, UART_ClockHz);
  
  //  Message 
  printf("BaudRate Changed: %d\n",  baudRate);
  printf("BaudError: %f\n", baudError);  
#endif
  
  MDR_UART_ChangeRateEx(UART_DBG->UARTx, &cfgBaud);    
}

bool MDR_UART_DBG_TrySend(char data)
{
  return MDR_UART_TrySend(UART_DBG->UARTx, data);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6010050)
struct __FILE
{
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};
#endif

/* FILE is typedef’d in stdio.h. */
FILE __stdout;

int fputc(int ch, FILE *f)
{ 
  UNUSED(f);
  
  while(!MDR_UART_CanSend(UART_DBG->UARTx));
  MDR_UART_SendData(UART_DBG->UARTx, (uint8_t)ch);
  
  return ch;
}

int ferror(FILE *f)
{
  UNUSED(f);
  
  /* Your implementation of ferror(). */
  return 0;
}
