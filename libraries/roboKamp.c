/* ****ROBOKAMP-2014 - MiniSumo Libraries
   This library designed for robokamp 2014 miniSumo robot circuit
   Author: Mustafa Tosun
   Datae: 18/06/2014
*/
#include <stdint.h>
#include "roboKamp.h"
#include "roboUART.h"

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

uint8_t checkFlag;
uint16_t zaman;

// *****************************************************************************
// PORT INITIALIZATION
// *****************************************************************************

// Initialize PORTA, PORTB, PORTC and others
// Input:  none
// Output: none
void portInit( void ){
     PORTA = 0x00;
     PORTB = 0x00;
     PORTC = 0x00;
     TRISA = 0x13;
     TRISB = 0xFF;
     TRISC = 0x10;

     ADCON0 = 0x09;
     ADCON1 = 0x84;

     timer0Init(void);
     timer1Init(void);
 // For buzzerKontrol function
     //PWM2_Init( 15700 ); // set PWM2 to 20Khz
     //PWM2_Start(); // start PWM1*/
     //PWM2_Set_Duty( 0 );
}

// *****************************************************************************
// Motor Control Library
// *****************************************************************************

// Initialize Motors and PWM
// Input:  none
// Output: none
void motorsInit( unsigned char value ){
     m1Port = 0; m2Port = 0;
     m3Port = 0; m4Port = 0;
     m1En = 0; m2En = 0;

     if( value ){
        PWM1_Init( 15700 ); // set PWM1 to 20Khz
        PWM2_Init( 15700 ); // set PWM2 to 20Khz
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
void setM1Speed( int speed ){
      unsigned char reverse = 0; // direction variable

     if ( speed < 0 ){
        speed = -speed;  // Make speed a positive quantity
        reverse = 1;  // Preserve the direction
     }
     if ( speed > 400 )  // Max PWM dutycycle
        speed = 400;

     PWM2_Set_Duty( speed * 51 / 80 ); // mapping 400 to 255

     if( speed == 0 ){
        m1Port = 0; m2Port = 0;
     } else if( reverse ){
        m1Port = 0; m2Port = 1;
     } else{
        m1Port = 1; m2Port = 0;
     }
}

// set motor2 speed and direction
// Input:  motor speed (between -400 and 400)
// Output: none
void setM2Speed( int speed ){
      unsigned char reverse = 0; // direction variable

     if ( speed < 0 ){
        speed = -speed;  // Make speed a positive quantity
        reverse = 1;  // Preserve the direction
     }
     if ( speed > 400 )  // Max PWM dutycycle
        speed = 400;

     PWM1_Set_Duty( speed * 51 / 80 ); // mapping 400 to 255

     if( speed == 0 ){
        m3Port = 0; m4Port = 0;
     }else if( reverse ){
        m3Port = 0; m4Port = 1;
     } else{
        m3Port = 1; m4Port = 0;
     }
}

// set both motors speed and direction
// Input:  motor speed (between -400 and 400)
// Output: none
void setMotors( int m1Speed, int m2Speed ){
     setM1Speed( m1Speed );
     setM2Speed( m2Speed );
}

// *****************************************************************************
// Timer Initializations
// *****************************************************************************

// Timer1 for ultrasonic sensor reading
// Input:  none
// Output: none
void timer1Init( void ){
     // T0CON (Prescale = 1:4 | Source = CLKO (Fosc/4))
     T1CON.B0 = 0; // TMR1ON
     T1CON.B1 = 0; // TMR1CS
     T1CON.B2 = 0; // ~T1SYNC
     T1CON.B3 = 0; // T1OSCEN
     T1CON.B4 = 0; // T1CKPS0
     T1CON.B5 = 1; // T1CKPS1
     T1CON.B6 = 0; // Unimplemented
     T1CON.B7 = 0; // RD16

     PIE1.B0 = 1;
     PIR1.B0 = 0;
}

// Timer0 for waiting in program for tactics
// Input:  none
// Output: none
void timer0Init( void ){
     // T0CON (Prescale = 1:256 | Source = CLKO (Fosc/4)) 76 1 sec
     T0CON.B0 = 1; // T0PS0
     T0CON.B1 = 1; // T0PS1
     T0CON.B2 = 1; // T0PS2
     T0CON.B3 = 0; // PSA
     T0CON.B4 = 0; // T0SE
     T0CON.B5 = 0; // T0CS
     T0CON.B6 = 1; // T08BIT
     T0CON.B7 = 1; // TMR0ON
}

//******************************************************************************
// READ DIP SWITCHES &&& BUZZER FUNCTIONS
// *****************************************************************************

uint8_t dipSwitchOku( uint8_t _dipSwitch ){
   return ( _dipSwitch == 1 ) ? 1 : 0;
}

void buzzerKontrol( uint8_t _DutyCycle ){
   PWM2_Set_Duty( ( _DutyCycle <= 255 && _DutyCycle >=0 ) ? ( _DutyCycle*51/20 ) : 255 );
}

uint8_t tachOku( uint8_t _tach ){
   return ( _tach == 1 ) ? 1 : 0;
}

//******************************************************************************
// SENSORS PART OF LIBRARY
// *****************************************************************************

// Sharp sensor reading function
// Input:  A0,A1,A3 ( which sensor read? )
// Output: 1 or 0 ( with respect to define distance )
uint8_t sharpSensorOku( uint8_t _sensorPin ){
   ADCON0 |= ( _sensorPin == sharp_1 ) ? 0x00 : ( ( _sensorPin == sharp_2 ) ? 0x08 : 0x00 ) );
   ADCON0.B2 = 1; // GO
   while( ADCON0.B2 ) continue; //nDONE
   return ( ( ( ADRESH<<8 ) + ADRESL ) < 200 ) ? 1 : 0;
}

uint8_t sharpSensorAnalogOku( uint8_t _sensorPin ){
   ADCON0 |= ( _sensorPin == sharp_1 ) ? 0x00 : ( ( _sensorPin == sharp_2 ) ? 0x08 : 0x00 ) );
   ADCON0.B2 = 1; // GO
   while( ADCON0.B2 ) continue; //nDONE
   return ( ( ( ADRESH<<8 ) + ADRESL ) < 200 ) ? ( ( ADRESH<<8 ) + ADRESL ) : 40;
}

// Ultrasonic sensor reading function
// Input:  distance value between 0 to 400 cm
// Output: 1 or 0 ( with respect to input distance )
uint8_t ultrasonicSensorOku( uint8_t _max_distance ){
   unsigned long distance_cm = 0;
   uint16_t TMR = 0;

   TMR1H = 0;
   TMR1L = 0;

   checkFlag = 1; // for
   // Send trig signal
   trig = 0;
   delay_us(2);
   trig = 1;
   delay_us(10);
   trig = 0;

   // Start to read Ultrasonic sensor
   while(echo == 0);
   enableTMR1ON = 1;
   while(echo == 1 && checkFlag == 1);
   enableTMR1ON = 0;

   TMR = (uint16_t) TMR1H << 8;
   TMR = TMR + TMR1L;

   distance_cm = ( ( TMR/10 ) * 8 )/58;

   return ( distance_cm <= _max_distance && distance_cm > 0 ) ? 1 : 0;
}

uint8_t ultrasonicSensorAnalogOku( uint8_t _max_distance ){
   unsigned long distance_cm = 0;
   uint16_t TMR = 0;

   TMR1H = 0;
   TMR1L = 0;

   checkFlag = 1; // for
   // Send trig signal
   trig = 0;
   delay_us( 2 );
   trig = 1;
   delay_us( 10 );
   trig = 0;

   // Start to read Ultrasonic sensor
   while( echo == 0 );
   enableTMR1ON = 1;
   while( echo == 1 && checkFlag == 1 );
   enableTMR1ON = 0;

   TMR = ( uint16_t ) TMR1H << 8;
   TMR = TMR + TMR1L;

   distance_cm = ( ( TMR/10 ) * 8 )/58;

   return ( distance_cm <= _max_distance ) ? distance_cm : 40;
}

// CN70 sensor reading function
// Input:  B00, B11, B22, B33
// Output: 1 or 0
uint8_t cn70SensorOku( uint8_t _cn70 ){
   return ( _cn70 == 1 ) ? 1 : 0;
}

// MZ80 digital distance sensor reading function
// Input: B66, B77
// Output: 1 or 0
uint8_t mz80SensorOku( uint8_t _mz80 ){
     return ( _mz80 == 1 ) ? 0 : 1;
}

// INTERRUPT FUNCTION: DON'T TOUCH THIS FUNCTION !!!
void interrupt( void ){
  if(RCIE && RCIF){
    roboUARTHandleRxInt();
  } else if( timer1InterruptFlag == 1 ){ // TMR1 Interrupt
    checkFlag = 0;
    timer1InterruptFlag = 0;
  } else if( timer0InterruptFlag == 1 ){ // TMR0 Interrupt
    zaman++;
    timer0InterruptFlag = 0;
  }
}
