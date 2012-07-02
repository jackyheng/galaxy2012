/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Bit1.C
**     Project   : galaxy2012_V0_1
**     Processor : 56F8013VFAE
**     Component : BitIO
**     Version   : Component 02.075, Driver 01.18, CPU db: 2.87.097
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012/6/26, 8:56
**     Abstract  :
**         This bean "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This bean is set to work in Input direction only.
**         Methods of this bean are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       2             |  GPIOB1_SS_B_SDA
**             ----------------------------------------------------
**
**         Port name                   : GPIOB
**
**         Bit number (in port)        : 1
**         Bit mask of the port        : 2
**
**         Initial direction           : Input (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : GPIO_B_DR [61713]
**         Port control register       : GPIO_B_DDR [61714]
**         Port function register      : GPIO_B_PER [61715]
**
**         Optimization for            : speed
**     Contents  :
**         GetVal - bool Bit1_GetVal(void);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE Bit1. */

#include "Bit1.h"
/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "Cpu.h"


/*
** ===================================================================
**     Method      :  Bit1_GetVal (component BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**         Note: This bean is set to work in Input direction only.
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
/*
bool Bit1_GetVal(void)

**  This method is implemented as a macro. See Bit1.h file.  **

*/

/* END Bit1. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
