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
float gyroValue2;
float g_fGravityAngle;                         //加速度计算后的角度
float g_fGyroscopeAngleSpeed;                  //陀螺仪的角速度
float g_fGyroscopeAngleIntegral;               //陀螺仪积分后的角度
float fDeltaValue;
float g_fCarAngle;
float ANGLE_CONTROL_P = 20.0;//38;                     //角度控制比例
float ANGLE_CONTROL_D = 0.05;//0.37;                     //角度控制微分
float g_fAngleControlOut;
int VOLTAGE_LEFT;
int VOLTAGE_RIGHT;
unsigned int dianciValue[]={0,0};
unsigned int dianciMax[]={380,350}; //830,550
unsigned int dianciMin[]={90,45};//25

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
  * 更新ADC的数据                2012-03-23
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
	AccValue = (int)(-1*(sensorValue[0] - AccOffset));
	gyroValue = (int)(sensorValue[1] - sensorZero[1]) * -1;
    VOLTAGE_LEFT = (int)sensorValue[2];	
	VOLTAGE_RIGHT = (int)sensorValue[3];		
	gyroValue2 = (int)(sensorValue[4] - sensorZero[4]);	
}


/**=================================================================================
  *
  * 对电磁传感器的信号进行归一化                2012-06-26
  *
  *=================================================================================
  */

void DianciCalculate()
{
    int i;
    long j,k,x;
    
    for(i=0; i<2; i++)
    {
    	if(sensorValue[i+2] <= dianciMin[i])
    	{
    		sensorValue[i+2] = dianciMin[i];
    	}
    	if(sensorValue[i+2] >= dianciMax[i])
    	{
    		sensorValue[i+2] = dianciMax[i];
    	}
    	
    	j=0;k=0;x=0;
        j = ((sensorValue[i+2]-dianciMin[i]));
        j = j*100;
        k = (dianciMax[i]-dianciMin[i]);
        x = (j/k);
        dianciValue[i] = (unsigned int)x;     
    }
    
    for(i=0; i<2; i++)
    {
        if(dianciValue[i]<=5)    dianciValue[i] = 0;                      
    }
}
	
	
/**=================================================================================
  *
  * 电磁数据处理                2012-05-7
  *
  *=================================================================================
  */

void DirectionVoltageSigma(void)
{		
	g_fLeftVoltageSigma += dianciValue[0];
	g_fRightVoltageSigma += dianciValue[1];		
}
	

/**=================================================================================
  *
  * 角度的计算                    2012-03-23
  *
  *=================================================================================
  */

void AngleCalculate() 
{	
    g_fGravityAngle = AccValue * GRAVITY_ANGLE_RATIO * 2.8444;
	g_fGyroscopeAngleSpeed = gyroValue * GYROSCOPE_ANGLE_RATIO * 2.8444;	
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
	g_fGyroscopeAngleIntegral = ((0.995)*((g_fGyroscopeAngleIntegral) + 
	(g_fGyroscopeAngleSpeed * GYROSCOPE_ANGLE_SIGMA_FREQUENCY)) + (0.005)*(g_fGravityAngle));		
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



