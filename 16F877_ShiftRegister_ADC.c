/*
 * File:   newmain.c
 * Author: user
 *
 * Created on 9 August, 2021, 12:27 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 20000000
void printNo(int n,int x,int dp);
void clearDisp(int x);
void setupADC(int x);
uint16_t calculateADC();

void main(void) {
    TRISD7=0;//12-latchclk
    TRISD6=0;//A serialin
    TRISD5=0;//shift clk
    
    TRISD4=0;  //digits
    TRISD3=0;
    TRISD2=0;
    TRISD0=0;
     
    uint8_t dig[4]={0};
    int8_t i=0;
    uint32_t x = 0, total=0;
    while(1){
        setupADC(0);
        
        for(i=0;i<100;i++){   //take average of 100 samples
            x = calculateADC();
            total += x; 
        }
        x = total/100;
        
        for(i=3;i>=0;i--){  //split the number into each digit
            dig[i]=x%10;
            x/=10;
        }
        for(int i=0;i<4;i++){  //show the number 
            printNo(dig[i],i,0);
            clearDisp(i);   
        }
        total=0;    //clear the variable for next iteration
    }
    return;
}

void printNo(int n,int x,int dp){
    switch (x){
        case 0:
            RD4=1;
            RD3=0;
            RD2=0;
            RD0=0;
            break;
        case 1:
            RD4=0;
            RD3=1;
            RD2=0;
            RD0=0;
            break;
        case 2:
            RD4=0;
            RD3=0;
            RD2=1;
            RD0=0;
            break;
        case 3:
            RD4=0;
            RD3=0;
            RD2=0;
            RD0=1;
            break;
        default:
            RD4=0;
            RD3=0;
            RD2=0;
            RD0=0;
    }
    
    unsigned char c = 0x00;
    
    switch (n){
        case 0:
            c = 0xFC;
            break;
        case 1:
            c = 0x60;
            break;
        case 2:
            c = 0xDA;
            break; 
        case 3:
            c = 0xF2;
            break; 
        case 4:
            c = 0x66;
            break;    
        case 5:
            c = 0xB6;
            break;    
        case 6:
            c = 0xBE;
            break;
        case 7:
            c = 0xE0;
            break;
        case 8:
            c = 0xFE;
            break;    
        case 9:
            c = 0xE6;
            break;    
        default:
            c = 0x00;
    }  
    
    if(dp != 0)
        c = c + 0x01;
        
    RD7=0;
    int i;
    for (i=0; i<8; i++) {
        RD6 = ((c >> i) & 1);
        RD5 = 1;
        __delay_us(1);
        RD5 = 0;
    }
    
    RD7 = 1;
    __delay_us(1);
    RD7 = 0;
}

void clearDisp(int x){
    switch (x){
        case 0:
            RD4=1;
            RD3=0;
            RD2=0;
            RD0=0;
            break;
        case 1:
            RD4=0;
            RD3=1;
            RD2=0;
            RD0=0;
            break;
        case 2:
            RD4=0;
            RD3=0;
            RD2=1;
            RD0=0;
            break;
        case 3:
            RD4=0;
            RD3=0;
            RD2=0;
            RD0=1;
            break;
        default:
            RD4=0;
            RD3=0;
            RD2=0;
            RD0=0;
    }
    unsigned char c = 0x00;
    RD7=0;
    int i;
    for (i=0; i<8; i++) {
        RD6 = ((c >> i) & 1);
        RD5 = 1;
        __delay_us(1);
        RD5 = 0;
    }
    RD7 = 1;
    __delay_us(1);
    RD7 = 0;   
}

void setupADC(int x){
    ADON=1;   //switch on the ADC
    ADFM=1; //right justified   
    switch(x)
        {
            case 0:           
                CHS2=0;
                CHS1=0;
                CHS0=0;
                break;
            case 1:           
                CHS2=0;
                CHS1=0;
                CHS0=1;
                break;
            case 2:           
                CHS2=0;
                CHS1=1;
                CHS0=0;
                break;
            case 3:           
                CHS2=0;
                CHS1=1;
                CHS0=1;
                break;
            case 4:           
                CHS2=1;
                CHS1=0;
                CHS0=0;
                break;    
            case 5:           
                CHS2=1;
                CHS1=0;
                CHS0=1;
                break;
            case 6:           
                CHS2=1;
                CHS1=1;
                CHS0=0;
                break;    
            case 7:           
                CHS2=1;
                CHS1=1;
                CHS0=1;
                break;    
            default:
                CHS2=0;
                CHS1=0;
                CHS0=0;    
        }   
}

uint16_t calculateADC(){
    GO_nDONE = 1; //Initializes A/D Conversion
    while(GO_nDONE); //Wait for A/D Conversion to complete;
    uint16_t val = (ADRESH<<8)+ADRESL;
    return val;
}
