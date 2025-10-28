#include "Bib_CONFG_PIC18F4520.h"

// ===========================================
// ENDEREÇO I2C DO MÓDULO
// ===========================================
#define LCD_ADDR 0x27 //define o endereço I²C do módulo PCF8574 (com três linhas de endereço em 1). Quando transmitido em modo write, o firmware desloca esse endereço (<<?1).

// ===========================================
// MAPA DE PINOS DO PCF8574 ? LCD
// ===========================================
//Máscaras correspondentes aos bits que controlam o registrador RS, RW, Enable e a luz de fundo no expansor I/O.
#define PCF_RS 0x01
#define PCF_RW 0x02
#define PCF_EN 0x04
#define PCF_BACKLIGHT 0x08

// ===========================================
// PROTÓTIPOS DAS FUNÇÕES
// ===========================================
//As declarações garantem que o compilador conheça todas as rotinas de I²C e LCD antes de usá-las, mantendo a estrutura organizada.
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);

void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Char(char data);
void LCD_String(const char *str);
void LCD_SetCursor(uint8_t linha, uint8_t coluna);
void LCD_SendNibble(uint8_t nibble, uint8_t mode);
void LCD_EnablePulse(uint8_t data);


// ===========================================
// I2C
// ===========================================
void I2C_Init(void) {
    //configura o módulo MSSP em modo master (SSPCON1=0x28), zera SSPCON2/SSPSTAT, define SSPADD para gerar 100?kHz ((Fosc/4)/100kHz - 1), e põe RC3/RC4 como entradas 
    //(open-drain requer resistores pull-up externos).
    SSPCON1 = 0b00101000; // Master mode
    SSPCON2 = 0x00;
    SSPADD = ((_XTAL_FREQ / 4) / 100000) - 1; // 100 kHz
    SSPSTAT = 0x00;
    TRISC3 = 1;  // SCL
    TRISC4 = 1;  // SDA
    //Datasheet: seção MSSP I²C Master Mode descreve os bits SSPCON1<3:0> para 1000 (I²C Master) e a fórmula do baud rate.
}

void I2C_Start(void) {      //aguarda o hardware limpar o bit após transmitir a condição START.
    SSPCON2bits.SEN = 1;    //SEN (Start Enable)
    while(SSPCON2bits.SEN);
}

void I2C_Stop(void) {       //aguarda o hardware limpar o bit após transmitir a condição STOP.
    SSPCON2bits.PEN = 1;
    while(SSPCON2bits.PEN);
}

void I2C_Write(uint8_t data) {  
    //coloca o byte em SSPBUF, espera o buffer esvaziar (BF=0) e aguarda qualquer operação pendente em SSPCON2 (bits ACKEN, RCEN etc.); 
    //isso garante que o byte foi enviado e que a etapa de acknowledge terminou.
    SSPBUF = data;
    while(SSPSTATbits.BF);       // espera o buffer ser enviado
    while(SSPCON2 & 0x1F);       // espera flags de transmissão
}


// ===========================================
// LCD via PCF8574
// ===========================================
void LCD_EnablePulse(uint8_t data) {
    //gera o pulso de Enable: escreve com PCF_EN alto, espera ?450?ns, depois limpa o bit e aguarda ?37?µs (tempo típico para latch). 
    I2C_Write(data | PCF_EN);
    __delay_us(5);
    I2C_Write(data & ~PCF_EN);
    __delay_us(50);
}

void LCD_SendNibble(uint8_t nibble, uint8_t mode) {
    //prepara o nibble alto (4 bits mais significativos), garante backlight ligado, adiciona RS se mode=1 (dados). Envia START, endereço (modo write), o byte e aciona o pulso.
    uint8_t data = (nibble & 0xF0) | PCF_BACKLIGHT;
    if(mode) data |= PCF_RS;
    I2C_Start();
    I2C_Write(LCD_ADDR << 1);  // endereço + WRITE
    I2C_Write(data);
    LCD_EnablePulse(data);
    I2C_Stop();
}

void LCD_Command(uint8_t cmd) { //envia um comando de 8 bits dividindo em dois nibbles (alto e baixo), conforme protocolo 4-bit do HD44780.
    LCD_SendNibble(cmd & 0xF0, 0);
    LCD_SendNibble((cmd << 4) & 0xF0, 0);
    if(cmd == 0x01) __delay_ms(2);
    else __delay_us(50);
}

void LCD_Char(char data) {  //envia um comando de 8 bits dividindo em dois nibbles (alto e baixo)
    LCD_SendNibble(data & 0xF0, 1);
    LCD_SendNibble((data << 4) & 0xF0, 1);
    __delay_us(50);
}

void LCD_String(const char *str) {  //envia cada caractere até o terminador nulo (string em C).
    while(*str) LCD_Char(*str++);
}

void LCD_SetCursor(uint8_t linha, uint8_t coluna) { //calcula o endereço DDRAM: primeira linha começa em 0x80, segunda em 0xC0; soma coluna-1 e manda como comando.
    uint8_t addr = (linha == 1) ? 0x80 : 0xC0;
    addr += (coluna - 1);
    LCD_Command(addr);
}

void LCD_Init(void) {
    //implementa a sequência recomendada para inicializar LCDs em 4 bits: espera >15?ms após power-up, envia 0x33 (reset), 0x32 (seleciona 4 bits), 0x28 (2 linhas, fonte 5x8), 
    //0x0C (display on, cursor off), 0x06 (incrementa cursor) e 0x01 (clear). Delays garantem que cada comando seja aceito, conforme a rotina típica do datasheet do HD44780.
    __delay_ms(20);
    LCD_Command(0x33); // Inicialização
    __delay_ms(5);
    LCD_Command(0x32);
    __delay_ms(5);
    LCD_Command(0x28); // 4 bits, 2 linhas, 5x8
    LCD_Command(0x0C); // Display ON, cursor OFF
    LCD_Command(0x06); // Incrementa cursor
    LCD_Command(0x01); // Limpa display
    __delay_ms(2);
}
