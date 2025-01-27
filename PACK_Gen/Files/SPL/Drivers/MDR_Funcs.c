#include <MDR_Funcs.h>

//===================    Функция ожидания с таймаутом  ===================
bool WaitCondition(uint32_t timeoutCycles, pBoolFunc_void checkFunc)
{
  while (timeoutCycles != 0)
  {
    if (checkFunc())
      return true;
    timeoutCycles--;
  }
  return checkFunc();
}

void MDR_WaitFlagSet(uint32_t addr, uint32_t flag)
{
  while ((REG32(addr) & flag) != flag);
}

void MDR_WaitFlagClear(uint32_t addr, uint32_t flag)
{
  while ((REG32(addr) & flag) == flag);
}


//=========================    Задержка =======================
void MDR_Delay(uint32_t Ticks)
{
  volatile uint32_t i = Ticks;
  if (i)
    while (--i);
  
  //for (; i > 0; i--);  // - Больше циклов, сильнее зависит от оптимизации
}


//=====================    Псевдо-случайное значение ===================
uint32_t MDR_ToPseudoRand(uint32_t value)
{ 
  uint32_t hash = 0;
  uint32_t i = 0;
  uint8_t* key = (uint8_t *)&value;

  for (i = 0; i < 4; i++)
  {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  for (i = 0; i < 256; i++)
  {
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}

//============    Log for debug ============
#ifdef DEBUG_LOG_ENA
  #define LOG_BUFF_Len  200
  // Объект лога. Можно завести несколько, чтобы логгировать в разные массивы.  
  static uint32_t LogData1[LOG_BUFF_Len];

  MDR_LogRec MDR_LogRec1 =
  {
    LogData1,
    LOG_BUFF_Len,
    0,
    0  
  };

  void MDR_LOG_Clear(MDR_LogRec *pLogRec)
  {
    uint16_t i;
    
    for (i = 0; i < pLogRec->BuffLen; ++i)
      pLogRec->pBuff[i] = 0;
    pLogRec->IndWR = 0;
    pLogRec->DataCnt = 0;
  }

  void MDR_LOG_Add(MDR_LogRec *pLogRec, uint32_t value)
  {
    pLogRec->pBuff[pLogRec->IndWR++] = value;
    pLogRec->DataCnt++;
    if (pLogRec->IndWR >= pLogRec->BuffLen)
      pLogRec->IndWR = 0;
  }
#endif
