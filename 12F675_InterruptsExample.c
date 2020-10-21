/*
 * File:   newmain.c
 * Author: user
 *
 * Created on 22 September, 2020, 10:49 PM
 */
#pragma config FOSC = INTRCCLK  // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // GP3/MCLR pin function select (GP3/MCLR pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#define _XTAL_FREQ 4000000
#include <xc.h>

void __interrupt() blink(void){         //interrupt function
    if(INTF){  //check if interrupt flag (int0) is 1
        GPIO5=1; //blink rd1 once 
        __delay_ms(1000);
        GPIO5=0;
        INTF=0;  //clear the flag
    }
}

void main(void) {
    GIE=1; //global interrupts enable   // these 4 bits are of INTCON
    INTEDG=0;  //falling edge
    INTE=1; //enable int0
    //PEIE=1; //peripheral interrupts enable       
    
    TRISIO0=0; //led1 out
    TRISIO5=0; //led2 out
    GPIO5=0;  //led off at main
    ANS2=0;//Setting INT(GPIO2) as special function pin,As per note given for setting ansel register
    while(1){     //normal operation , blink RB1 at 1sec delay
        GPIO0=1;
        __delay_ms(1000);
        GPIO0=0;
        __delay_ms(1000);
    }
    return;
}   
