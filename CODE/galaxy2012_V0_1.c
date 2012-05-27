/** ###################################################################
**     Filename  : galaxy2012_V0_1.C
**     Project   : galaxy2012_V0_1
**     Processor : 56F8013VFAE
**     Version   : Driver 01.14
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012/3/28, 20:03
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE galaxy2012_V0_1 */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "TI1.h"
#include "AD1.h"
#include "AS1.h"
#include "Bit1.h"
#include "PWMC1.h"
#include "Puls1.h"
#include "Puls2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "serial.h"
//-------------------------------------------------------------------

#define LOOP_TIME		250
//-------------------------------------------------------------------

unsigned int nLoop;
word L =13;
word count;
unsigned int SCIcount;
int speedL,speedR;
unsigned char receive[15]={'0','0','.','0','0','0',' ','0','0','.','0','0','0'};
int g_nSpeedControlCount=0;
int g_nDirectionControlCount=0;
//-------------------------------------------------------------------

void main(void)
{
  
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  nLoop = 0;
  
  SCIcount=0;
  
  AD1_Start();
  Puls1_Enable();
  Puls2_Enable();
   
  for(;;) 
  {
    /*******************设置程序的循环时间，控制串口的发送速度******************/
    nLoop ++;
    if(nLoop >= LOOP_TIME) 	     
      nLoop = 0;
    else 
      continue;
    //----------------------------------------------------------------
    Cpu_Delay100US(100);
  
    //----------------------------------------------------------------
    receiveData();
    sendData();
    

  }
}

/* END galaxy2012_V0_1 */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
