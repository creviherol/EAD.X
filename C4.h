
void BC4(int O,int T1,int O1,int T, int P1, int P2){
    char texto1[20],texto2[20];

    for (int i=900;i>0;i--){
        O++;
        if (O==(30*O1)){
            O1++;
            T1--;
        }
        
        sprintf(texto1, "Tempo: %u         ",T1);
        LCD_SetCursor(1,1);
        LCD_String(texto1);
        P1 = varredura();
        
        if (P1>=0 && P1<=9){
            if (T<3){
                P2 = P2*10 + P1;
                T++;
            }
        }
     
        sprintf(texto2, "Senha: %u        ",P2);
        LCD_SetCursor(2,1);
        LCD_String(texto2);
        
        if (T==3){
            if (P2==658){
                i=0;
                T=0;
            }
            else{
                P2=0;
                T=0;
            }
        }
    }    
}