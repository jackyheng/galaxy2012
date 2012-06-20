/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : AD1.H
**     Project   : galaxy2012_V0_1
**     Processor : 56F8013VFAE
**     Component : ADC
**     Version   : Component 01.580, Driver 02.05, CPU db: 2.87.097
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012/6/3, 12:29
**     Abstract  :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings  :
**         AD control register         : ADC_ADCR1   [61568]
**         AD control register         : ADC_ADCR2   [61569]
**         AD control register         : ADC_ADZCC   [61570]
**         AD control register         : ADC_ADLST1  [61571]
**         AD control register         : ADC_ADLST2  [61572]
**         AD control register         : ADC_ADSDIS  [61573]
**         AD control register         : ADC_ADSTAT  [61574]
**         AD control register         : ADC_ADLSTAT [61575]
**         AD control register         : ADC_ADZCSTAT [61576]
**         AD control register         : ADC_ADLLMT0 [61585]
**         AD control register         : ADC_ADLLMT1 [61586]
**         AD control register         : ADC_ADLLMT2 [61587]
**         AD control register         : ADC_ADLLMT3 [61588]
**         AD control register         : ADC_ADLLMT4 [61589]
**         AD control register         : ADC_ADLLMT5 [61590]
**         AD control register         : ADC_ADLLMT6 [61591]
**         AD control register         : ADC_ADLLMT7 [61592]
**         AD control register         : ADC_ADHLMT0 [61593]
**         AD control register         : ADC_ADHLMT1 [61594]
**         AD control register         : ADC_ADHLMT2 [61595]
**         AD control register         : ADC_ADHLMT3 [61596]
**         AD control register         : ADC_ADHLMT4 [61597]
**         AD control register         : ADC_ADHLMT5 [61598]
**         AD control register         : ADC_ADHLMT6 [61599]
**         AD control register         : ADC_ADHLMT7 [61600]
**         AD control register         : ADC_ADOFS0  [61601]
**         AD control register         : ADC_ADOFS1  [61602]
**         AD control register         : ADC_ADOFS2  [61603]
**         AD control register         : ADC_ADOFS3  [61604]
**         AD control register         : ADC_ADOFS4  [61605]
**         AD control register         : ADC_ADOFS5  [61606]
**         AD control register         : ADC_ADOFS6  [61607]
**         AD control register         : ADC_ADOFS7  [61608]
**         AD control register         : ADC_ADPOWER [61609]
**         AD control register         : ADC_CAL     [61610]
**         Interrupt name              : INT_ADCA_Complete
**         Priority                    : 1
**         User handling procedure     : AD1_OnEnd
**         Number of conversions       : 1
**         AD resolution               : 12-bit
**
**         Input pins
**
**              Port name              : GPIOC
**              Bit number (in port)   : 0
**              Bit mask of the port   : 1
**              Port data register     : GPIO_C_DR   [61729]
**              Port control register  : GPIO_C_DDR  [61730]
**              Port function register : GPIO_C_PER  [61731]
**
**              Port name              : GPIOC
**              Bit number (in port)   : 1
**              Bit mask of the port   : 2
**              Port data register     : GPIO_C_DR   [61729]
**              Port control register  : GPIO_C_DDR  [61730]
**              Port function register : GPIO_C_PER  [61731]
**
**              Port name              : GPIOC
**              Bit number (in port)   : 4
**              Bit mask of the port   : 16
**              Port data register     : GPIO_C_DR   [61729]
**              Port control register  : GPIO_C_DDR  [61730]
**              Port function register : GPIO_C_PER  [61731]
**
**              Port name              : GPIOC
**              Bit number (in port)   : 5
**              Bit mask of the port   : 32
**              Port data register     : GPIO_C_DR   [61729]
**              Port control register  : GPIO_C_DDR  [61730]
**              Port function register : GPIO_C_PER  [61731]
**
**              Port name              : GPIOC
**              Bit number (in port)   : 6
**              Bit mask of the port   : 64
**              Port data register     : GPIO_C_DR   [61729]
**              Port control register  : GPIO_C_DDR  [61730]
**              Port function register : GPIO_C_PER  [61731]
**
**         Initialization:
**              Conversion             : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-6
**     Contents  :
**         Enable     - byte AD1_Enable(void);
**         Disable    - byte AD1_Disable(void);
**         Start      - byte AD1_Start(void);
**         Stop       - byte AD1_Stop(void);
**         Measure    - byte AD1_Measure(bool WaitForResult);
**         GetValue16 - byte AD1_GetValue16(word *Values);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE AD1. */

#ifndef __AD1
#define __AD1

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* MODULE AD1. */



void AD1_InterruptCC(void);
/*
** ===================================================================
**     Method      :  AD1_InterruptCC (component ADC)
**
**     Description :
**         The method services the conversion complete interrupt of the 
**         selected peripheral(s) and eventually invokes the beans 
**         event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

byte AD1_Enable(void);
/*
** ===================================================================
**     Method      :  AD1_Enable (component ADC)
**
**     Description :
**         Enables A/D converter bean. <Events> may be generated
**         (<DisableEvent>/<EnableEvent>). If possible, this method
**         switches on A/D converter device, voltage reference, etc.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte AD1_Disable(void);
/*
** ===================================================================
**     Method      :  AD1_Disable (component ADC)
**
**     Description :
**         Disables A/D converter bean. No <events> will be generated.
**         If possible, this method switches off A/D converter device,
**         voltage reference, etc.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte AD1_Start(void);
/*
** ===================================================================
**     Method      :  AD1_Start (component ADC)
**
**     Description :
**         This method starts continuous conversion on all channels
**         that are set in the bean inspector. When each measurement on
**         all channels has finished the <OnEnd > event may be invoked.
**         This method is not available if the <interrupt service> is
**         disabled and the device doesn't support the continuous mode.
**         Note: If time of measurement is too short and the
**         instruction clock is too slow then the conversion complete
**         interrupt and its handler may cause a system overflow.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
** ===================================================================
*/

byte AD1_Stop(void);
/*
** ===================================================================
**     Method      :  AD1_Stop (component ADC)
**
**     Description :
**         This method stops the continuous measurement or disables
**         a trigger mode (if supported by HW), which has been
**         started by one of the following methods:
**         Version specific information for Freescale 56800
**         derivatives ] 
**         - <Start> 
**         - <EnableIntTrigger>
**         - <EnableIntChanTrigger>
**         The Stop method is available if one of the previously
**         mentioned methods is supported by A/D converter device
**         and is enabled to be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - No continuous measurement is
**                           running. Neither internal trigger nor
**                           external trigger have been enabled (if
**                           these are supported by HW).
** ===================================================================
*/

byte AD1_Measure(bool WaitForResult);
/*
** ===================================================================
**     Method      :  AD1_Measure (component ADC)
**
**     Description :
**         This method performs one measurement on all channels that
**         are set in the bean inspector. (Note: If the <number of
**         conversions> is more than one the conversion of A/D channels
**         is performed specified number of times.)
**     Parameters  :
**         NAME            - DESCRIPTION
**         WaitForResult   - Wait for a result of a
**                           conversion. If <interrupt service> is
**                           disabled, A/D peripheral doesn't support
**                           measuring all channels at once or Autoscan
**                           mode property isn't enabled and at the same
**                           time the <number of channel> is greater
**                           than 1, then the WaitForResult parameter is
**                           ignored and the method waits for each
**                           result every time. If the <interrupt
**                           service> is disabled and a <number of
**                           conversions> is greater than 1, the
**                           parameter is ignored and the method also
**                           waits for each result every time.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
** ===================================================================
*/

byte AD1_GetValue16(word *Values);
/*
** ===================================================================
**     Method      :  AD1_GetValue16 (component ADC)
**
**     Description :
**         This method returns the last measured values of all channels
**         justified to the left. Compared with <GetValue> method this
**         method returns more accurate result if the <number of
**         conversions> is greater than 1 and <AD resolution> is less
**         than 16 bits. In addition, the user code dependency on <AD
**         resolution> is eliminated.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Values          - Pointer to the array that contains
**                           the measured data.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
** ===================================================================
*/

void AD1_Init(void);
/*
** ===================================================================
**     Method      :  AD1_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END AD1. */

#endif /* ifndef __AD1 */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
