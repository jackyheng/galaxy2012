/**================================================================================
  *
  * sensor.h                      by QI_ZI_HENG 2012-03-19
  *
  *================================================================================
  */
 
#ifndef __SENSOR__H
#define __SENSOR__H
//-------------------------------------------------------------------------------

#define channal                  4                    //一共要读的AD端口数
#define ADC_Counter              20                   //计算平均数的次数
#define ACCmax                   3045//3020
#define ACCmin                   1090//1020
#define GRAVITY_ANGLE_RATIO                180/(ACCmax - ACCmin)             //180/(ACCmax - ACCmin)
#define GYROSCOPE_ANGLE_RATIO              0.2//0.18                           //（3300/4096）/（0.67*9.1) = 0.132
#define GYROSCOPE_ANGLE_SIGMA_FREQUENCY    0.005                    //陀螺仪的测量周期
#define GRAVITY_ADJUST_TIME_CONSTANT       2
#define gyroOffset               1448//2651//2617                           //陀螺仪静止时的输出值
#define AccOffset                2025//2049                           //加速度静止时的输出值
#define RightOffset              92
#define LeftOffset               108
//-------------------------------------------------------------------------------


extern unsigned int nInputVoltage[];
extern float AccValue;
extern float gyroValue;
extern int VOLTAGE_LEFT;
extern int VOLTAGE_RIGHT;
extern unsigned int sensorValue[channal];
extern unsigned int sensorZero[channal];
extern float g_fGravityAngle;                                   
extern float g_fGyroscopeAngleIntegral; 
extern float g_fGyroscopeAngleSpeed;
extern float ANGLE_CONTROL_P;
extern float ANGLE_CONTROL_D;
extern float  g_fAngleControlOut;
//-------------------------------------------------------------------------------


void updataSensor();
void AngleCalculate();
void complementaryFilter();
void AngleControl(void);
void DirectionVoltageSigma(void);
//-------------------------------------------------------------------------------
#endif
