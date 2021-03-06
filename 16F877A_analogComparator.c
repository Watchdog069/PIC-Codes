/*
 * File:   newmain.c
 * Author: user
 *
 * Created on 17 September, 2020, 8:59 PM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 20000000
#include <xc.h>

void main(void) {
    TRISD1=0;  //led outputs
    TRISB1=0;
    TRISA0=1;  //a0 ldr input at -
    TRISA3=1;  //a3 input for 2.5v at +
    while(1){
        CM2=0; //independent comparator (010)
        CM1=1;
        CM0=0;
        //C1INV=1;
        if(C1OUT){
            RB1=0;
            RD1=1;
        }
        else{
            RB1=1;
            RD1=0;
        }
        __delay_ms(100);
    }
    return;
}
