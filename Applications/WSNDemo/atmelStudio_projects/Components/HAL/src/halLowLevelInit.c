/**************************************************************************//**
\file  halLowLevelInit.c

\brief
   Implementation of the basic initialization module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    07/04/14 karthik.p_u - Created
*******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <atsamr21.h>
#include <core_cm0plus.h>
#include <sysTypes.h>
#include <halClkCtrl.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define DFLL_COARSE_STEP_SIZE        (0x1f/4)
#define DFLL_FINE_STEP_SIZE          (0xff/4)
// XOSC32K Output Freq if en32k in XOSC32K Reg is enabled
#define XOSC32K_CLK                  (32768ul)
// The Fixed Output Freq of DFLL
#define DFLL_OUTPUT_FREQ             48000000ul
// The multiplication factor needed to get 48MHz out of DFLL
#define DFLL_MUL_48MHz               (DFLL_OUTPUT_FREQ/XOSC32K_CLK)

/******************************************************************************
                   Prototypes section
******************************************************************************/
#if defined(HAL_4MHz) || defined(HAL_8MHz)
/**************************************************************************//**
\brief Run CPU from internal 8Mhz RC Oscillator 

\param[in] div - The division factor to be applied before giving the RC clock \
                 to CPU
******************************************************************************/
static void halConfigCpuIntRC(uint8_t div);

#elif defined(HAL_16MHz) || defined(HAL_24MHz) || defined(HAL_48MHz)
/**************************************************************************//**
\brief Run CPU from XOSC32K Oscillator through DFLL to run at \
       different frequencies. 

\param[in] div - The division factor to be applied before giving the DFLL    \
                 clock to CPU.
\param[in] mul - The multiplication factor to be applied on DFLL to multiply \
                 the RC clock.
******************************************************************************/
static void halConfigCpuDFLL(uint16_t div, uint16_t mul);

#endif

/**************************************************************************//**
\brief Initialize the Peripherals with Internal RC oscillator.

\param[in] div - The division factor to be applied before giving the Internal \
                 RC clock to Peripherals.
******************************************************************************/
static void halConfigPeriIntRC(uint8_t div);

/******************************************************************************
                              Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Run device from 8MHz RC clock
******************************************************************************/
void halSwitchToRcClock(void)
{
  // NVM wait cycles
  // These Wait cycles are need without which CPU will stop
#if defined(HAL_16MHz) || defined(HAL_24MHz)
  // The wait cycles are set to 2 as per datasheet for voltages from 1V8 to 3V6
  NVMCTRL_CTRLB |= NVMCTRL_CTRLB_RWS(2);
#elif defined(HAL_48MHz)
  // The wait cycles are set to 3 as per datasheet for voltages from 1V8 to 3V6
  NVMCTRL_CTRLB |= NVMCTRL_CTRLB_RWS(3);
#endif /* NVM wait cycles */

  // setting the pre-scalar
  SYSCTRL_OSC8M_s.presc = 0x0;
  // Enabling the oscillator
  SYSCTRL_OSC8M_s.enable = 0x1;
  // Check if the oscillator is ready
  halCheckIntRcReady();

  // Setting the pre-scalar for generator 0
  GCLK_GENDIV = GCLK_GENDIV_ID(0) | GCLK_GENDIV_DIV(0);
  halGclkSync();

  // Routing the internal RC as source to generator 0
  GCLK_GENCTRL = GCLK_GENCTRL_ID(0) | GCLK_GENCTRL_SRC(6) | GCLK_GENCTRL_GENEN;
  halGclkSync();
}
/**************************************************************************//**
\brief Run device from active clock (intended at configuration)
******************************************************************************/
void halSwitchToActiveClock(void)
{

  // Configuring the peripheral frequency
  // The peripherals will always be running at Internal 8Mhz irrespective of CPU freq
  // Only Exception is For HAL_4MHz the Peripherals also run at 4Mhz
#if defined(HAL_4MHz)
  // The division factor 2 is in place as to make the Peripheral frequency same as CPU Frequency.
  halConfigPeriIntRC(2);
#elif defined(HAL_8MHz) || defined(HAL_16MHz) || defined(HAL_24MHz) || defined(HAL_48MHz)
  // No division factor is needed as it configured for 8MHz
  halConfigPeriIntRC(0);
#endif /* Configuring the Peripheral Freq */

  // Configuring the CPU Freq
  // Configuring Internal RC 8MHz as clock for CPU
#if defined(RC_INTERNAL)

#if defined(HAL_4MHz)
  // configuring CPU Freq for 4MHz 
  halConfigCpuIntRC(2);
#elif defined(HAL_8MHz)
  // configuring CPU Freq for 8MHz 
  halConfigCpuIntRC(0);
#elif defined(HAL_16MHz) || defined(HAL_24MHz) || defined(HAL_48MHz)
#error "Choose HAL_CLOCK_SOURCE as XOSC32K when choosing HAL_16MHz, HAL_24MHz and HAL_48MHz in HAL\Configuration" 
#endif

#endif /* Configuring Internal RC 8MHz as clock for CPU */

  // Configuring XOSC32K as clock for CPU by multiplying with DFLL
#if defined(XOSC32K)

  // Initializing external 32khz crystal used as a clock source for DFLL
  halXOSC32KInit();

#if defined(HAL_16MHz)
  // A division factor of 3 is needed as 48MHz/3 = 16MHz
  halConfigCpuDFLL(3, DFLL_MUL_48MHz);
#elif defined(HAL_24MHz)
  // A division factor of 2 is needed as 48MHz/2 = 24MHz
  halConfigCpuDFLL(2, DFLL_MUL_48MHz);
#elif defined(HAL_48MHz)
  // No division factor is needed as the output is 48MHz
  halConfigCpuDFLL(0, DFLL_MUL_48MHz);
#elif defined(HAL_4MHz) || defined(HAL_8MHz)
#error "Choose HAL_CLOCK_SOURCE as RC_INTERNAL when choosing HAL_4MHz and HAL_8MHz in HAL\Configuration"
#endif
 
#endif /* Configuring the CPU Freq */
}

#if defined(HAL_4MHz) || defined(HAL_8MHz)
/**************************************************************************//**
\brief Run CPU from internal 8Mhz RC Oscillator 

\param[in] div - The division factor to be applied before giving the RC clock \
                 to CPU
******************************************************************************/
static void halConfigCpuIntRC(uint8_t div)
{
  // Setting the prescalar for generator 0
  GCLK_GENDIV = GCLK_GENDIV_ID(0) | GCLK_GENDIV_DIV(div);
  halGclkSync();
 
  // Routing the internal RC as source to generator 0
  GCLK_GENCTRL = GCLK_GENCTRL_ID(0) | GCLK_GENCTRL_SRC(6) | GCLK_GENCTRL_GENEN;
  halGclkSync();
}

#elif defined(HAL_16MHz) || defined(HAL_24MHz) || defined(HAL_48MHz)
/**************************************************************************//**
\brief Run CPU from external XOSC32K Oscillator through DFLL to run at \
       different frequencies.

\param[in] div - The division factor to be applied before giving the DFLL    \
                 clock to CPU.
\param[in] mul - The multiplication factor to be applied on DFLL to multiply \
                 the RC clock.
******************************************************************************/
static void halConfigCpuDFLL(uint16_t div, uint16_t mul)
{
  // Setting the prescalar for generator 1
  GCLK_GENDIV = GCLK_GENDIV_ID(1) | GCLK_GENDIV_DIV(0);
  halGclkSync();

  // Routing the XOSC32K as source to generator 1
  GCLK_GENCTRL = GCLK_GENCTRL_ID(1) | GCLK_GENCTRL_SRC(5) | GCLK_GENCTRL_GENEN;
  halGclkSync();

  // Clearing Flags
  SYSCTRL_INTFLAG |= SYSCTRL_INTFLAG_DFLLRDY | SYSCTRL_INTFLAG_DFLLLCKF \
                     | SYSCTRL_INTFLAG_DFLLLCKC;

  // Setting the DFLL mode to closed loop and enabling it
  halDfllReady();
  SYSCTRL_DFLLCTRL = SYSCTRL_DFLLCTRL_ENABLE | SYSCTRL_DFLLCTRL_MODE;

  // Setting the FSTEP, CSTEP and multiplication factor for DFLL
  SYSCTRL_DFLLMUL = SYSCTRL_DFLLMUL_MUL(mul) | SYSCTRL_DFLLMUL_FSTEP(DFLL_FINE_STEP_SIZE) \
                    | SYSCTRL_DFLLMUL_CSTEP(DFLL_COARSE_STEP_SIZE);

  // Routing the clock for DFLL from generator 1
  GCLK_CLKCTRL = GCLK_CLKCTRL_ID(0) | GCLK_CLKCTRL_GEN(1) | GCLK_CLKCTRL_CLKEN;

  // Waiting for coarse lock to happen
  halCoarseLock();
  // Waiting for fine lock to happen
  halFineLock();

  // Setting the prescalar for generator 0
  GCLK_GENDIV = GCLK_GENDIV_ID(0) | GCLK_GENDIV_DIV(div);
  halGclkSync();

  // Routing the DFLL output as source to generator 0
  GCLK_GENCTRL = GCLK_GENCTRL_ID(0) | GCLK_GENCTRL_SRC(7) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_IDC;
  halGclkSync();
}

#endif
/**************************************************************************//**
\brief Initialize the 32KHz external Crystal oscillator.
******************************************************************************/
void halXOSC32KInit(void)
{
  /* Start up time for XOSC32K */
  SYSCTRL_XOSC32K_s.startup = SYSTEM_XOSC32K_STARTUP_65536;
  /* External XOSC32K Enable */
  SYSCTRL_XOSC32K_s.xtalen = 1;
 
  /* Auto amplitude control */
  SYSCTRL_XOSC32K_s.aampen = true;
  /* 1KHz output Enable/Disable */
  SYSCTRL_XOSC32K_s.en1k = false;
  /* 32KHz output Enable/Disable */
  SYSCTRL_XOSC32K_s.en32k = true;

  /* On demand feature of the clock module */
  SYSCTRL_XOSC32K_s.ondemand = false;
  /* Run in standby mode feature of the clock */
  SYSCTRL_XOSC32K_s.runstdby = true;
  /* Write once feature of the clock */
  SYSCTRL_XOSC32K_s.wrtlock  = false;
 
  /* Enable the XOSC32K crystal */
  SYSCTRL_XOSC32K_s.enable = true;
 
  /* Check the XOSC32K Clock source is ready to use */
  halCheckXOSC32KReady();
}

/**************************************************************************//**
\brief Initialize the Peripherals with Internal RC oscillator.

\param[in] div - The division factor to be applied before giving the Internal \
                 RC clock to Peripherals.
******************************************************************************/
static void halConfigPeriIntRC(uint8_t div)
{
  // Setting the pre-scalar for generator 3
  GCLK_GENDIV = GCLK_GENDIV_ID(3) | GCLK_GENDIV_DIV(div);
  halGclkSync();

#if defined(HAL_USE_WDT)  
  // Setting the pre-scalar for generator 4
  GCLK_GENDIV = GCLK_GENDIV_ID(4) | GCLK_GENDIV_DIV(32);
  halGclkSync();
#endif // defined(HAL_USE_WDT)

  // Routing the internal RC as source to generator 3
  GCLK_GENCTRL = GCLK_GENCTRL_ID(3) | GCLK_GENCTRL_SRC(6) | GCLK_GENCTRL_GENEN;
  halGclkSync();

#if defined(HAL_USE_WDT)
  // Routing the OSCULP32K as source to generator 4 as this is routed for WDT
  GCLK_GENCTRL = GCLK_GENCTRL_ID(4) | GCLK_GENCTRL_SRC(3)  \
                 | GCLK_GENCTRL_GENEN;
  halGclkSync();
#endif // defined(HAL_USE_WDT)
}

/**************************************************************************//**
\brief Restore default setup value: enable Main On-Chip RC oscillator running on
8 MHz for Main Clock source.
******************************************************************************/
void halRestoreStartupClock(void)
{

  /* Clock system may be already setup by flash loaders or IAR startup script.
     Restore default settings: CPU is clocked from RC oscillator running on
     8 MHz as Main Clock source. */
  halSwitchToRcClock();
  /* Switch to active clock (RC or XTAL) and perform clock system initialization */
  halSwitchToActiveClock();
}

/**************************************************************************//**
\brief Initialization of the flash controller, the clock source systems and
the watchdog timer.
******************************************************************************/
void halLowLevelInit(void)
{
  halRestoreStartupClock();

#if !defined(HAL_USE_WDT)
  /* Disable watchdog timer */
  WDT_CTRL_s.enable = 0;
#endif

  /* Enable interrupt */
  __enable_irq();
}
// eof halLowLevelInit.c
