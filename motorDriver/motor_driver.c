//****MOTOR_DRIVER - A simple library to control DC Motors
// This program for control of miniSumo robot
// Author: Mustafa Tosun
// Datae: 05/06/2014
//

// Pre-processor Directives Section
#include "motor_driver.h"

#define m1Tris TRISC.B0
#define m2Tris TRISC.B3
#define m3Tris TRISC.B4
#define m4Tris TRISC.B5
#define m1EnTris TRISC.B1
#define m2EnTris TRISC.B2
#define m1Port PORTC.B0
#define m2Port PORTC.B3
#define m3Port PORTC.B4
#define m4Port PORTC.B5
#define m1En   PORTC.B1
#define m2En   PORTC.B2

// Initialize Motors and PWM
// Input:  none
// Output: none
void motorsInit(unsigned char value){
     m1Tris = 0; m2Tris= 0;
     m3Tris = 0; m4Tris = 0;
     m1EnTris = 0; m2EnTris = 0;
     m1Port = 0; m2Port = 0;
     m3Port = 0; m4Port = 0;
     m1En = 0; m2En = 0;
     
     if(value){
        PWM1_Init(20000); // set PWM1 to 20Khz
        PWM2_Init(20000); // set PWM2 to 20Khz
        PWM1_Start(); // start PWM1
        PWM2_Start(); // start PWM2
     } else {
        m1En = 1;
        m2En = 1;
     }
}

// set motor1 speed and direction
// Input:  motor speed (between -400 and 400)
// Output: none
void setM1Speed(int speed){
      unsigned char reverse = 0; // direction variable

     if (speed < 0){
        speed = -speed;  // Make speed a positive quantity
        reverse = 1;  // Preserve the direction
     }
     if (speed > 400)  // Max PWM dutycycle
        speed = 400;
     
     PWM2_Set_Duty(speed * 51 / 80); // mapping 400 to 255
     
     if(speed == 0){
        m1Port = 0; m2Port = 0;
     } else if(reverse){
        m1Port = 0; m2Port = 1;
     } else{
        m1Port = 1; m2Port = 0;
     }
}

// set motor2 speed and direction
// Input:  motor speed (between -400 and 400)
// Output: none
void setM2Speed(int speed){
      unsigned char reverse = 0; // direction variable

     if (speed < 0){
        speed = -speed;  // Make speed a positive quantity
        reverse = 1;  // Preserve the direction
     }
     if (speed > 400)  // Max PWM dutycycle
        speed = 400;

     PWM1_Set_Duty(speed * 51 / 80); // mapping 400 to 255

     if(speed == 0){
        m3Port = 0; m4Port = 0;
     }else if(reverse){
        m3Port = 0; m4Port = 1;
     } else{
        m3Port = 1; m4Port = 0;
     }
}

// set both motors speed and direction
// Input:  motor speed (between -400 and 400)
// Output: none
void setMotors(int m1Speed, int m2Speed){
     setM1Speed(m1Speed);
     setM2Speed(m2Speed);
}