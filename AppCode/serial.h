/**=================================================================================
  *
  * serial.h               by QI_ZI_HENG 2012-03-28
  *
  *=================================================================================
  */
  
#ifndef __SERIAL__H
#define __SERIAL__H
//----------------------------------------------------------------------------------

extern unsigned char receive[15];
//----------------------------------------------------------------------------------

void sendData();
void receiveData();
void SendNum(int num);
//----------------------------------------------------------------------------------

#endif