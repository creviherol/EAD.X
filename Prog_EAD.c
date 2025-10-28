#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "bib_TECLADO.h"
#include "bib_LCD.h"
#include "bib_Ultrasonico.h"
#include "C4.h"
#include "Bib_CONFG_PIC18F4520.h"


int P=0,P1,P2,U = 0,T = 0,O=0,O1,T1;
char texto1[16],texto2[16];
    
void buzzer(int D,int P);
void Escolha();
void BC4(int O,int T1,int O1,int T, int P1, int P2);

void buzzer(int D,int P){
    if (D<P){
        PORTCbits.RC1 = 1;
    }
    else {
        PORTCbits.RC1 = 0;
    }
}


void Escolha(){
    while(U){
        P1 = varredura();
        LCD_SetCursor(2,1);
        LCD_String("Um valor ate 250");

        if (P1>=0 && P1<=9){
            if (T<3){
                P2 = P2*10 + P1;
                T++;
                __delay_ms(200);
            }
        }
        
        sprintf(texto1, "Valor: %u cm     ",P2);
        LCD_SetCursor(1,1);
        LCD_String(texto1);
        
        if (P2==999){
            P2=0;
            T=0;
            T1=30;
            O1=1;      
            BC4(O,T1,O1,T,P1,P2);
            U=0;
        }
        
        if (P1==11){
            U=0;
            P = P2;
        }
    }
}

// ===========================================
// PROGRAMA PRINCIPAL
// ===========================================
void main(void) {
    I2C_Init();
    LCD_Init();
    Ultrasonic_Init();
    ADCON1 = 15;
    TRISB = 0b11110000;
    TRISCbits.TRISC1=0;
    LATB = 0x0F;
    INTCON2bits.RBPU = 0;   //pull up
    
    
    while(1) {
        unsigned int dist = Ultrasonic_Read();
        
        P1 = varredura();
        
        if (P1==10){
            U=1;
            P2=0;
            T=0;
            PORTCbits.RC1 = 0;
            Escolha();
        }
        
        buzzer(dist,P);
        __delay_ms(200);
        sprintf(texto1, "Dist: %u cm     ", dist);
        LCD_SetCursor(1,1);
        LCD_String(texto1);
        sprintf(texto2, "Dist/Detec: %u      ", P);
        LCD_SetCursor(2,1);
        LCD_String(texto2);
        
    }
}