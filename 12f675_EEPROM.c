/*
 * File:   newmain.c
 * Author: user
 *
 * Created on 22 September, 2020, 11:28 AM
 */
#pragma config FOSC = INTRCCLK  // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // GP3/MCLR pin function select (GP3/MCLR pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include <xc.h>
#include <eeprom_routines.h>
void main(void) {
    TRISIO0=0;
    eeprom_write(0,0xAA);
    if(eeprom_read(0)==0xAA)  //this should make the led glow
        GPIO0=1;
    else
        GPIO0=0;
    return;
}
