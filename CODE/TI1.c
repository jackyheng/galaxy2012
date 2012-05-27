/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : TI1.C
**     Project   : galaxy2012_V0_1
**     Processor : 56F8013VFAE
**     Component : TimerInt
**     Version   : Component 02.157, Driver 02.02, CPU db: 2.87.097
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012/5/27, 19:24
**     Abstract  :
**         This bean "TimerInt" implements a periodic interrupt.
**         When the bean and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings  :
**         Timer name                  : TMR0 (16-bit)
**         Compare name                : TMR0_Compare
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 32000000 Hz
**           Initial period/frequency
**             Xtal ticks              : 8000
**             microseconds            : 1000
**             milliseconds            : 1
**             seconds (real)          : 0.001
**             Hz                      : 1000
**             kHz                     : 1
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : TMR0_CNTR [61445]
**              Mode                   : TMR0_CTRL [61446]
**              Run                    : TMR0_CTRL [61446]
**              Prescaler              : TMR0_CTRL [61446]
**
**         Compare registers
**              Compare                : TMR0_CMP1 [61440]
**
**         Flip-flop registers
**              Mode                   : TMR0_SCR  [61447]
**     Contents  :
**         EnableEvent  - byte TI1_EnableEvent(void);
**         DisableEvent - byte TI1_DisableEvent(void);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE TI1. */

#include "Events.h"
#include "TI1.h"

static bool EnEvent;                   /* Enable/Disable events */


/* Internal method prototypes */
static void SetCV(word Val);
static void SetPV(byte Val);

/*
** ===================================================================
**     Method      :  SetCV (component TimerInt)
**
**     Description :
**         Sets compare or preload register value. The method is called 
**         automatically as a part of several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetCV(word Val)
{
  EnterCritical();                     /* Disable global interrupts */
  setReg(TMR0_CMPLD1,Val);             /* Store given value to the compare preload 1 register */
  setReg(TMR0_CMPLD2,Val);             /* Store given value to the compare preload 2 register */
  ExitCritical();                      /* Enable global interrupts */
}

/*
** ===================================================================
**     Method      :  SetPV (component TimerInt)
**
**     Description :
**         Sets prescaler value. The method is called automatically as a 
**         part of several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetPV(byte Val)
{
  setRegBitGroup(TMR0_CTRL,PCS,Val);   /* Store given value to the prescaler */
  setReg(TMR0_CNTR,0);                 /* Reset counter */
}

/*
** ===================================================================
**     Method      :  TI1_EnableEvent (component TimerInt)
**
**     Description :
**         This method enables the events.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte TI1_EnableEvent(void)
{
  EnEvent = TRUE;                      /* Set the flag "events enabled" */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TI1_DisableEvent (component TimerInt)
**
**     Description :
**         This method disables the events.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte TI1_DisableEvent(void)
{
  EnEvent = FALSE;                     /* Set the flag "events disabled" */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TI1_Init (component TimerInt)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void TI1_Init(void)
{
  /* TMR0_CTRL: CM=0,PCS=0,SCS=0,ONCE=0,LENGTH=1,DIR=0,Co_INIT=0,OM=4 */
  setReg(TMR0_CTRL,36);                /* Stop timer, use alternating compare registers */
  /* TMR0_SCR: TCF=0,TCFIE=1,TOF=0,TOFIE=0,IEF=0,IEFIE=0,IPS=0,INPUT=0,Capture_Mode=0,MSTR=0,EEOF=0,VAL=0,FORCE=0,OPS=0,OEN=0 */
  setReg(TMR0_SCR,16384);              /* Enable compare interrupt */
  setReg(TMR0_CNTR,0);                 /* Reset counter register */
  setReg(TMR0_LOAD,0);                 /* Reset load register */
  setReg(TMR0_CMP1,31999);             /* Set up compare 1 register */
  setReg(TMR0_CMP2,31999);             /* Set up compare 2 register */
  /* TMR0_COMSCR: DBG_EN=0,??=0,??=0,??=0,??=0,??=0,??=0,TCF2EN=0,TCF1EN=0,TCF2=0,TCF1=0,CL2=1,CL1=2 */
  setReg(TMR0_COMSCR,6);               /* Compare load control */
  EnEvent = TRUE;                      /* Enable events */
  SetCV((word)31999);                  /* Store appropriate value to the compare register according to the selected high speed CPU mode */
  SetPV((byte)8);                      /* Set prescaler register according to the selected high speed CPU mode */
  setRegBitGroup(TMR0_CTRL,CM,1);      /* Run counter */
}

/*
** ===================================================================
**     Method      :  TI1_Interrupt (component TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma interrupt alignsp saveall
void TI1_Interrupt(void)
{
  clrRegBit(TMR0_SCR,TCF);             /* Reset interrupt request flag */
  if (EnEvent) {                       /* Are the events enabled? */
    TI1_OnInterrupt();                 /* Invoke user event */
  }
}

/* END TI1. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
