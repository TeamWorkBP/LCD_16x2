//##############################################################################
//    	filename:        	main.c
//
//     	Archivo principal del proyecto LCD_TEST
//
//##############################################################################
//
//      Autor:              Luis Arenas
//      Organización:       TeamWork BP
//
//      Revisión:           1.0
//      Fecha:              April. 2018
//      Compilador:         XC8
//
//##############################################################################

#include <xc.h>           // XC8 compiler
#define _XTAL_FREQ 1000000

#include "fuses.h"
#include "LCD_16x2.h"


#define BUTTON          PORTBbits.RB0
#define BUTTON_TRI      TRISBbits.TRISB0

#define OUTPUT_PIN      0
#define INPUT_PIN       1

unsigned char displayTODO;
unsigned int cntButton = 0;
unsigned char btnText[7] = "Btn ?";

void printNumber(unsigned int n) {
    //int : [-32768 : 32767]
    //ejemplo: n = 312
    int div = 10000; //comenzar con (decenas de millar)
    
    if (n < 0) { //si es negativo, mostrar signo '-'
        LCD_Char('-');
        n = -n;
    }
    
    //buscamos el primer digito
    //ejemplo: n = 00312
    //             xx*
    //(*) se encuentra el primer digito (centenas))
    while (n / div == 0) {
        div /= 10;
    }
    
    char digito = 0; //digito a mostrar
    
    //Encontrar cada digito en adelante y mostrar en LCD
    //Ejemplo: n=312
    //si div es 100, n/div será 3
    //se muestra el digito encontrado y se resta al numero evaluado
    //(312-3*100) es 12
    
    while (div > 0) {
        digito = n / div; 
        n -= digito*div;
        div /= 10;
        LCD_Char(digito + '0');
    }
}

void main() {

    ADCON1 = 0x0F; // pins digital IO
    TRISC = 0x00;
    PORTC = 0x00;

    displayTODO = 0;

    LCD_Init();

    BUTTON_TRI = INPUT_PIN;

    LCD_ConstText_pos(0, 0, "23.04.18");

    LCD_Text_pos(1, 0, btnText);

    LCD_Command(DISPLAY_CTRL + DISPLAY_ON); // + CURSOR_ON );
    LCD_SetCursor(1, 3);

    while (1) {
        if (BUTTON == 0) {
            while (BUTTON == 0);
            cntButton++;
            displayTODO = 1;
        }

        if (displayTODO) {
            LCD_SetCursor(1, 4);
            printNumber(cntButton);
            displayTODO = 0;
        }
    }
}

