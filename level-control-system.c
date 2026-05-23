/*Practrica 6
CONTROL DE NIVEL
Ceti Colomos
Electronica digital 4
Parcial 2
Diego Antonio Pérez Castellanos
Andrés Manuel Pérez Franco
*/

#INCLUDE <16F887.H>
#DEVICE ADC=8
#USE DELAY(CLOCK=4000000) 
#FUSES INTRC_IO,NOWDT,NOPUT,NOMCLR,NOPROTECT,NOCPD,NOBROWNOUT 
#FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21 

#USE FAST_IO(A)
#INCLUDE <LCD1.C>

INT I, AUX, CUENTA, X, Z=0, LVLINT, SP=0, TECLA[16]={1,2,3,10,4,5,6,11,7,8,9,12,14,0,15,13};
FLOAT LVL;


VOID LECTURA(){
   SET_ADC_CHANNEL(6);
   DELAY_US(20);
   X=READ_ADC();
   LVL=X*(5.0/255);
   LVLINT=(INT)LVL;
}

VOID MATRICIAL(){
   AUX=0XEF;                                 //Inicializar variable AUX
   CUENTA=0;                                 //Iniciaizar variable CUENTA
   FOR(I=0;I<4;I++)                          //Ciclo para barrido 4 Filas
   {
      AUX=AUX>>1;                               //Desplazamiento Derecha Pilas
      OUTPUT_A((INPUT_A()&0XF0)|(AUX&0X0F));    //Envío de 0 a cada fila
      
      IF(INPUT(PIN_A7)==0)                      //Preguntar por columnas=0
      BREAK;                                    //Se rompe el ciclo al ser verdadero
      CUENTA++;                                 //Se incrementa la cuenta al ser falso
      IF(INPUT(PIN_A6)==0)
      BREAK;
      CUENTA++;
      IF(INPUT(PIN_A5)==0)
      BREAK;
      CUENTA++;
      IF(INPUT(PIN_A4)==0)
      BREAK;
      CUENTA++;
      DELAY_MS(20);                             //Retraso de tiempo de 20ms
   }
}

VOID MAIN (){
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(sAN6);
   
   SET_TRIS_A(0XF0);
   SET_TRIS_C(0X01);
   SET_TRIS_D(0X00);
   
   LCD_INIT();
   
   PRINTF(LCD_PUTC,"\f");
   PRINTF(LCD_PUTC,"CONTROL DE NIVEL");
   DELAY_MS(1000);
   PRINTF(LCD_PUTC,"\f");
   PRINTF(LCD_PUTC,"DIEGO PEREZ\n21300606");
   DELAY_MS(1000);
   PRINTF(LCD_PUTC,"\f");
   PRINTF(LCD_PUTC,"ANDRES PEREZ\n21300583");
   DELAY_MS(1000);
   PRINTF(LCD_PUTC,"\f");
   PRINTF(LCD_PUTC,"PRESIONE EL\nBOTON PULSADOR");
   
   WHILE(INPUT(PIN_C0)==0){
   }
   WHILE(INPUT(PIN_C0)==1){
   }
   
   WHILE (TRUE){
      LECTURA();
      MATRICIAL();
      IF(Z==0&&(CUENTA<3||(CUENTA>3&&CUENTA<6)||CUENTA==13)){
         SP=TECLA[CUENTA];
      }
      
      IF(Z==0&&INPUT(PIN_C0)==1){
         WHILE(INPUT(PIN_C0)==1){
         }
         Z=1;
      }
      
      IF(Z==0){
         lcd_gotoxy(1,1);
         PRINTF(LCD_PUTC,"NIVEL=%1.2gL     \nSP=%uL           ",LVL,SP);
      }
      
      IF((Z==1)&&(LVLINT>SP)){
      lcd_gotoxy(1,1);
      PRINTF(LCD_PUTC,"NIVEL=%1.2gL     \n               V",LVL);
      }
      ELSE IF((Z==1)&&(LVLINT==SP)){
      lcd_gotoxy(1,1);
      PRINTF(LCD_PUTC,"NIVEL=%1.2gL     \n               E",LVL);
      }
      ELSE IF((Z==1)&&(LVLINT<SP)){
      lcd_gotoxy(1,1);
      PRINTF(LCD_PUTC,"NIVEL=%1.2gL     \n               L",LVL);
      }
      
      IF(Z==1&&INPUT(PIN_C0)==1){
         WHILE(INPUT(PIN_C0)==1){
         }
         Z=0;
      }
      
      DELAY_MS(100);
   }
} 
