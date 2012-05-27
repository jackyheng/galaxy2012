/**=================================================================================
  *
  * motor.h               2012-03-30
  *
  *=================================================================================
  */

#ifndef __MOTOR_H
#define __MOTOR_H
//------------------------------------------------------------------

#include "PWMC1.h"
#include "PE_Types.h"
//------------------------------------------------------------------

#define MOTOR_OUT_DEAD_VAL              40                     //���������ѹ97
#define CAR_SPEED_CONSTANT              0.1                    //ת�ٱ���ϵ��������Ϊ100�룬��������Ϊ100����
#define SPEED_CONTROL_COUNT				20    
#define SPEED_CONTROL_PERIOD            100     //SPEED_CONTROL_COUNT * 5
#define SPEED_CONTROL_OUT_MAX           10
#define SPEED_CONTROL_OUT_MIN           -10 
#define DIRECTION_CONTROL_PERIOD        10  

#define DIRECTION_CONTROL_COUNT         2

void L_Wheel_Forward(word ratio);
void L_Wheel_Back(word ratio);
void R_Wheel_Forward(word ratio);
void R_Wheel_Back(word ratio);
byte motorOutput(float fLeftVoltage, float fRightVoltage);
void motorControl();
float speedControl(void);
void speedControlOutput(void);
void GetMotorPulse(void);
void DirectionControl(void);
void DirectionControlOutput(void);



extern float SPEED_CONTROL_P;
extern float SPEED_CONTROL_I;
extern float g_fspeedControlOutNew;
extern float g_fspeedControlOutOld;
extern float g_nspeedControPeriod;
extern float g_fspeedControlOut;
extern float CAR_SPEED_SET;
extern float g_nDirectionControlPeriod;
extern float g_fspeedControlIntegral;
extern float g_fDirectionControlOut;

extern float DIR_CONTROL_P;
extern float DIR_CONTROL_D;
//------------------------------------------------------------------


#endif
