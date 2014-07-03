/*
   DIP1 -> RB5
   DIP2 -> RB4
   LED1 -> RC7
   LED2 -> RC6
*/
// predefined
#include <stdint.h>
#include "roboKamp.h"

#define tmr0IEnable INTCON.TMR0IE = 1
#define tmr0IDisable INTCON.TMR0IE = 0
#define globalINTEnable INTCON.GIE = 1
#define globalINTDisable INTCON.GIE = 0
#define tmr0IFlag INTCON.TMR0IF

// Global definitions
uint8_t yon   = 0;

void solaDon( void ){
  tmr0IEnable;
  globalINTEnable;
  
  while( zaman < 25 && mz80SensorOku( mz80_1 ) == 0 ){
     setMotors( -200, 200 );
  }
  
  tmr0IDisable;
  globalINTDisable;
  zaman = 0;
}

void main() {
     portInit();
     motorsInit( 1 );

     tmr0IDisable;
     globalINTDisable;

     LED_1 = 1;
     LED_2 = 1;
     delay_ms(5000);
     LED_1 = 0;

     while(1){
       if( mz80SensorOku( mz80_1 ) == 1 ){
         // kodunuz
       } else{
         solaDon();
         
       }
     }
}
