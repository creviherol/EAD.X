// Arquivo de config . inicial
// do MCU PIC18F4520
#include <xc.h>

#pragma config OSC = HS         // Cristal externo (4 MHz)
#pragma config LVP = OFF        // Low Voltage Programming desativado
#pragma config WDT = OFF        // Watchdog Timer desativado
#pragma config MCLRE = ON       
#pragma config PBADEN = OFF     // PORTB como digital


#define _XTAL_FREQ 8000000    // Clock de 8 MHz - VERIFIQUE SE � CORRETO!
#define LCD_ADDR 0x20         // Endere�o I2C do PCF8574 (confirmado)