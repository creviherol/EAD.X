
void BC4(){
    int O = 0,T1 = 30,O1 = 1,T = 0,P1,P2=0;
    char texto1[16];
    
    for (int i=1800;i>0;i--){
        O++;
        if (O==(60*O1)){
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
        
        sprintf(texto1, "Senha: %u        ",P2);
        LCD_SetCursor(2,1);
        LCD_String(texto1);
        
        if (T==3){
            if (P2==111){
                i=0;
                T=0;
            }
            else{
                P2=0;
            }
        }
    }    
}