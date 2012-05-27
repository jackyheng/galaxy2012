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
float AccValue;                                //���ٶȼ�ȥ��ֹ���õ�����
float gyroValue;                               //���ٶȼ�ȥ��ֹ���õ�����
float g_fGravityAngle;                         //���ٶȼ����ĽǶ�
float g_fGyroscopeAngleSpeed;                  //�����ǵĽ��ٶ�
float g_fGyroscopeAngleIntegral;               //�����ǻ��ֺ�ĽǶ�
float fDeltaValue;
float g_fCarAngle;
float ANGLE_CONTROL_P = 38;                     //�Ƕȿ��Ʊ���
float ANGLE_CONTROL_D = 0.1;//0.37;                     //�Ƕȿ���΢��
float g_fAngleControlOut;
int VOLTAGE_LEFT;
int VOLTAGE_RIGHT;

extern float g_fLeftVoltageSigma;
extern float g_fRightVoltageSigma;
//---------------------------------------------------------------------------------


/**=================================================================================
  *
  * ����ADC�ľ�ֵֹ              2012-03-23
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
  * ���������Ǻͼ��ٶ�ADC������                2012-03-23
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
  * ������ݴ���                2012-05-7
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
  * �Ƕȵļ���                    2012-03-23
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
  * �����˲�                      2012-03-26
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
  * �Ƕȵ�PDֵ����                2012-03-28
  *
  *=================================================================================
  */

void AngleControl() 
{
	float fValue;	

	fValue = (g_fGyroscopeAngleIntegral * ANGLE_CONTROL_P + g_fGyroscopeAngleSpeed * ANGLE_CONTROL_D); 
	         
	g_fAngleControlOut = fValue;	
}





