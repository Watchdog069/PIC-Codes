/* PIC16F877A
 * File:   newmain.c
 * Author: user
 * Datasheet: https://ww1.microchip.com/downloads/en/devicedoc/39582b.pdf 
 * Created on 13 September, 2020, 1:50 PM
 */
// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
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

void setupADC(int x){
    ADCON1 |= (1<<ADFM);  //right justified , Fosc/2 selected, PCFG bits set to 0000
    ADCON0 |= (1<<ADON);    //switch on the ADC  
    switch(x)
    {
        case 0:
            ADCON0 |= 0x00;
            break;
        case 1:
            ADCON0 |= (1<<CHS0);
            break;
        case 2:    
            ADCON0 |= (1<<CHS1);
            break;
        case 3:    
            ADCON0 |= (1<<CHS1)|(1<<CHS0);
            break;
        case 4:    
            ADCON0 |= (1<<CHS2);
            break; 
        case 5:    
            ADCON0 |= (1<<CHS2)|(1<<CHS0);
            break;   
        case 6:    
            ADCON0 |= (1<<CHS2)|(1<<CHS1);
            break;
        case 7:    
            ADCON0 |= (1<<CHS2)|(1<<CHS1)|(1<<CHS0);
            break;
        default:
            ADCON0 |= 0x00;    
    }        
}

int calculateADC(){
    GO_nDONE = 1; //Initializes A/D Conversion
    while(GO_nDONE); //Wait for A/D Conversion to complete;
    int val = (ADRESH<<8)+ADRESL;
    return val;
}

void main(void) {
    TRISB1=0;//o/p
    TRISD1=0;//o/p
    setupADC(0);
    if (calculateADC()>500){
        RB1=1;
        RD1=0;
    }
    else{
        RB1=0;
        RD1=1;
    }
    __delay_ms(100);  
    return;
}
