#ifndef MDR_CONFIG_H
#define MDR_CONFIG_H

#if   defined (USE_MDR1986VE1)
  #include <MDR_1986BE1.h>
#elif defined (USE_MDR1986VE3)
  #include <MDR_1986BE3.h>
#elif defined (USE_MDR1986VE4)
  #include <MDR_1986BE4.h>
#elif defined (USE_MDR1986VE9x)
  #include <MDR_1986BE9x.h>
#elif defined (USE_MDR1901VC1)
  #include <MDR_1901VC1.h>
#elif defined (USE_MDR1986VK214)
  #include <MDR_1986BK214.h>
#elif defined (USE_MDR1986VK234)
  #include <MDR_1986BK234.h>  
#endif

//  Internal Generators
#define HSI_FREQ_HZ     (8000000UL)
#define HSI_FREQ_TRIM    MDR_BKP_HSI_TRIM_8M0Hz
#define HSI_TIMEOUT      0x0600UL   //#define HSI_TIMEOUT_MS  1

#define LSI_FREQ_HZ      (40000UL)
#define LSI_FREQ_TRIM    MDR_BKP_LSI_TRIM_40KHz
#define LSI_TIMEOUT      0x0600UL  //#define LSI_TIMEOUT_MS  80

//  External Generators
#define HSE_FREQ_HZ     (8000000UL)
#define HSE_TIMEOUT     0x8000UL

#define LSE_FREQ_HZ     (32768UL)
#define LSE_TIMEOUT     0x0600UL


//  External Generator for Ethernet PHY
#define HSE2_FREQ_HZ    (25000000UL)

#define HSE2_TIMEOUT_CYCLES  2400

//  PLL Ready Timeout
#define PLL_TIMEOUT_MS  100


#endif  //  MDR_CONFIG_H