// ===========================================
// CONFIGURAÇÃO DO PIC
// ===========================================
#pragma config OSC = HS     //seleciona o oscilador externo de alta velocidade, adequado para cristais de 8?MHz a 25?MHz.
#pragma config WDT = OFF    //desliga o Watchdog Timer, evitando resets automáticos caso o temporizador não seja reiniciado periodicamente.
#pragma config PWRT = ON    //habilita o Power-up Timer, garantindo um atraso de inicialização para estabilizar a tensão de alimentação antes de liberar o código principal.
#pragma config BOREN = ON   //ativa o Brown-out Reset: se a tensão cair abaixo do limite configurado, o microcontrolador é resetado, protegendo a aplicação.
#pragma config LVP = OFF    //desliga a programação Low-Voltage; isso libera o pino RB5 como GPIO normal (programação passa a exigir MCLR/PGM com alta tensão).
#pragma config PBADEN = OFF //configura os pinos RB0?RB4 como digitais na reinicialização, evitando o modo analógico padrão que interfere com o uso de botões/teclas.
#pragma config MCLRE = ON   //mantém o pino RE3/MCLR dedicado como reset externo e não como entrada digital.
#pragma config DEBUG = OFF  //desabilita o modo de depuração no circuito, permitindo operação normal sem o depurador do MPLAB.
#pragma config STVREN = ON  //habilita o Stack Overflow/Underflow Reset, protegendo contra estouros da pilha de hardware.

// ===========================================
// #pragma config WRT0/1/2/3 = OFF e #pragma config CP0/1/2/3 = OFF liberam toda a memória de programa para gravação e leitura, úteis em desenvolvimento 
//(sem proteção de escrita nem de cópia).
// ===========================================
#pragma config WRT0 = OFF   
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF

#define _XTAL_FREQ 8000000UL  // Informa à biblioteca XC8 que o clock do sistema é 8?MHz;

