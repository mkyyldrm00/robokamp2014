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

void main() {
     portInit();
     timer0Init();

     tmr0IDisable;
     globalINTDisable;

     LED_1 = 1;
     LED_2 = 1;
     delay_ms(4000);
     LED_1 = 0;
     
     tmr0IEnable;
     globalINTEnable;

     while( zaman < 77 ){
        yon = ( DIP_1 == 1 ) ? 1 : 0;
     }
     
     while(1){

     }
}