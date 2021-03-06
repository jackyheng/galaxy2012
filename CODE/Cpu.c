/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Cpu.C
**     Project   : galaxy2012_V0_1
**     Processor : 56F8013VFAE
**     Component : 56F8013VFAE
**     Version   : Component 01.022, Driver 02.08, CPU db: 2.87.097
**     Datasheet :  MC56F8300UM/D - Rev. 1.0
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012/6/26, 8:56
**     Abstract  :
**
**     Settings  :
**
**     Contents  :
**         EnableInt   - void Cpu_EnableInt(void);
**         DisableInt  - void Cpu_DisableInt(void);
**         SetWaitMode - void Cpu_SetWaitMode(void);
**         SetStopMode - void Cpu_SetStopMode(void);
**         Delay100US  - asm void Cpu_Delay100US(word us100);
**
**     (c) Freescale Semiconductor
**     2004 All Rights Reserved
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE Cpu. */
#include "TI1.h"
#include "AD1.h"
#include "PWMC1.h"
#include "Puls1.h"
#include "Puls2.h"
#include "AS1.h"
#include "Bit1.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Events.h"
#include "Cpu.h"


/* Global variables */
volatile word SR_lock = 0;             /* Lock */
volatile word SR_reg;                  /* Current value of the SR register */
/*
** ===================================================================
**     Method      :  Cpu_Interrupt (component 56F8013VFAE)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma interrupt alignsp
void Cpu_Interrupt(void)
{
  asm(DEBUGHLT);                       /* Halt the core and placing it in the debug processing state */
}

/*
** ===================================================================
**     Method      :  Cpu_Delay100US (component 56F8013VFAE)
**
**     Description :
**         This method realizes software delay. The length of delay
**         is at least 100 microsecond multiply input parameter
**         [us100]. As the delay implementation is not based on real
**         clock, the delay time may be increased by interrupt
**         service routines processed during the delay. Adding read
**         wait states for external program memory can cause delay
**         extension as well. The method is independent on selected
**         speed mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us100           - Number of 100 us delay repetitions.
**     Returns     : Nothing
** ===================================================================
*/
/*lint -save -e???? Disable MISRA rule (all) checking. */
asm void Cpu_Delay100US(word us100)
{
  /* Total irremovable overhead: about 16 cycles */
  /* move.w: 2 cycles overhead (load parameter into register) */
  /* jsr:    5 cycles overhead (jump to subroutine) */
  /* rts:    8 cycles overhead (return from subroutine) */
  /* nop:    1 cycles overhead (aditional nops) */

  loop:
  /* 100 us delay block begin */
  /*
   * Delay
   *   - requested                  : 100 us @ 32MHz,
   *   - possible                   : 3200 c, 100000 ns
   *   - without removable overhead : 3194 c, 99812.5 ns
   */
  adda #2, SP                          /* (1 c: 31.25 ns) move SP forward */
  move.l A10, X:(SP)                   /* (2 c: 62.5 ns) push A */
  move.w #3178, A                      /* (2 c: 62.5 ns) number of iterations */
  do A, label0                         /* (8 c: 250 ns) repeat 3178x nop */
    nop                                /* (1 c: 31.25 ns) wait for 1 c */
  label0:
  move.l X:(SP), A                     /* (2 c: 62.5 ns) pop A */
  suba #2, SP                          /* (1 c: 31.25 ns) move SP back */
  /* 100 us delay block end */
  dec.w Y0                             /* us100 parameter is passed via Y0 register */
  jne loop                             /* next loop */
  nop                                  /* avoid pipeline conflicts */
  rts                                  /* return from subroutine */
}
/*lint -restore */

/*
** ===================================================================
**     Method      :  Cpu_DisableInt (component 56F8013VFAE)
**
**     Description :
**         Disables all maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_DisableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (component 56F8013VFAE)
**
**     Description :
**         Enables all maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_EnableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetStopMode (component 56F8013VFAE)
**
**     Description :
**         Sets low power mode - Stop mode.
**         For more information about the stop mode see this CPU
**         documentation.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetStopMode(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetWaitMode (component 56F8013VFAE)
**
**     Description :
**         Sets low power mode - Wait mode.
**         For more information about the wait mode see this CPU
**         documentation.
**         Release from wait mode: Reset or interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetWaitMode(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  _EntryPoint (component 56F8013VFAE)
**
**     Description :
**         Initializes the whole system like timing and so on. At the end 
**         of this function, the C startup is invoked to initialize stack,
**         memory areas and so on.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
extern void init_56800_(void);         /* Forward declaration of external startup function declared in startup file */

/*** !!! Here you can place your own code using property "User data declarations" on the build options tab. !!! ***/

void _EntryPoint(void)
{
  #pragma constarray off

  /*** !!! Here you can place your own code before PE initialization using property "User code before PE initialization" on the build options tab. !!! ***/

  /*** ### 56F8013VFAE "Cpu" init code ... ***/
  /*** PE initialization code after reset ***/
  /* System clock initialization */
  setRegBitGroup(OSCTL, TRIM, (word)getReg(FMOPT1)); /* Set the trim osc freq with factory programmed value */
  clrRegBit(PLLCR, PRECS);             /* Select an internal clock source for the CPU core */
  setReg(PLLCR, (PLLCR_LCKON_MASK | PLLCR_ZSRC0_MASK)); /* Enable PLL, LCKON and select clock source from prescaler */
  /* PLLDB: LORTP=2,??=0,PLLCOD=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  setReg16(PLLDB, 8192U);              /* Set the clock prescalers */ 
  while(!getRegBit(PLLSR, LCK0)){}     /* Wait for PLL lock */
  setReg(PLLCR, (PLLCR_LCKON_MASK | PLLCR_ZSRC1_MASK)); /* Select clock source from postscaler */
  /* FMCLKD: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DIVLD=0,PRDIV8=0,DIV=40 */
  setReg16(FMCLKD, 40U);               /* Set the flash clock prescaler */ 
  /*** End of PE initialization code after reset ***/

  /*** !!! Here you can place your own code after PE initialization using property "User code after PE initialization" on the build options tab. !!! ***/

  asm(JMP init_56800_);                /* Jump to C startup code */
}

/*
** ===================================================================
**     Method      :  PE_low_level_init (component 56F8013VFAE)
**
**     Description :
**         Initializes beans and provides common register initialization. 
**         The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  /* GPIO_A_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE=0 */
  setReg16(GPIO_A_DRIVE, 0U);          /* Set High/Low drive strength on GPIOA pins according to the CPU bean settings */ 
  /* GPIO_B_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE=0 */
  setReg16(GPIO_B_DRIVE, 0U);          /* Set High/Low drive strength on GPIOB pins according to the CPU bean settings */ 
  /* GPIO_C_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE6=0,DRIVE5=0,DRIVE4=0,??=0,DRIVE2=0,DRIVE1=0,DRIVE0=0 */
  setReg16(GPIO_C_DRIVE, 0U);          /* Set High/Low drive strength on GPIOC pins according to the CPU bean settings */ 
  /* GPIO_D_DRIVE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DRIVE=0 */
  setReg16(GPIO_D_DRIVE, 0U);          /* Set High/Low drive strength on GPIOD pins according to the CPU bean settings */ 
  /* SIM_PCE: I2C=0,??=0,ADC=1,??=0,??=0,??=0,??=0,??=0,??=0,TMR=1,??=0,SCI=1,??=0,SPI=0,??=0,PWM=1 */
  setReg16(SIM_PCE, 8273U);            /* Set up the peripheral clock enable register */ 
  /* SIM_CTRL: TC3_SD=0,TC2_SD=0,TC1_SD=0,TC0_SD=0,SCI_SD=0,??=0,TC3_INP=0,??=0,??=0,??=0,ONCEEBL=0,SWRST=0,STOP_DISABLE=0,WAIT_DISABLE=0 */
  setReg16(SIM_CTRL, 0U);              /* Set up the SIM control register */ 
  /* SIM_CLKOUT: ??=0,??=0,??=0,??=0,??=0,??=0,PWM3_b=0,PWM2_b=0,PWM1_b=0,PWM0_b=0,CLKDIS=1,CLKOSEL=0 */
  setReg16(SIM_CLKOUT, 32U);           /* Set up the SIM clock output select register */ 
  /* Common initialization of the CPU registers */
  /* INTC_IPR3: ADCA_CC_IPL=2,TMR_0_IPL=2 */
  clrSetReg16Bits(INTC_IPR3, 16448U, 32896U); 
  /* INTC_IPR4: ADC_ZC_IPL=2 */
  clrSetReg16Bits(INTC_IPR4, 4U, 8U);   
  /* GPIO_C_PER: PE6=1,PE5=1,PE4=1,PE1=1,PE0=1 */
  setReg16Bits(GPIO_C_PER, 115U);       
  /* GPIO_A_PER: PE|=127 */
  setReg16Bits(GPIO_A_PER, 127U);       
  /* SIM_CLKOUT: PWM3_b=0,PWM2_b=0,PWM1_b=0,PWM0_b=0 */
  clrReg16Bits(SIM_CLKOUT, 960U);       
  /* SIM_GPS: CFG_B7=0,CFG_B6=0,CFG_B5=1,CFG_B4=0,CFG_B2=1,CFG_A5=2,CFG_A4=2 */
  clrSetReg16Bits(SIM_GPS, 3333U, 586U); 
  /* GPIO_B_PER: PE&=~2,PE|=244 */
  clrSetReg16Bits(GPIO_B_PER, 2U, 244U); 
  /* GPIO_B_PUR: PU&=~22 */
  clrReg16Bits(GPIO_B_PUR, 22U);        
  /* INTC_IPR2: SCI_RCV_IPL=2,SCI_RERR_IPL=2,SCI_TIDL_IPL=2,SCI_XMIT_IPL=2 */
  clrSetReg16Bits(INTC_IPR2, 20800U, 41600U); 
  /* GPIO_B_IENR: IEN&=~2 */
  clrReg16Bits(GPIO_B_IENR, 2U);        
  /* GPIO_B_IAR: IA&=~2 */
  clrReg16Bits(GPIO_B_IAR, 2U);         
  /* GPIO_B_IESR: IES|=2 */
  setReg16Bits(GPIO_B_IESR, 2U);        
  /* GPIO_B_DDR: DD&=~2 */
  clrReg16Bits(GPIO_B_DDR, 2U);         
  /* ### TimerInt "TI1" init code ... */
  TI1_Init();
  /* ### ADC "AD1" init code ... */
  AD1_Init();
  /* ### PWMMC "PWMC1" init code ... */
  PWMC1_Init();


  /* ### PulseAccumulator "Puls1" init code ... */
  Puls1_Init();
  /* ### PulseAccumulator "Puls2" init code ... */
  Puls2_Init();
  /* ### Asynchro serial "AS1" init code ... */
  AS1_Init();
  __EI(0);                             /* Enable interrupts of the selected priority level */
}

/* END Cpu. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
