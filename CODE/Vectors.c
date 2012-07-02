/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Vectors.C
**     Project   : galaxy2012_V0_1
**     Processor : 56F8013VFAE
**     Version   : Component 01.022, Driver 02.08, CPU db: 2.87.097
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012/6/26, 8:56
**     Abstract  :
**
**     Settings  :
**
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#include "Cpu.h"
#include "TI1.h"
#include "AD1.h"
#include "PWMC1.h"
#include "Puls1.h"
#include "Puls2.h"
#include "AS1.h"
#include "Bit1.h"
#include "Events.h"

/*lint -save -e40 -e718 -e746 -e745 -e939 -e937 -e957 -e505 -e522 -e533 Disable MISRA rule (20,75,71,53,83) checking. */

extern void _EntryPoint(void);         /* Startup routine */

volatile asm void _vectboot(void);
#pragma define_section interrupt_vectorsboot "interrupt_vectorsboot.text"  RX
#pragma section interrupt_vectorsboot begin
volatile asm void _vectboot(void) {
  JMP  _EntryPoint                     /* Reset vector (Used) */
  JMP  _EntryPoint                     /* COP reset vector (Used) */
}
#pragma section interrupt_vectorsboot end

volatile asm void _vect(void);
#pragma define_section interrupt_vectors "interrupt_vectors.text"  RX
#pragma section interrupt_vectors begin
volatile asm void _vect(void) {
  JMP  _EntryPoint                     /* Interrupt no. 0 (Used)   - ivINT_Reset */
  JMP  _EntryPoint                     /* Interrupt no. 1 (Used)   - ivINT_COPReset  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 2 (Unused) - ivINT_Illegal_Instruction  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 3 (Unused) - ivINT_SW3  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 4 (Unused) - ivINT_HWStackOverflow  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 5 (Unused) - ivINT_MisalignedLongWordAccess  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 6 (Unused) - ivINT_OnCE_StepCounter  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 7 (Unused) - ivINT_OnCE_BU0  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 8 (Unused) - ivINT_OnCE_TraceBuffer  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 9 (Unused) - ivINT_OnCE_TxREmpty  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 10 (Unused) - ivINT_OnCE_RxRFull  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 11 (Unused) - ivINT_SW2  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 12 (Unused) - ivINT_SW1  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 13 (Unused) - ivINT_SW0  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 14 (Unused) - ivReserved3  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 15 (Unused) - ivReserved4  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 16 (Unused) - ivINT_LVI  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 17 (Unused) - ivINT_PLL  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 18 (Unused) - ivINT_HFM_ERR  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 19 (Unused) - ivINT_HFM_CC  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 20 (Unused) - ivINT_HFM_CBE  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 21 (Unused) - ivReserved8  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 22 (Unused) - ivINT_GPIO_D  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 23 (Unused) - ivINT_GPIO_C  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 24 (Unused) - ivINT_GPIO_B  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 25 (Unused) - ivINT_GPIO_A  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 26 (Unused) - ivINT_SPI_RxFull  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 27 (Unused) - ivINT_SPI_TxEmpty  */
  JSR  AS1_InterruptTx                 /* Interrupt no. 28 (Used)   - ivINT_SCI_TxEmpty  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 29 (Unused) - ivINT_SCI_TxIdle  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 30 (Unused) - ivINT_SCI_Reserved  */
  JSR  AS1_InterruptError              /* Interrupt no. 31 (Used)   - ivINT_SCI_RxError  */
  JSR  AS1_InterruptRx                 /* Interrupt no. 32 (Used)   - ivINT_SCI_RxFull  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 33 (Unused) - ivReserved9  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 34 (Unused) - ivReserved10  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 35 (Unused) - ivINT_I2C  */
  JSR  TI1_Interrupt                   /* Interrupt no. 36 (Used)   - ivINT_TMR0  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 37 (Unused) - ivINT_TMR1  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 38 (Unused) - ivINT_TMR2  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 39 (Unused) - ivINT_TMR3  */
  JSR  AD1_InterruptCC                 /* Interrupt no. 40 (Used)   - ivINT_ADCA_Complete  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 41 (Unused) - ivINT_ADCB_Complete  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 42 (Unused) - ivINT_ADC_ZC_LE  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 43 (Unused) - ivINT_PWM_Reload  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 44 (Unused) - ivINT_PWM_Fault  */
  JSR  Cpu_Interrupt                   /* Interrupt no. 45 (Unused) - ivINT_LP  */
}
#pragma section interrupt_vectors end

/*lint -restore */

/* Disable MISRA rules for interurupt routines */
/*lint -esym(765,Cpu_Interrupt) Disable MISRA rule (23) checking for symbols (Cpu_Interrupt). */
/*lint -esym(765,AS1_InterruptTx) Disable MISRA rule (23) checking for symbols (AS1_InterruptTx). */
/*lint -esym(765,AS1_InterruptError) Disable MISRA rule (23) checking for symbols (AS1_InterruptError). */
/*lint -esym(765,AS1_InterruptRx) Disable MISRA rule (23) checking for symbols (AS1_InterruptRx). */
/*lint -esym(765,TI1_Interrupt) Disable MISRA rule (23) checking for symbols (TI1_Interrupt). */
/*lint -esym(765,AD1_InterruptCC) Disable MISRA rule (23) checking for symbols (AD1_InterruptCC). */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
