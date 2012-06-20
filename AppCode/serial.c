/**=================================================================================
  *
  * serial.c               by QI_ZI_HENG 2012-03-28
  *
  *=================================================================================
  */
  
  
#include "serial.h"
#include "sensor.h"
#include "AS1.h"
#include "PE_Types.h"
#include "motor.h"
#include "Bit1.h"
//----------------------------------------------------------------------------------

int debugWord[2];
extern unsigned char receive[15];
extern byte pwmval;
extern unsigned int speedL,speedR;
extern float SUB,ADD;
extern int   RIGHT,LEFT;
extern unsigned int sensorValue[channal];
//----------------------------------------------------------------------------------


/**=================================================================================
  *
  * 发送传感器的数据                2012-03-30
  *
  *=================================================================================
  */
    
void sendData()
{
    debugWord[0] = (int)(g_fGravityAngle * 3);                 //把数据放大，方便观察波形
    debugWord[1] = (int)(g_fGyroscopeAngleIntegral * 3);
   /* SendNum(debugWord[0]);
    AS1_SendChar(' ');
    SendNum(debugWord[1]);  */   
  


   

    /*SendNum((int)(VOLTAGE_LEFT));
    AS1_SendChar(' '); 
    
    SendNum((int)(VOLTAGE_RIGHT));
    AS1_SendChar(' ');      



    SendNum((int)LEFT);
    AS1_SendChar(' '); 
    
    SendNum((int)RIGHT);
    AS1_SendChar(' '); */     


    //SendNum((int)g_fDirectionControlOutNew);
    //AS1_SendChar(' ');
    
    //SendNum((int)(ANGLE_CONTROL_P*100));
    //AS1_SendChar(' '); 
    
    //SendNum((int)(ANGLE_CONTROL_D*100));
    //AS1_SendChar(' ');
              
//    SendNum((int)(speedL)); 
//    AS1_SendChar(' ');

  
/*    SendNum((int)(speedControl()));
    AS1_SendChar(' '); 
    
    SendNum((int)(g_fspeedControlOut));
    AS1_SendChar(' ');      
  

    SendNum((int)(CAR_SPEED_SET));
    AS1_SendChar(' '); 
*/      
   
    //SendNum((int)(SPEED_CONTROL_P*100));
   //AS1_SendChar(' ');     
    //SendNum((int)(SPEED_CONTROL_I*100));
 //   AS1_SendChar(' ');  
 

   // SendNum((int)(sensorValue[2]));
   // AS1_SendChar(' '); 
    
    //SendNum((int)(sensorValue[3]));
    //AS1_SendChar(' '); 

    //SendNum((int)(sensorZero[1]));
    //AS1_SendChar(' '); 
    
    //SendNum((int)(sensorValue[1]));



 
    SendNum((int)DIR_CONTROL_P);
    //AS1_SendChar(' ');    
    //SendNum((int)DIR_CONTROL_D);
      //SendNum((int)LEFT);
      //AS1_SendChar(' ');  
    
      //SendNum((int)RIGHT);
   // AS1_SendChar(' '); 
    
      //SendNum((int)VOLTAGE_LEFT);
      //AS1_SendChar(' '); 
      //SendNum((int)VOLTAGE_RIGHT);
    
        
    //SendNum((int)ADD);
   // AS1_SendChar(' ');
        
    //SendNum((int)sensorValue[2]);
    //AS1_SendChar(' ');
     
   // SendNum((int)sensorValue[3]);
//    AS1_SendChar(' ');       
        
    AS1_SendChar(0x0d);                       
    AS1_SendChar(0x0a);

}


/**=================================================================================
  *
  * 发送整数               2012-03-30
  *
  *=================================================================================
  */
  
void SendNum(int num)
{  
	unsigned char i,temp[5];
	
	if(num<0)
    {
      AS1_SendChar('-');
      num=0-num;    	
    }
    
	temp[0]=(unsigned char)(num/10000);
	temp[1]=(unsigned char)(num%10000/1000);
	temp[2]=(unsigned char)(num%1000/100);
	temp[3]=(unsigned char)(num%100/10);
	temp[4]=(unsigned char)(num%10);
	
	
	    if(temp[0]==0)
	    {
	      if(temp[1]==0)
	      {
	        if(temp[2]==0)
	        {
	        	if(temp[3]==0)
	        	{
	        		AS1_SendChar((unsigned char)(temp[4]+0x30));
	        	}
	        	else
	        	{
	        		AS1_SendChar((unsigned char)(temp[3]+0x30));
                    AS1_SendChar((unsigned char)(temp[4]+0x30));
	        	}
	        }
	        else
	        {
	      	  for(i=2;i<5;i++)
	      	  {
	      	    AS1_SendChar((unsigned char)(temp[i]+0x30));
	      	  }
	        }	        
	      }
	      else
	      {
	      	for(i=1;i<5;i++)
	      	{
	      	  AS1_SendChar((unsigned char)(temp[i]+0x30));
	      	}
	      }
	    	
	    }
	    else
	    {
	      for(i=0;i<5;i++)
	      {
	      	AS1_SendChar((unsigned char)(temp[i]+0x30));
	      }
	    }	
}


/**=================================================================================
  *
  * 接收数据               2012-03-30
  *
  *=================================================================================
  */
  
void receiveData()
{
     double P,D;
   
     P=(receive[0]-0x30)*100;
     P=P+(receive[1]-0x30)*10;
     P=P+receive[2]-0x30;
     P=P+(receive[4]-0x30)*0.1;
     P=P+(receive[5]-0x30)*0.01;
     

     /*P=(receive[0]-0x30)*10;
     P=P+receive[1]-0x30;
     P=P+(receive[3]-0x30)*0.1;
     P=P+(receive[4]-0x30)*0.01;
     P=P+(receive[5]-0x30)*0.001;      */
     
     D=(receive[7]-0x30)*10;
     D=D+receive[8]-0x30;
     D=D+(receive[10]-0x30)*0.1;
     D=D+(receive[11]-0x30)*0.01;
     D=D+(receive[12]-0x30)*0.001; 
     
    
    /* 
     if(P>99)
       P=0;
     if(D>99)
       D=0;
     */    
     
     //ANGLE_CONTROL_P = P;
     //ANGLE_CONTROL_D = D; 
     //SPEED_CONTROL_P=P;
     //SPEED_CONTROL_I=D; 
     
       DIR_CONTROL_P=P;
      // DIR_CONTROL_D=D;
//     CAR_SPEED_SET=-D; 
    
}