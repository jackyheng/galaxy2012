/**=================================================================================
  *
  * sensor.c               by QI_ZI_HENG 2012-03-23
  *
  *=================================================================================
  */
  
#include "sensor.h"
#include "AD1.h"
#include "motor.h"
//-------------------------------------------------------------------------------
       
unsigned int nInputVoltage[channal];         
unsigned int sensorValue[channal];  
unsigned int sensorZero[channal];         
float AccValue;                                //加速度减去静止数得到的数
float gyroValue;                               //角速度减去静止数得到的数
float g_fGravityAngle;                         //加速度计算后的角度
float g_fGyroscopeAngleSpeed;                  //陀螺仪的角速度
float g_fGyroscopeAngleIntegral;               //陀螺仪积分后的角度
float fDeltaValue;
float g_fCarAngle;
float ANGLE_CONTROL_P = 38;                     //角度控制比例
float ANGLE_CONTROL_D = 0.1;//0.37;                     //角度控制微分
float g_fAngleControlOut;
int VOLTAGE_LEFT;
int VOLTAGE_RIGHT;

extern float g_fLeftVoltageSigma;
extern float g_fRightVoltageSigma;
//---------------------------------------------------------------------------------


/**=================================================================================
  *
  * 测量ADC的静止值              2012-03-23
  *
  *=================================================================================
  */

void calibrateSensor()
{
	unsigned long v = 0;
	unsigned int n,i;
    for(n=0; n<channal; n++) 
    {
      v = 0;
      for(i=0; i<50; i++)
      {
        AD1_GetValue16(nInputVoltage);
      	v += (nInputVoltage[n] >> 4);
      }      
      sensorZero[n] = (unsigned int)(v / 50);
    }     	
}


/**=================================================================================
  *
  * 更新陀螺仪和加速度ADC的数据                2012-03-23
  *
  *=================================================================================
  */

void updataSensor()
{		
	unsigned long v = 0;
	unsigned int n,i;
	for(n=0; n<channal; n++)
	{
	    v = 0;
		for(i=0; i<ADC_Counter; i++)
	    {
	      AD1_GetValue16(nInputVoltage);
		  v += (nInputVoltage[n] >> 4);
		  
	    }
	    sensorValue[n] = (unsigned int)(v / ADC_Counter);
	}
	AccValue = (int)(-1*(sensorValue[0] - sensorZero[0]));
	gyroValue = (int)(sensorValue[1] - sensorZero[1]) * -1;

    VOLTAGE_LEFT = (int)sensorValue[2];	
	VOLTAGE_RIGHT = (int)sensorValue[3];	
/*    g_fLeftVoltageSigma = (int)(sensorValue[2] - LeftOffset)+g_fLeftVoltageSigma;	
	g_fRightVoltageSigma = (int)(sensorValue[3] - RightOffset)+g_fRightVoltageSigma;

*/	

}
	
	
	
	

/**=================================================================================
  *
  * 电磁数据处理                2012-05-7
  *
  *=================================================================================
  */

void DirectionVoltageSigma(void)
{		
	int nLeft, nRight;
	if(VOLTAGE_LEFT > LeftOffset) 		nLeft = VOLTAGE_LEFT - LeftOffset;
	else nLeft = 0;
	if(VOLTAGE_RIGHT > RightOffset) 	nRight = VOLTAGE_RIGHT - RightOffset;
	else nRight = 0;

	g_fLeftVoltageSigma += nLeft;
	g_fRightVoltageSigma += nRight;
		
}

	

/**=================================================================================
  *
  * 角度的计算                    2012-03-23
  *
  *=================================================================================
  */

void AngleCalculate() 
{	
    g_fGravityAngle = (AccValue * GRAVITY_ANGLE_RATIO) ;
	g_fGyroscopeAngleSpeed = (gyroValue * GYROSCOPE_ANGLE_RATIO) ;
	
    complementaryFilter();	
}


/**=================================================================================
  *
  * 互补滤波                      2012-03-26
  *
  *=================================================================================
  */
  
void complementaryFilter()
{
/*	g_fCarAngle = g_fGyroscopeAngleIntegral;
    fDeltaValue = (g_fGravityAngle - g_fCarAngle) / GRAVITY_ADJUST_TIME_CONSTANT;	
    g_fGyroscopeAngleIntegral += (g_fGyroscopeAngleSpeed + fDeltaValue) * GYROSCOPE_ANGLE_SIGMA_FREQUENCY;
*/
	g_fGyroscopeAngleIntegral = ((0.99)*((g_fGyroscopeAngleIntegral) + 
	(g_fGyroscopeAngleSpeed * GYROSCOPE_ANGLE_SIGMA_FREQUENCY)) + (0.01)*(g_fGravityAngle));
		
}
 

/**=================================================================================
  *
  * 角度的PD值控制                2012-03-28
  *
  *=================================================================================
  */

void AngleControl() 
{
	float fValue;	

	fValue = (g_fGyroscopeAngleIntegral * ANGLE_CONTROL_P + g_fGyroscopeAngleSpeed * ANGLE_CONTROL_D); 
	         
	g_fAngleControlOut = fValue;	
}





