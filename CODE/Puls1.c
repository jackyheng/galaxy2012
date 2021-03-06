/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Puls1.C
**     Project   : galaxy2012_V0_1
**     Processor : 56F8013VFAE
**     Component : PulseAccumulator
**     Version   : Component 01.183, Driver 02.03, CPU db: 2.87.097
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012/6/26, 8:56
**     Abstract  :
**          Pulse accumulator counts the number of active edges at the input of its
**          channel.
**     Settings  :
**             Pulse accumulator       : TMR1_PACNT
**
**
**         Used input pin              :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       17            |  GPIOB2_MISO_T2
**             ----------------------------------------------------
**
**         Mode                        : Count
**
**         Initialization:
**              Pulse accumulator      : Disabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : TMR1_CNTR [61461]
**              Hold                   : TMR1_HOLD [61460]
**              Run                    : TMR1_CTRL [61462]
**              Prescaler              : TMR1_CTRL [61462]
**
**         User handling procedure     : not specified
**
**     Contents  :
**         Enable           - byte Puls1_Enable(void);
**         Disable          - byte Puls1_Disable(void);
**         ResetCounter     - void Puls1_ResetCounter(void);
**         GetCounterValue  - void Puls1_GetCounterValue(word *Value);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE Puls1. */

#include "Puls1.h"

/*
** ===================================================================
**     Method      :  Puls1_Enable (component PulseAccumulator)
**
**     Description :
**         Enables the bean.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
** ===================================================================
*/
byte Puls1_Enable(void)
{
  setRegBitGroup(TMR1_CTRL,CM,1);      /* Run counter */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  Puls1_Disable (component PulseAccumulator)
**
**     Description :
**         Disables the bean.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
** ===================================================================
*/
byte Puls1_Disable(void)
{
  setRegBitGroup(TMR1_CTRL,CM,0);      /* Stop counter */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  Puls1_ResetCounter (component PulseAccumulator)
**
**     Description :
**         This method resets the pulse accumulator counter (sets to
**         zero).
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Puls1_ResetCounter(void)
{
  setReg(TMR1_CNTR,0);                 /* Reset counter register */
}

/*
** ===================================================================
**     Method      :  Puls1_GetCounterValue (component PulseAccumulator)
**
**     Description :
**         This method returns the content of the pulse accumulator
**         counter.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Value           - Pointer to returned value. [Note:]
**                           Parameter type depends on the width of the
**                           selected counter (may be 8, 16, 32 or 64
**                           bits long). See the method prototype in the
**                           generated module.
**     Returns     : Nothing
** ===================================================================
*/
void Puls1_GetCounterValue(Puls1_TCounterValue *Value)
{
  *Value = getReg(TMR1_CNTR);          /* Return counter value */
}

/*
** ===================================================================
**     Method      :  Puls1_Init (component PulseAccumulator)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void Puls1_Init(void)
{
  /* TMR1_CTRL: CM=0,PCS=2,SCS=0,ONCE=0,LENGTH=0,DIR=0,Co_INIT=0,OM=0 */
  setReg(TMR1_CTRL,1024);              /* Set up mode */
  /* TMR1_SCR: TCF=0,TCFIE=0,TOF=0,TOFIE=0,IEF=0,IEFIE=0,IPS=1,INPUT=0,Capture_Mode=0,MSTR=0,EEOF=0,VAL=0,FORCE=0,OPS=0,OEN=0 */
  setReg(TMR1_SCR,512);
  setReg(TMR1_CNTR,0);                 /* Reset counter register */
  setReg(TMR1_LOAD,0);                 /* Reset load register */
}

/* END Puls1. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
