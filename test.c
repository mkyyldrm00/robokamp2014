/* 
   DIP1 -> RB5
   DIP2 -> RB4
   LED1 -> RC7
   LED2 -> RC6
*/
// predefined
#include <stdint.h>

#define DIP1 PORTB.RB5
#define DIP2 PORTB.RB4
#define LED1 PORTC.RC7
#define LED2 PORTC.RC6
#define BUT1 PORTA.RA4

#define tmr0IEnable INTCON.TMR0IE = 1
#define tmr0IDisable INTCON.TMR0IE = 0
#define globalINTEnable INTCON.GIE = 1
#define globalINTDisable INTCON.GIE = 0
#define tmr0IFlag INTCON.TMR0IF

// Global definitions
uint8_t zaman = 0;
uint8_t yon   = 0;

// subroutines
void portInit( void ){
   TRISA = 0x10; // RA4 input
   TRISB = 0x30; // B4, B5 input
   TRISC = 0x00;
   ADCON1 = 0x04;
   PORTA = 0x00;
   PORTB = 0x00;
   PORTC = 0x00;
}

void timer0Init( void ){
   T0CON.TMR0ON = 1;
   T0CON.T08BIT = 1;
   T0CON.T0CS = 0;
   T0CON.T0SE = 0;
   T0CON.PSA = 1;
   T0CON.T0PS2 = 1;
   T0CON.T0PS1 = 1;
   T0CON.T0PS0 = 1;
}

void interrupt(){
   if( tmr0IFlag == 1 ){
      zaman++;
      tmr0IFlag = 0;
   }
}

void main() {
     portInit();
     timer0Init();
     
     tmr0IDisable;
     globalINTDisable;
     
     LED1 = 1;
     LED2 = 1;
     delay_ms(4000);
     LED1 = 0;
     
     tmr0IEnable;
     globalINTEnable;
     
     while( zaman < 77 ){
        yon = ( DIP1 == 1 ) ? 1 : 0;
     }
     
     //PWM2_Init( 15700 );
     while(1){
       /*if( !BUT1 ){
           PWM2_Start();
           PWM2_Set_Duty( 255 );
           delay_ms( 1000 );
           PWM2_Init( 10000 );
           delay_ms( 1000 );
           PWM2_Init( 8000 );
           delay_ms( 1000 );
       } else{
           PWM2_Stop();
       }*/
       /*delay_ms(100);
       LED1 = ( DIP1 == 1 ) ? 1 : 0;
       LED2 = ( DIP2 == 1 ) ? 1 : 0; */
     }
}
