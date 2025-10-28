
// ===========================================
// ULTRASSÔNICO
// ===========================================
#define TRIG LATCbits.LATC7
#define ECHO PORTCbits.RC2

// =========================
// Implementação Ultrassônico
// =========================
void Ultrasonic_Init(void){
    TRISCbits.TRISC7 = 0; // TRIG saída
    TRISCbits.TRISC2 = 1; // ECHO entrada
    
    // Timer1: Fosc/4, prescaler 1:1
    T1CON = 0x01;
    
    // CCP1: Capture mode, rising edge
    CCP1CON = 0x05;
    
    // Zera registros
    TMR1 = 0;
    CCPR1 = 0;
    PIR1bits.CCP1IF = 0;
}

unsigned int Ultrasonic_Read(void){
    unsigned int start, end;
    unsigned long pulse_time_us;

    // Zera Timer1 e flags
    TMR1 = 0;
    PIR1bits.CCP1IF = 0;

    // Pulso de TRIG 10 us
    TRIG = 1;
    __delay_us(10);
    TRIG = 0;

    // Espera rising edge
    while(!PIR1bits.CCP1IF);
    start = CCPR1;
    PIR1bits.CCP1IF = 0;

    // Configura CCP1 para falling edge
    CCP1CON = 0x04; // Falling edge
    while(!PIR1bits.CCP1IF);
    end = CCPR1;
    PIR1bits.CCP1IF = 0;

    // Reconverte CCP1 para rising edge
    CCP1CON = 0x05;

    // Calcula duração do pulso em microsegundos
    // Tick = 1 / (Fosc/4) = 0.5 us para 8 MHz
    pulse_time_us = (end - start) * 0.5;
    
    // Distância em cm: pulse_time_us / 58
    return (unsigned int)(pulse_time_us / 58);
}