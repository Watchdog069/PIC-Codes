/*
 * File:   newmain.c
 * Author: user
 *
 * Created on 24 September, 2020, 11:38 AM
 */
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (LP oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF         // Data EEPROM Memory Code Protection bit (Data EEPROM code-protected)
#pragma config WRT = HALF       // Flash Program Memory Write Enable bits (0000h to 0FFFh write-protected; 1000h to 1FFFh may be written to by EECON control)
#pragma config CP = OFF          // Flash Program Memory Code Protection bit (All program memory code-protected)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 20000000
#include <xc.h>

void __interrupt() blink(void){         //interrupt function
    if(INTF){  //check if interrupt flag (int0) is 1
        RD1=1; //blink rd1 once 
        __delay_ms(1000);
        RD1=0;
        INTF=0;  //clear the flag
    }
    if(CMIF){   //check if comparator interrupt flag is 1
        for(int i=0;i<5;i++){  //blink rd1 5 times
            RD1=1;
            __delay_ms(100);
            RD1=0;
            __delay_ms(100);
        }
        CMIF=0; //clear the flag
    }
}


void main(void) {
    GIE=1; //global interrupts enable   // these 4 bits are of INTCON
    INTEDG=0;  //falling edge
    INTE=1; //enable int0
    PEIE=1; //peripheral interrupts enable       
    CMIE=1;//comaparator intr enable bit  //inside PIE2
    
    TRISB1=0; //led out
    TRISD1=0; //led out
    TRISA0=1; //LDR at Vin- for comparator
    TRISA3=1; //2.5v reference at Vin+ for comparator
    
    RD1=0;  //led off at main
    while(1){     //normal operation , blink RB1 at 1sec delay
        CMCON|=(1<<CM1); //independent comparator (010) 
        RB1=1;
        __delay_ms(1000);
        RB1=0;
        __delay_ms(1000);
        CM0=0;
        CMCON &= ~(1<<CM0); //resetting for reading again
    }
    return;
}
