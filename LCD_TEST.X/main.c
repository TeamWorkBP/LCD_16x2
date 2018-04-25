//##############################################################################
//    	filename:        	main.c
//
//     	Archivo principal del proyecto LCD_TEST
//
//##############################################################################
//
//      Autor:              Luis Arenas
//      Organizaci�n:       TeamWork BP
//
//      Revisi�n:           1.0
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

    char buf[8 * sizeof (int) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof (buf) - 1];

    *str = '\0';

    do {
        char c = n % 10;
        n /= 10;

        *--str = c + '0';
    } while (n);

    LCD_Text(str);
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
