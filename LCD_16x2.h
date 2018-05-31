//##############################################################################
//    filename:        LCD_16x2.h
//##############################################################################
//    Libreria de comandos para LCD 16x2
//##############################################################################
//
//      Autor:              Luis Arenas
//      Organización:       TeamWork BP
//      Empresa:            UTP
//
//      Revisión:           1.0
//      Fecha:              April. 2018
//      Compilador:         XC8
//
//##############################################################################
//
//      Funciones:
//
//- void LCD_Init(void)
//      Secuencia de inicialización del LCD
//      Se debe ejecutar antes de usar cualquier otra función!!!
//
//- void LCD_Command(unsigned char cmd)
//      Envia un comando al LCD 
//      -> LCD_Command(DISPLAY_CTRL + DISPLAY_ON + CURSOR_ON + BLINK_ON);
//
//- void LCD_Clear(void)
//      Limpia la memoria y pantalla del LCD
//
//- void LCD_Home(void)
//      Envia el cursor a la posicion de inicio (fila 0, columna 0)
//
//- void LCD_SetCursor(unsigned char row,unsigned char column)
//      Posiciona el cursor en la fila y columna indicada (ambos empiezan con 0)
//
//- void LCD_CharOut(unsigned char character)
//      Escribe un caracter en la posición del cursor
//
//- void LCD_TextOut(unsigned char *text)
//      Escribe una cadena de caracteres;
//      -> unsigned char string[] = "Hello";
//         LCD_TextOut(string);
//
//- void LCD_TextOut_pos(unsigned char row,unsigned char col,unsigned char *text)
//      Escribe una cadena de caracteres en la fila y columna (row, col)
//      -> unsigned char string[] = "Hello";
//         LCD_TextOut_pos(0,0,string);
//
//- void LCD_ConstTextOut(const char *text)
//      Escribe una cadena de caracteres de tipo constante en la fila y columna (row, col)
//      -> LCD_ConstTextOut_pos(0,0,"Hello");
//
//##############################################################################

#ifndef LCD_16X2_H
#define	LCD_16X2_H

#include <xc.h>
#include "LCD_config.h" // pin and power configuration file

//******************************************************************************

// Definicion de Comandos e Instrucciones (HD44780 compatible)
//                              RS  R/W |   D7  D6  D5  D4  D3  D2  D1  D0
// Limpiar Pantalla             0   0   |   0   0   0   0   0   0   0   1
#define CLEAR_DISPLAY       0x01 // 0b00000001
// Retorno a Inicio             0   0   |   0   0   0   0   0   0   1   x
#define RETURN_HOME         0x02 // 0b00000010
// Modo de Entrada               0   0   |   0   0   0   0   0   1   I/D S
#define ENTRY_MODE          0x04 // 0b00000100 (MODELO BASE - Modo de Entrada)
#define CURSOR_INC          0x02 // 0b00000010 (I/D-1)
#define CURSOR_DEC          0x00 // 0b00000001 (I/D-0)
#define DISPLAY_SHIFT_ON    0x01 // 0b00000001 (S-1)
#define DISPLAY_SHIFT_OFF   0x00 // 0b00000001 (S-0)
// Display ctrl                 0   0   |   0   0   0   0   1   D   C   B
#define DISPLAY_CTRL        0x08 // 0b00001000 (MODELO BASE - Display Control)
#define DISPLAY_ON          0x04 // 0b00000100 (D-1)
#define DISPLAY_OFF         0x00 // 0b00000000 (D-0)
#define CURSOR_ON           0x02 // 0b00000010 (C-1)
#define CURSOR_OFF          0x00 // 0b00000000 (C-0)
#define BLINK_ON            0x01 // 0b00000001 (B-1)
#define BLINK_OFF           0x00 // 0b00000000 (B-0)
// Cursor / Display shift       0   0   |   0   0   0   1   S/C R/L x   x
#define DISPLAY_SHIFT_R     0x1C // 0b00011100 [S/C-1, R/L-1]
#define DISPLAY_SHIFT_L     0x18 // 0b00011000 [S/C-1, R/L-0]
#define CURSOR_MOVE_R       0x14 // 0b00010100 [S/C-0, R/L-1]
#define CURSOR_MOVE_L       0x10 // 0b00010000 [S/C-0, R/L-0]

//                              RS  R/W |   D7  D6  D5  D4  D3  D2  D1  D0
// Function Set                 0   0   |   0   0   1   DL  N   F   x   x
//      DL: 1 = 8-Bit   / 0 = 4-Bit interface
//      N:  1 = 2 lines / 0 = 1 line
//      F:  1 = 5x11    / 0 = 5x8 dots
#define LCD_RESET           0x30
#define FOUR_BIT            0x20 // 4-bit Interface
#define FOUR_BIT_ONE_LINE   0x20 // 0b00100000 [DL-0, N-0, F-0]
#define FOUR_BIT_TWO_LINE   0x28 // 0b00101000 [DL-0, N-1, F-0]
#define EIGHT_BIT           0x30 // 8-bit Interface
#define EIGHT_BIT_ONE_LINE  0x30 // 0b00110000 [DL-1, N-0, F-0]
#define EIGHT_BIT_TWO_LINE  0x38 // 0b00111000 [DL-1, N-1, F-0]

//******************************************************************************

// Set CGRAM address            0   0   |   0   1   a   a   a   a   a   a
#define CGRAM_ADDR          0x40
// Set DDRAM address            0   0   |   1   a   a   a   a   a   a   a
#define CURSOR_ADDR         0x80

// Read busy flag               0   1   |   BF  a   a   a   a   a   a   a

//******************************************************************************

#ifndef LCD_USE_8BIT_DATA
#define LCD_D3_OUT  LCD_D7_OUT
#define LCD_D2_OUT  LCD_D6_OUT
#define LCD_D1_OUT  LCD_D5_OUT
#define LCD_D0_OUT  LCD_D4_OUT
#define LCD_D3_IN   LCD_D7_IN
#endif

#define LCD_READ        1   //LCD_RW - Modo Lectura
#define LCD_WRITE       0   //LCD_RW - Modo Escritura
#define LCD_CMD         0   //LCD_RS - Modo Comando
#define LCD_DATA        1   //LCD_RS - Modo Dato

#define LCD_BUSY        1   // busy flag logic

#define LCD_ENABLE()    LCD_E = 1;
#define LCD_DISABLE()   LCD_E = 0;
#define LCD_STROBE()    LCD_E = 1; LCD_DELAY_1US(); LCD_E = 0;

#define LINE_OFFSET     0x40    // Registro de inicio de la 2da fila

union LCDv8bit {
    char all;

    struct {
        unsigned bit0 : 1;
        unsigned bit1 : 1;
        unsigned bit2 : 1;
        unsigned bit3 : 1;
        unsigned bit4 : 1;
        unsigned bit5 : 1;
        unsigned bit6 : 1;
        unsigned bit7 : 1;
    };
};

union LCDv8bit LCD_data; // bitfield variable (bitwise acess)
unsigned char LCD_busy_cnt;

char _displaycontrol;
char _displaymode;

// -------------------- LCD-functions ------------------------------------------

void LCD_Init(void);
void LCD_Write(char value, char mode);
void LCD_Text(void *text);
void LCD_CustomChar(void *pt);
unsigned char LCD_Busy(void);

//******************************************************************************
#define LCD_Write_Nibble(dato)  LCD_RS = LCD_CMD; LCD_Write(dato,0)

//******************************************************************************
#define LCD_DISPLAY_CTRL()      LCD_Command((unsigned)DISPLAY_CTRL | _displaycontrol)

//******************************************************************************
#define LCD_ENTRY_MODE()        LCD_Command((unsigned)ENTRY_MODE | _displaymode)

//******************************************************************************
#define LCD_Clear()             LCD_Command(CLEAR_DISPLAY)

//******************************************************************************
#define LCD_Home()              LCD_Command(RETURN_HOME)

//******************************************************************************
#define LCD_Display()           _displaycontrol |= DISPLAY_ON; LCD_DISPLAY_CTRL()

//******************************************************************************
#define LCD_noDisplay()         _displaycontrol &= ~DISPLAY_ON; LCD_DISPLAY_CTRL()

//******************************************************************************
#define LCD_Cursor()            _displaycontrol |= CURSOR_ON; LCD_DISPLAY_CTRL()

//******************************************************************************
#define LCD_noCursor()          _displaycontrol &= ~CURSOR_ON; LCD_DISPLAY_CTRL()

//******************************************************************************
#define LCD_Blink()             _displaycontrol |= BLINK_ON; LCD_DISPLAY_CTRL()

//******************************************************************************
#define LCD_noBlink()           _displaycontrol &= ~BLINK_ON; LCD_DISPLAY_CTRL()

//******************************************************************************
#define LCD_scrollDisplayLeft()  LCD_Command(DISPLAY_SHIFT_L)

//******************************************************************************
#define LCD_scrollDisplayRight() LCD_Command(DISPLAY_SHIFT_R)

//******************************************************************************
#define LCD_leftToRight()       _displaymode |= CURSOR_INC;; LCD_ENTRY_MODE()

//******************************************************************************
#define LCD_rightToLeft()       _displaymode &= ~CURSOR_INC; LCD_ENTRY_MODE()

//******************************************************************************
#define LCD_Autoscroll()        _displaymode |= DISPLAY_SHIFT_ON;; LCD_ENTRY_MODE()

//******************************************************************************
#define LCD_noAutoscroll()      _displaymode &= ~DISPLAY_SHIFT_ON; LCD_ENTRY_MODE()

//******************************************************************************
#define LCD_Command(dato)       while(LCD_Busy()); LCD_RS = LCD_CMD; LCD_Write(dato,1)

//******************************************************************************
#define LCD_Data(dato)          while(LCD_Busy()); LCD_RS = LCD_DATA; LCD_Write(dato,1)

//******************************************************************************
#define LCD_CreateChar(pos,v)   LCD_CustomMem(pos); LCD_CustomChar(v)

//******************************************************************************
#define LCD_Char                LCD_Data

//******************************************************************************
#define LCD_Char_pos(row,col,c) LCD_SetCursor(row,col); LCD_Data(c)

//******************************************************************************
#define LCD_SetCursor(r,c)      LCD_Command(CURSOR_ADDR + (LINE_OFFSET * r) + c)

//******************************************************************************
#define LCD_CustomMem(loc)      LCD_Command(CGRAM_ADDR | ((loc & 0x7) << 3))

//******************************************************************************

void LCD_Init(void) {
#ifdef LCD_RW
    LCD_RW_DIR = 0;
    LCD_RW = 0;
#endif
    LCD_RS_DIR = 0;
    LCD_RS = 0;
    LCD_E_DIR = 0;
    LCD_E = 0;

    LCD_DIR_OUT();

    LCD_busy_cnt = 1; // busy_flag time out counter

    LCD_DELAY_15MS();
    // display reset procedure
    LCD_Write_Nibble(LCD_RESET);
    LCD_DELAY_5MS();
    LCD_Write_Nibble(LCD_RESET);
    LCD_DELAY_5MS();
    LCD_Write_Nibble(LCD_RESET);
    LCD_DELAY_5MS();

#ifdef LCD_USE_8BIT_DATA
    LCD_Write_Nibble(EIGHT_BIT);
    while (LCD_Busy()) {
        ;
    } // wait
    LCD_Command(EIGHT_BIT_TWO_LINE);
#else
    LCD_Write_Nibble(FOUR_BIT);
    while (LCD_Busy()) {
        ;
    } // wait
    LCD_Command(FOUR_BIT_TWO_LINE);
#endif
    _displaycontrol = DISPLAY_ON | CURSOR_OFF | BLINK_OFF;
    LCD_DISPLAY_CTRL();
    _displaymode = CURSOR_INC | DISPLAY_SHIFT_OFF;
    LCD_ENTRY_MODE();
    LCD_Clear();
    LCD_Home();
}

//******************************************************************************

void LCD_Write(char value, char mode) {
    LCD_data.all = value;
#ifdef LCD_RW
    LCD_RW = LCD_WRITE;
#endif
    LCD_D7_OUT = LCD_data.bit7;
    LCD_D6_OUT = LCD_data.bit6;
    LCD_D5_OUT = LCD_data.bit5;
    LCD_D4_OUT = LCD_data.bit4;
#ifndef LCD_USE_8BIT_DATA
    LCD_STROBE();
    if (mode) {
#endif
        LCD_D3_OUT = LCD_data.bit3;
        LCD_D2_OUT = LCD_data.bit2;
        LCD_D1_OUT = LCD_data.bit1;
        LCD_D0_OUT = LCD_data.bit0;
        LCD_STROBE();
#ifndef LCD_USE_8BIT_DATA
    }
#endif
}

//******************************************************************************

#define LCD_Text_pos(row,col,text) LCD_SetCursor(row,col);LCD_Text(text)

void LCD_Text(void *pt) {
    unsigned char *text = pt;
    while (*text) {
        LCD_Data(*text);
        text++;
    }
}

//******************************************************************************

void LCD_CustomChar(void *pt) {
    unsigned char *c = pt;
    for (char i = 0; i < 8; i++) {
        LCD_Data(*c);
        c++;
    }
}

//******************************************************************************

#define LCD_PrintNumber(num) LCD_print_number((unsigned long)num,num > 0 ? 0 : 1u)
#define LCD_PrintNumber_pos(row,col,num) LCD_SetCursor(row,col);LCD_PrintNumber(num)

void LCD_print_number(unsigned long num, char sign) {
    if (num == 0) {
        LCD_Char('0');
        return;
    }
    if (sign) {
        LCD_Char('-');
        num = ~num + 1;
    }
    unsigned long lcd_div = 1000000000;
    while (num / lcd_div == 0) {
        lcd_div /= 10;
    }
    while (lcd_div) {
        char c = num / lcd_div;
        LCD_Data('0' + c);
        num %= lcd_div;
        lcd_div /= 10;
    }
}

//******************************************************************************

unsigned char LCD_Busy() {
#ifdef LCD_RW
    if (LCD_busy_cnt >= LCD_TIMEOUT) {
        LCD_busy_cnt = 1;
        return 0;
    }

    LCD_RW = LCD_READ;
    LCD_RS = LCD_CMD;
    LCD_DIR_IN();

    LCD_ENABLE();
    LCD_DELAY_1US();
    LCD_data.bit7 = LCD_D7_IN;
    LCD_DISABLE();
    LCD_ENABLE();
    LCD_DELAY_1US();
    LCD_DISABLE();

    LCD_DIR_OUT();
    LCD_RW = LCD_WRITE;
    //LCD_DELAY_5MS();

    if (LCD_data.bit7 == LCD_BUSY) {
        LCD_busy_cnt++;
        return 1;
    } else {
        LCD_busy_cnt = 1;
        return 0;
    }
#else
    __delay_ms(5);
    return 0;
#endif
}
#endif	/* LCD_16X2_H */
