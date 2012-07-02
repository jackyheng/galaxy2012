/** ###################################################################
**     Filename  : Events.C
**     Project   : galaxy2012_V0_1
**     Processor : 56F8013VFAE
**     Component : Events
**     Version   : Driver 01.03
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012/3/28, 20:03
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         AD1_OnEnd       - void AD1_OnEnd(void);
**         TI1_OnInterrupt - void TI1_OnInterrupt(void);
**
** ###################################################################*/
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

unsigned int oneMsCounter = 0;
unsigned int oneHundredMsCounter = 0;
extern unsigned int SCIcount;
extern unsigned int speedL,speedR;
extern int g_nSpeedControlCount;
extern int g_nDirectionControlCount;
extern bool AD_Flag;
extern bool UartFlag;
extern bool standFlag;
//--------------------------------------------------------------------

/*
** ===================================================================
**     Event       :  AD1_OnEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void AD1_OnEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void TI1_OnInterrupt(void)
{
  oneMsCounter++;
  
  //------------------------------------------- 
    g_nspeedControPeriod ++;
  	speedControlOutput();
  //___________________________________________
  
  //-------------------------------------------
  
    g_nDirectionControlPeriod ++;
  	DirectionControlOutput();
  //___________________________________________
  
  if(oneMsCounter == 1)            
  {
     if(AD_Flag)    updataSensor();  		       //读取ADC的值
  }
//--------------------------------------------------  
  else if(oneMsCounter == 2)       
  {
    AngleCalculate();              //计算角度
  	AngleControl();                //角度的PD值控制  	 
  	motorControl();                //电机输出控制		
  }
//-----------------------------------------------  
  else if(oneMsCounter == 3)       
  {  
    g_nSpeedControlCount++;
    oneHundredMsCounter++;
    
    if(g_nSpeedControlCount >= SPEED_CONTROL_COUNT)
    {
      speedControl();               //速度控制
      g_nSpeedControlCount=0;
      g_nspeedControPeriod=0;	
    }
    
    if(standFlag){
        if(oneHundredMsCounter == 100)         
        {
          if(CAR_SPEED_SET < speedNeed3)
              CAR_SPEED_SET += 10;
          else
          {
              CAR_SPEED_SET = speedNeed3;
              speedStarEndFlag = 1;
          }   
          oneHundredMsCounter = 0;         
        }
    }
    else
    {
        CAR_SPEED_SET = 0;
        oneHundredMsCounter = 0;
        speedStarEndFlag = 0;
    }
  }
//--------------------------------------------------  
  else if(oneMsCounter == 4)       
  {
      g_nDirectionControlCount ++;
      DianciCalculate();
      DirectionVoltageSigma();
      if(g_nDirectionControlCount >= DIRECTION_CONTROL_COUNT) {
          DirectionControl();
          g_nDirectionControlCount = 0;
          g_nDirectionControlPeriod = 0;
      }  	  
  }
//-------------------------------------------------  
  else if(oneMsCounter >= 5)
  {
  	oneMsCounter = 0; 
  	GetMotorPulse();
  	UartFlag = 1;
  }
}

/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be
**         read using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void AS1_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is
**         received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the
**         <Receiver> property is enabled or the <SCI output mode>
**         property (if supported) is set to Single-wire mode.
**         Version specific information for Freescale 56800
**         derivatives ] 
**         DMA mode:
**         If DMA controller is available on the selected CPU and
**         the receiver is configured to use DMA controller then
**         this event is disabled. Only OnFullRxBuf method can be
**         used in DMA mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void AS1_OnRxChar(void)
{
  AS1_RecvChar(&receive[SCIcount]);
  if(receive[SCIcount]=='c')        
      SCIcount=0;
  else
  {
      SCIcount++;
      if(SCIcount>=13)
         SCIcount=0;  	
  }
}

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void AS1_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFullRxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void AS1_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFreeTxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void AS1_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI2_OnInterrupt (module Events)
**
**     Component   :  TI2 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void TI2_OnInterrupt(void)
{
  /* Write your code here ... */
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
