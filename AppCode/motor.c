/**=================================================================================
  *
  * motor.c               2012-03-30
  *
  *=================================================================================
  */
  
#include "motor.h"
#include "sensor.h"
#include "serial.h"
#include "AS1.h"
#include "Puls1.h"
#include "Puls2.h"
#include "Bit1.h"
//------------------------------------------------------------
byte pwmval;
float g_fcarSpeed;
float CAR_SPEED_SET=0;       
float SPEED_CONTROL_P=1.0;//0.8;
float SPEED_CONTROL_I=0.8;//0.0002;
float g_fspeedControlIntegral=0;
float g_fspeedControlOutOld=0;
float g_fspeedControlOutNew=0;
float g_nspeedControPeriod=0;
float g_nLeftMotorPulseSigma=0;
float g_nRightMotorPulseSigma=0;
float g_fspeedControlOut=0;
bool speedControlFlag=1;
int speedCounter = 0;
bool speedStarEndFlag=0;

float g_nDirectionControlPeriod=0;
float g_fDirectionControlOutOld = 0;
float g_fDirectionControlOut = 0;
float g_fDirectionControlOutNew = 0;
float g_fLeftVoltageSigma=0;
float g_fRightVoltageSigma=0;
float LEFT_RIGHT_MINIMUM = 25;
float DIR_CONTROL_P;
float DIR_CONTROL_P1=180;
float DIR_CONTROL_P2=160;
float DIR_CONTROL_P3=100;
float DIR_CONTROL_D=0.08;
int nLeft, nRight;

extern int speedL,speedR;
extern bool standFlag;


/**=================================================================================
  *
  * 电机PWM控制              2012-03-30
  *
  *=================================================================================
  */
  
void L_Wheel_Forward(word ratio) 
{
 PWMC1_SetRatio16(0,ratio<<8);
 PWMC1_SetRatio16(1,0);
 PWMC1_Load();
}


void L_Wheel_Back(word ratio) 
{
 PWMC1_SetRatio16(1,ratio<<8);
 PWMC1_Load(); 
 PWMC1_SetRatio16(0,0);
 PWMC1_Load();
}


void R_Wheel_Forward(word ratio)  
{
 PWMC1_SetRatio16(2,ratio<<8);
 PWMC1_Load(); 
 PWMC1_SetRatio16(3,0);
 PWMC1_Load(); 
}



void R_Wheel_Back(word ratio) 
{
 PWMC1_SetRatio16(3,ratio<<8);
 PWMC1_Load(); 
 PWMC1_SetRatio16(2,0);
 PWMC1_Load(); 
}


/**=================================================================================
  *
  * 电机的输出电压              2012-03-30
  *
  *=================================================================================
  */

byte motorOutput(float fLeftVoltage, float fRightVoltage)
{
    byte pwm;
    
    if(fLeftVoltage > 0) 			fLeftVoltage += MOTOR_OUT_DEAD_VAL;
	else if(fLeftVoltage < 0) 		fLeftVoltage -= MOTOR_OUT_DEAD_VAL;
	if(fRightVoltage > 0) 		    fRightVoltage += MOTOR_OUT_DEAD_VAL;
	else if(fRightVoltage < 0) 		fRightVoltage -= MOTOR_OUT_DEAD_VAL;
    
    if(fLeftVoltage > 255.0)           fLeftVoltage = 255.0;
    else if(fLeftVoltage < -255.0)     fLeftVoltage = -255.0;
    
    if(fRightVoltage > 255.0)          fRightVoltage = 255.0;
    else if(fRightVoltage < -255.0)    fRightVoltage = -255.0;
    //-------------------------------------------------------------
    
    if(fLeftVoltage >= 0)
    {
        pwm = (byte)(fLeftVoltage );
    	L_Wheel_Forward(pwm);
    }
    else if(fLeftVoltage < 0)
    {
        pwm = (byte)((-1) * (fLeftVoltage));
    	L_Wheel_Back(pwm);
    }
    
    if(fRightVoltage >= 0)
    {
        pwm = (byte)(fRightVoltage);
    	R_Wheel_Forward(pwm);
    }
    else if(fRightVoltage < 0)
    {
        pwm = (byte)((-1) * (fRightVoltage));
    	R_Wheel_Back(pwm);
    } 
    return pwm;  
}


/**=================================================================================
  *
  * 电机的输出电压              2012-03-30
  *
  *=================================================================================
  */
void motorControl()
{
	if((g_fGyroscopeAngleIntegral < 100.0) && (g_fGyroscopeAngleIntegral > -100.0))     
 		pwmval=motorOutput(g_fAngleControlOut - g_fspeedControlOut-g_fDirectionControlOut,
  		                   g_fAngleControlOut - g_fspeedControlOut+g_fDirectionControlOut);		                  		                    		                     		                     		                   
  	else if((g_fGyroscopeAngleIntegral >= 100.0) || (g_fGyroscopeAngleIntegral <= -100.0))
  		pwmval=motorOutput(0,0);
}


/**=================================================================================
  *
  * 电机转速             2012-03-30
  *
  *=================================================================================
  */

void GetMotorPulse(void)
{
      unsigned int nLeftPulse, nRightPulse;
	  Puls1_GetCounterValue(&nLeftPulse);
      Puls2_GetCounterValue(&nRightPulse);
      Puls1_ResetCounter();
      Puls2_ResetCounter();       
      speedL = (int)nLeftPulse;
	  speedR = (int)nRightPulse;
	  
      if(!Bit1_GetVal())
      {
        speedL = -speedL;
        speedR = -speedR;      	
      }	
	  g_nLeftMotorPulseSigma += speedL;
	  g_nRightMotorPulseSigma += speedR;       
}


/**=================================================================================
  *
  * 速度控制             2012-03-30
  *
  *=================================================================================
  */

void speedControl(void)
{
	float fdelta;
	float fP,fI;
	
	
	g_fcarSpeed=(g_nLeftMotorPulseSigma+g_nRightMotorPulseSigma)/2;
	g_nLeftMotorPulseSigma=g_nRightMotorPulseSigma=0;	
    //-------------------------------------------------------------------------------
    
    if(speedStarEndFlag)
    {
        if(nLeft <= 40 && nRight <= 40)
        {
    	    CAR_SPEED_SET = speedNeed3;
        }
        else if((nLeft > 40 && nLeft <= 70)  || (nRight > 40 && nRight <= 70))
        {
            CAR_SPEED_SET = speedNeed2;
        }
        else
        {
    	    CAR_SPEED_SET = speedNeed1;
        }
    }
    	
	fdelta=CAR_SPEED_SET-g_fcarSpeed;
	fP=fdelta*SPEED_CONTROL_P;
	fI=fdelta*SPEED_CONTROL_I;
	
	g_fspeedControlIntegral+=fI;
	
	if (g_fspeedControlIntegral > SPEED_CONTROL_OUT_MAX )	
	    g_fspeedControlIntegral = SPEED_CONTROL_OUT_MAX;
	
	if(g_fspeedControlIntegral < SPEED_CONTROL_OUT_MIN ) 	
		g_fspeedControlIntegral = SPEED_CONTROL_OUT_MIN;
		
	g_fspeedControlOutOld=g_fspeedControlOutNew;
	g_fspeedControlOutNew=fP+g_fspeedControlIntegral;
	//return fdelta;
}



/**=================================================================================
  *
  * 速度平滑            2012-03-30
  *
  *=================================================================================
  */

void speedControlOutput(void)
{
	float fValue;
	fValue=g_fspeedControlOutNew-g_fspeedControlOutOld;
	g_fspeedControlOut=fValue*(g_nspeedControPeriod+1)/SPEED_CONTROL_PERIOD+g_fspeedControlOutOld;
}


/**=================================================================================
  *
  * 方向控制            2012-03-30
  *
  *=================================================================================
  */

float SUB=0,ADD = 0;
int   RIGHT=0,LEFT=0;

void DirectionControl(void)
{
    float fLeftRightAdd, fLeftRightSub, fValue; 
    float fDValue; 
    //int nLeft, nRight;
    //---------------------------------------------------------------------------
    nLeft = (int)(g_fLeftVoltageSigma /= DIRECTION_CONTROL_COUNT);
    nRight = (int)(g_fRightVoltageSigma /= DIRECTION_CONTROL_COUNT);
    g_fLeftVoltageSigma = 0;
    g_fRightVoltageSigma = 0;
    
    if(nLeft <= 40 && nRight <= 40)
    {
    	DIR_CONTROL_P = DIR_CONTROL_P3;
    }
    else if((nLeft > 40 && nLeft <= 60)  || (nRight > 40 && nRight <= 60))
    {
        DIR_CONTROL_P = DIR_CONTROL_P2;
    }
    else
    {
    	DIR_CONTROL_P = DIR_CONTROL_P1;
    }
    
    fLeftRightAdd = nLeft + nRight;
    fLeftRightSub = nLeft - nRight;
      
    g_fDirectionControlOutOld = g_fDirectionControlOutNew;
    
    if(fLeftRightAdd <= LEFT_RIGHT_MINIMUM) {    
        g_fDirectionControlOutNew = 0;
    } else {
        if(fLeftRightAdd)
             fValue = fLeftRightSub * DIR_CONTROL_P / fLeftRightAdd;
        fDValue = gyroValue2;
        fDValue *= DIR_CONTROL_D;      
        fValue += fDValue;      
        g_fDirectionControlOutNew = fValue;
    }
    
    
    //为了看串口定义全局变量
    LEFT=nLeft;
    RIGHT=nRight;
    SUB=fLeftRightSub;
    ADD = fLeftRightAdd;       
}
	
	
/**=================================================================================
  *
  * 方向平滑              2012-03-30
  *
  *=================================================================================
  */

void DirectionControlOutput(void)
{
	float fValue;
	fValue=g_fDirectionControlOutNew-g_fDirectionControlOutOld;
	g_fDirectionControlOut=fValue*(g_nDirectionControlPeriod+1)/DIRECTION_CONTROL_PERIOD+g_fDirectionControlOutOld;
}
	




