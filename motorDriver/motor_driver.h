/* ****MOTOR_DRIVER - A simple library to control DC Motors

Hardware Setup:

5V       <--->  5V
GND      <--->  GND
M1       <--->  RC0
M2       <--->  RC3
M3       <--->  RC4
M4       <--->  RC5
MEN1     <--->  RC1(CCP2)
MEN2     <--->  RC2(CCP2)


*/

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

// Subroutine function prototypes
void motorsInit(unsigned char); // Initialize Motor I/O ports
void setM1Speed(int speed); // Set speed for M1.
void setM2Speed(int speed); // Set speed for M2.
void setMotors(int m1Speed, int m2Speed); // Set speed for both M1 and M2.

#endif