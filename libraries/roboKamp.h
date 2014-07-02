/* ****ROBOKAMP-2014 - MiniSumo Libraries
   This library designed for robokamp 2014 miniSumo robot circuit
   Author: Mustafa Tosun
   Datae: 18/06/2014
*/
#ifndef ROBOKAMP_H
#define ROBOKAMP_H

// Sharp Analog Sensors
#define sharp_1 0
#define sharp_2 1
// CN70 Sensors
#define cn70_1 PORTB.RB0
#define cn70_2 PORTB.RB1
#define cn70_3 PORTB.RB2
#define cn70_4 PORTB.RB3
// DIP Switch
#define DIP_1 PORTB.RB5
#define DIP_2 PORTB.RB4
// MZ80 Sensors or Sharp Digital Sensors
#define mz80_1 PORTB.RB7
#define mz80_2 PORTB.RB6
// TACH
#define BUT_1 PORTA.RA4
// LEDs
#define LED_1 PORTC.RC7
#define LED_2 PORTC.RC6
// Motors
#define m1Port PORTC.RC0
#define m2Port PORTC.RC3
#define m3Port PORTA.RA2
#define m4Port PORTA.RA5
#define m1En   PORTC.RC1
#define m2En   PORTC.RC2

#define trig PORTC.RC5
#define echo PORTC.RC4

#define RCIE PIE1.RCIE
#define RCIF PIR1.RCIF

#define enableTMR1ON T1CON.B0
#define timer0InterruptFlag INTCON.B2
#define timer1InterruptFlag PIR1.B0

extern uint8_t checkFlag;
extern uint16_t zaman = 0;

void portInit( void );
// Subroutine function prototypes
void motorsInit( unsigned char ); // Initialize Motor I/O ports
void setM1Speed( int speed ); // Set speed for M1.
void setM2Speed( int speed ); // Set speed for M2.
void setMotors( int m1Speed, int m2Speed ); // Set speed for both M1 and M2.

void timer0Init( void );
void timer1Init( void );

uint8_t dipSwitchOku( uint8_t _dipSwitch );
void buzzerKontrol( uint8_t _DutyCycle );
uint8_t tachOku( uint8_t _tach );

uint8_t sharpSensorOku( uint8_t _sensorPin );
//uint8_t ultrasonicSensorOku( uint8_t _max_distance );
//uint8_t ultrasonicSensorAnalogOku( uint8_t _max_distance );
uint8_t cn70SensorOku( uint8_t _cn70 );
uint8_t mz80SensorOku( uint8_t _mz80 );

void interrupt( void );

#endif