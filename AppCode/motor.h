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

#define MOTOR_OUT_DEAD_VAL              40                     //电机死区电压97
#define CAR_SPEED_CONSTANT              0.1                    //转速比例系数，码盘为100码，计数周期为100毫秒
#define SPEED_CONTROL_COUNT				20    
#define SPEED_CONTROL_PERIOD            100     //SPEED_CONTROL_COUNT * 5
#define SPEED_CONTROL_OUT_MAX           10
#define SPEED_CONTROL_OUT_MIN           -10 
#define DIRECTION_CONTROL_PERIOD        10  
#define DIRECTION_CONTROL_COUNT         2
#define speedNeed1                      360
#define speedNeed2                      380
#define speedNeed3                      400
//----------------------------------------------------------------

void L_Wheel_Forward(word ratio);
void L_Wheel_Back(word ratio);
void R_Wheel_Forward(word ratio);
void R_Wheel_Back(word ratio);
byte motorOutput(float fLeftVoltage, float fRightVoltage);
void motorControl();
void speedControl(void);
void speedControlOutput(void);
void GetMotorPulse(void);
void DirectionControl(void);
void DirectionControlOutput(void);
//------------------------------------------------------------------

extern float speedNeed;
extern bool speedControlFlag;
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
extern float g_fDirectionControlOutNew;
extern float g_nLeftMotorPulseSigma;
extern float g_nRightMotorPulseSigma;
extern float DIR_CONTROL_P;
extern float DIR_CONTROL_D;
extern bool speedStarEndFlag;
extern int nLeft, nRight;
//------------------------------------------------------------------


#endif

