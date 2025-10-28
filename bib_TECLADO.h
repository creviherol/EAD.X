//biblioteca para interface com
//teclado matricial 4x3

#define C1  PORTBbits.RB7
#define C2  PORTBbits.RB5
#define C3  PORTBbits.RB6
#define C4  PORTBbits.RB4

#define L1  LATBbits.LATB0
#define L2  LATBbits.LATB1
#define L3  LATBbits.LATB2
#define L4  LATBbits.LATB3

int varredura(){
    int valor = -1;
    
    //primeira linha
    L1 = 0;
    L2 = 1;
    L3 = 1;
    L4 = 1;
    if(C1==0){
        valor = 1;
        while(C1==0);
    }
    if(C2==0){
        valor = 2;
        while(C2==0);
    }
    if(C3==0){
        valor = 3;
        while(C3==0);
    }
    if(C4==0){
        valor = 12;
        while(C4==0);
    }
    
    
    //segunda linha
    L1 = 1;
    L2 = 0;
    L3 = 1;
    L4 = 1;
    if(C1==0){
        valor = 4;
        while(C1==0);
    }
    if(C2==0){
        valor = 5;
        while(C2==0);
    }
    if(C3==0){
        valor = 6;
        while(C3==0);
    }
    if(C4==0){
        valor = 13;
        while(C4==0);
    }
    
    //terceira linha
    L1 = 1;
    L2 = 1;
    L3 = 0;
    L4 = 1;
    if(C1==0){
        valor = 7;
        while(C1==0);
    }
    if(C2==0){
        valor = 8;
        while(C2==0);
    }
    if(C3==0){
        valor = 9;
        while(C3==0);
    }
    if(C4==0){
        valor = 14;
        while(C4==0);
    }
    
    //quarta linha
    L1 = 1;
    L2 = 1;
    L3 = 1;
    L4 = 0;
    if(C1==0){
        valor = 10; 
        while(C1==0);
    }
    if(C2==0){
        valor = 0;
        while(C2==0);
    }
    if(C3==0){
        valor = 11; 
        while(C3==0);
    }
    if(C4==0){
        valor = 15; 
        while(C4==0);
    }

    return valor;
}