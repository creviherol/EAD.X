// ===========================================
// CONFIGURA��O DO PIC
// ===========================================
#pragma config OSC = HS     //seleciona o oscilador externo de alta velocidade, adequado para cristais de 8?MHz a 25?MHz.
#pragma config WDT = OFF    //desliga o Watchdog Timer, evitando resets autom�ticos caso o temporizador n�o seja reiniciado periodicamente.
#pragma config PWRT = ON    //habilita o Power-up Timer, garantindo um atraso de inicializa��o para estabilizar a tens�o de alimenta��o antes de liberar o c�digo principal.
#pragma config BOREN = ON   //ativa o Brown-out Reset: se a tens�o cair abaixo do limite configurado, o microcontrolador � resetado, protegendo a aplica��o.
#pragma config LVP = OFF    //desliga a programa��o Low-Voltage; isso libera o pino RB5 como GPIO normal (programa��o passa a exigir MCLR/PGM com alta tens�o).
#pragma config PBADEN = OFF //configura os pinos RB0?RB4 como digitais na reinicializa��o, evitando o modo anal�gico padr�o que interfere com o uso de bot�es/teclas.
#pragma config MCLRE = ON   //mant�m o pino RE3/MCLR dedicado como reset externo e n�o como entrada digital.
#pragma config DEBUG = OFF  //desabilita o modo de depura��o no circuito, permitindo opera��o normal sem o depurador do MPLAB.
#pragma config STVREN = ON  //habilita o Stack Overflow/Underflow Reset, protegendo contra estouros da pilha de hardware.

// ===========================================
// #pragma config WRT0/1/2/3 = OFF e #pragma config CP0/1/2/3 = OFF liberam toda a mem�ria de programa para grava��o e leitura, �teis em desenvolvimento 
//(sem prote��o de escrita nem de c�pia).
// ===========================================
#pragma config WRT0 = OFF   
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF

#define _XTAL_FREQ 8000000UL  // Informa � biblioteca XC8 que o clock do sistema � 8?MHz;

