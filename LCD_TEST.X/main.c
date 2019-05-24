/*
 * File:   main.c
 * Author: Luis Arenas
 *
 * Demostración del uso de la libreria LCD_16x2
 * 
 * Created on 23 de mayo de 2019, 09:22 AM
 */


#include <xc.h>
#include "fuses.h"
#define _XTAL_FREQ 1000000

#include "LCD_16x2.h"

char msg1[] = "Hola Mundo";
char msg2[] = "Quien eres?";
char msg3[] = {1, 2, '_', '(', 194, ')', '_', '/', 1}; //"¯\_(?)_/¯";
char msg4[] = {'(', 3, '_', 3, ')'};

char C1[] = {0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
char C2[] = {0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00};
char C3[] = {0x00, 0x00, 0x1F, 0x0A, 0x0A, 0x0A, 0x0A};

void main(void) {
    ADCON1 = 0x0F;
    LCD_Init();
    LCD_CreateChar(1, C1);
    LCD_CreateChar(2, C2);
    LCD_CreateChar(3, C3);
    LCD_SetCursor(0, 0);
    LCD_Text("Testeo....");
    LCD_SetCursor(1, 0);
    LCD_Cursor();
    LCD_Blink();
    char i, j;
    char valid;
    while (1) {
        //mensaje 1
        for (j = 0; j < 4; j++) {
            LCD_SetCursor(1, 0);
            LCD_Blink();
            __delay_ms(1500);
            LCD_leftToRight();
            i = 0;
            LCD_noBlink();
            do {
                switch (j) {
                    case 0:
                        valid = i < (sizeof (msg1) - 2);
                        LCD_Char(msg1[i]);
                        break;
                    case 1:
                        valid = i < (sizeof (msg2) - 2);
                        LCD_Char(msg2[i]);
                        break;
                    case 2:
                        valid = i < (sizeof (msg3) - 1);
                        LCD_Char(msg3[i]);
                        break;
                    default:
                        valid = i < (sizeof (msg4) - 1);
                        LCD_Char(msg4[i]);
                        break;
                }
                i++;
                __delay_ms(150);
            } while (valid);
            LCD_Blink();
            __delay_ms(1000);
            LCD_rightToLeft();
            i = 0;
            LCD_noBlink();
            do {
                switch (j) {
                    case 0:
                        valid = i < (sizeof (msg1));
                        break;
                    case 1:
                        valid = i < (sizeof (msg2));
                        break;
                    case 2:
                        valid = i < (sizeof (msg3));
                        break;
                    default:
                        valid = i < (sizeof (msg4));
                        break;
                }
                LCD_Char(' ');
                i++;
                __delay_ms(50);
            } while (valid);
        }
    }
    LCD_Text(msg3);

    return;
}
