//**** MiniSumo V1 Software ****//
// This program for testing miniSumo with sensors
// Author: Mustafa Tosun
// Datae: 04/06/2014
//

// Pre-processor Directives Section
#include "motor_driver.h"
// Global Declarations Section

// Subroutines Section

// MAIN: Mandatory routine for a C program to be executable
void main(){
     motorsInit(void);

     while(1){
     // test code
        setSpeeds(0,0);
        delay_ms(2000);
        setSpeeds(-400,-400);
        delay_ms(2000);
        setSpeeds(200,-200);
        delay_ms(2000);
        setSpeeds(-400,400);
        delay_ms(2000);
        setSpeeds(200,200);
        delay_ms(2000);
     }
}