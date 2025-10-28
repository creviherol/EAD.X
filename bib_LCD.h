// ===========================================
// CONFIGURAÇÃO DO PIC
// ===========================================
#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config PWRT = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config PBADEN = OFF
#pragma config MCLRE = ON
#pragma config DEBUG = OFF
#pragma config STVREN = ON
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#define _XTAL_FREQ 8000000UL  // Frequência do cristal


// ===========================================
// ENDEREÇO I2C DO MÓDULO
// ===========================================
#define LCD_ADDR 0x27

// ===========================================
// MAPA DE PINOS DO PCF8574 ? LCD
// ===========================================
#define PCF_RS 0x01
#define PCF_RW 0x02
#define PCF_EN 0x04
#define PCF_BACKLIGHT 0x08

// ===========================================
// PROTÓTIPOS DAS FUNÇÕES
// ===========================================
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
    SSPCON1 = 0b00101000; // Master mode
    SSPCON2 = 0x00;
    SSPADD = ((_XTAL_FREQ / 4) / 100000) - 1; // 100 kHz
    SSPSTAT = 0x00;
    TRISC3 = 1;  // SCL
    TRISC4 = 1;  // SDA
}

void I2C_Start(void) {
    SSPCON2bits.SEN = 1;
    while(SSPCON2bits.SEN);
}

void I2C_Stop(void) {
    SSPCON2bits.PEN = 1;
    while(SSPCON2bits.PEN);
}

void I2C_Write(uint8_t data) {
    SSPBUF = data;
    while(SSPSTATbits.BF);       // espera o buffer ser enviado
    while(SSPCON2 & 0x1F);       // espera flags de transmissão
}

// ===========================================
// LCD via PCF8574
// ===========================================
void LCD_EnablePulse(uint8_t data) {
    I2C_Write(data | PCF_EN);
    __delay_us(5);
    I2C_Write(data & ~PCF_EN);
    __delay_us(50);
}

void LCD_SendNibble(uint8_t nibble, uint8_t mode) {
    uint8_t data = (nibble & 0xF0) | PCF_BACKLIGHT;
    if(mode) data |= PCF_RS;

    I2C_Start();
    I2C_Write(LCD_ADDR << 1);  // endereço + WRITE
    I2C_Write(data);
    LCD_EnablePulse(data);
    I2C_Stop();
}

void LCD_Command(uint8_t cmd) {
    LCD_SendNibble(cmd & 0xF0, 0);
    LCD_SendNibble((cmd << 4) & 0xF0, 0);
    if(cmd == 0x01) __delay_ms(2);
    else __delay_us(50);
}

void LCD_Char(char data) {
    LCD_SendNibble(data & 0xF0, 1);
    LCD_SendNibble((data << 4) & 0xF0, 1);
    __delay_us(50);
}

void LCD_String(const char *str) {
    while(*str) LCD_Char(*str++);
}

void LCD_SetCursor(uint8_t linha, uint8_t coluna) {
    uint8_t addr = (linha == 1) ? 0x80 : 0xC0;
    addr += (coluna - 1);
    LCD_Command(addr);
}

void LCD_Init(void) {
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
