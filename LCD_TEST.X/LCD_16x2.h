/*
 * #############################################################################
 *     filename:        LCD_16x2.h
 * #############################################################################
 *     Libreria de comandos para LCD 16x2
 * #############################################################################
 * 
 *       Autor:              Luis Arenas
 *       Organización:       TeamWork BP
 * 
 *       Revisión:           2.0
 *       Fecha:              Mayo. 2019
 *       Compilador:         XC8
 * 
 * #############################################################################
 * 
 *       FUNCIONES PRINCIPALES:
 * 
 * - void LCD_Init(void)
 *       Secuencia de inicialización del LCD
 *       Se debe ejecutar antes de usar cualquier otra función!!!
 * 
 * - void LCD_Command(char cmd)
 *      Envia un comando al LCD 
 *      -> LCD_Command(DISPLAY_CTRL + DISPLAY_ON + CURSOR_ON + BLINK_ON);
 *
 * - void LCD_Clear(void)
 *       Limpia la memoria y pantalla del LCD
 * 
 * - void LCD_Home(void)
 *       Envia el cursor y pantalla a la posicion de inicio (fila 1, columna 1)
 * 
 * - void LCD_Display(void)
 *       Habilita la visualizacion de texto en pantalla.
 * 
 * - void LCD_noDisplay(void)
 *       Deshabilita la visualizacion de texto en pantalla.
 * 
 * - void LCD_Cursor(void)
 *       Habilita la visualizacion del cursos en pantalla.
 * 
 * - void LCD_noCursor(void)
 *       Deshabilita la visualizacion del cursos en pantalla.
 * 
 * - void LCD_Blink(void)
 *       Si el cursor se encuentra visible, este se visualizará como un cuadro
 *       parpadeando.
 * 
 * - void LCD_noBlink(void)
 *       Si el cursor se encuentra visible, este se visualizará como una linea
 *       estatica.
 * 
 * - void LCD_scrollDisplayLeft(void)
 *       Permite desplazar la pantalla a la izquierda para mostrar los
 *       caracteres ocultos en memoria.
 * 
 * - void LCD_scrollDisplayRight(void)
 *       Permite desplazar la pantalla a la derecha para mostrar los caracteres
 *       ocultos en memoria.
 * 
 * - void LCD_leftToRight(void)
 *       Cada vez que se escriba un caracter, el cursor se desplazará a la
 *       izquierda.
 * 
 * - void LCD_rightToLeft(void)
 *       Cada vez que se escriba un caracter, el cursor se desplazará a la
 *       derecha.
 * 
 * - void LCD_Autoscroll(void)
 *       La pantalla se desplazará automaticamente al escribir un nuevo
 *       caracter.
 * 
 * - void LCD_noAutoscroll(void)
 *       La pantalla permanecerá estatica en su posicion actual.
 * 
 * - void LCD_SetCursor( char row, char column)
 *       Posiciona el cursor en la fila y columna indicada.
 *       [ambos empiezan con 0]
 * 
 * - void LCD_Char( char character)
 *       Escribe un caracter.
 *       ->LCD_Char('P')
 * 
 * - void LCD_Char_pos(char row, char col, char character)
 *       Escribe un caracter en la fila y columna(row, col)
 *       -> LCD_Char_pos(0,2,'P')
 * 
 * - void LCD_Text(char *text)
 *       Escribe una cadena de caracteres.
 *       -> char string[] = "Hello";
 *          LCD_TextOut(string);
 * 
 * - void LCD_Text_pos(char row, char col, char *num)
 *       Escribe una cadena de caracteres en la fila y columna (row, col).
 *       -> char string[] = "Hello";
 *          LCD_TextOut_pos(0,0,string);
 * 
 * - void LCD_PrintNumber(int *text)
 *       Escribe un número entero [+/-].
 *       -> int num = -120;
 *          LCD_PrintNumber(num);
 * 
 * - void LCD_PrintNumber_pos(char row, char col,int num)
 *       Escribe un número entero en la fila y columna (row, col).
 *       -> int num = -120;
 *          LCD_PrintNumber_pos(0,5,num);
 * 
 * - void LCD_CreateChar(char pos,char pt[])
 *       Almacena en la memoria CGRAM del LCD un caracter personalizado (pt[])
 *       en la posicion o indice determinado (pos).
 *       -> char man[]={
 *          b01110,
 *          b01110,
 *          b00101,
 *          b11111,
 *          b10100,
 *          b01110,
 *          b11011,
 *          };
 *          LCD_CreateChar(0,man);
 * 
 * #############################################################################
 */

#ifndef LCD_16X2_H
#define	LCD_16X2_H

#include <xc.h>

//*********************** CONFIGURACION DE LCD-PIC *****************************

/*
 * Definir los pines de conexion del microcontrolador al LCD.
 * Notas:
 * - Los pines de D0-D7 [Modo: 8-bits] o D4-D7 [4-bits] deben estar en el mismo
 *   puerto y en el mismo orden de bits del uC.
 *
 * - Los pines E, RS y RW pueden estar en otros puertos y pines del uC.
 *
 * - Si no se utiliza RW, se debe comentar la linea "#define LCD_RW"
 *   (Comentar: colocar al principio "//" de la linea)
 *
 * - Si el LCD está en modo 8-bits descomentar #define LCD_USE_8BITS_DATA
 *   (Descomentar: borrar "//" de la linea)
 */

//#define LCD_USE_8BIT_DATA

#define LCD_E       LATDbits.LATD3
#define LCD_E_DIR   TRISDbits.TRISD3
#define LCD_RW      LATAbits.LATA0
#define LCD_RW_DIR  TRISAbits.TRISA0
#define LCD_RS      LATDbits.LATD2
#define LCD_RS_DIR  TRISDbits.TRISD2         

#define LCD_D4_IN   PORTDbits.RD4
#define LCD_D5_IN   PORTDbits.RD5
#define LCD_D6_IN   PORTDbits.RD6
#define LCD_D7_IN   PORTDbits.RD7

#define LCD_D4_OUT  LATDbits.LATD4
#define LCD_D5_OUT  LATDbits.LATD5
#define LCD_D6_OUT  LATDbits.LATD6
#define LCD_D7_OUT  LATDbits.LATD7

#define LCD_D4_DIR  TRISDbits.TRISD4
#define LCD_D5_DIR  TRISDbits.TRISD5
#define LCD_D6_DIR  TRISDbits.TRISD6
#define LCD_D7_DIR  TRISDbits.TRISD7

#ifdef LCD_USE_8BIT_DATA
#define LCD_D0_IN   PORTDbits.RD0
#define LCD_D1_IN   PORTDbits.RD1
#define LCD_D2_IN   PORTDbits.RD2
#define LCD_D3_IN   PORTDbits.RD3

#define LCD_D0_OUT  LATDbits.LATD0
#define LCD_D1_OUT  LATDbits.LATD1
#define LCD_D2_OUT  LATDbits.LATD2
#define LCD_D3_OUT  LATDbits.LATD3

#define LCD_D0_DIR  TRISDbits.TRISD0
#define LCD_D1_DIR  TRISDbits.TRISD1
#define LCD_D2_DIR  TRISDbits.TRISD2
#define LCD_D3_DIR  TRISDbits.TRISD3

#define LCD_DIR_IN()    TRISD = 0xFF
#define LCD_DIR_OUT()   TRISD = 0x00
#warning "Configuracion LCD-8BIT !!!"
#else
#define LCD_DIR_IN()    TRISD |= 0xF0
#define LCD_DIR_OUT()   TRISD &= 0x0F
#warning "Configuracion LCD-4BIT !!!"
#endif

// Si el LCD esta en Modo: 4-bits
#ifndef LCD_USE_8BIT_DATA
#define LCD_D3_OUT  LCD_D7_OUT
#define LCD_D2_OUT  LCD_D6_OUT
#define LCD_D1_OUT  LCD_D5_OUT
#define LCD_D0_OUT  LCD_D4_OUT
#define LCD_D3_IN   LCD_D7_IN
#endif

//*************** CONFIGURACIÓN DE TIEMPOS/RETARDOS/INTENTOS *******************

#define LCD_TIMEOUT 100     // max # de revisiones "busy"

#define LCD_DELAY_15MS() __delay_ms(15)
#define LCD_DELAY_5MS() __delay_ms(5)
#define LCD_DELAY_1US() __delay_us(1)

//********************* COMANDOS E INSTRUCCIONES *******************************

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

#define LCD_READ        1   //LCD_RW - Modo Lectura
#define LCD_WRITE       0   //LCD_RW - Modo Escritura
#define LCD_CMD         0   //LCD_RS - Modo Comando
#define LCD_DATA        1   //LCD_RS - Modo Dato

#define LCD_BUSY        1   // busy flag logic

#define LCD_ENABLE()    LCD_E = 1;
#define LCD_DISABLE()   LCD_E = 0;
#define LCD_STROBE()    LCD_E = 1; LCD_DELAY_1US(); LCD_E = 0;

#define LINE_OFFSET     0x40    // Registro de inicio de la 2da fila

//********************** BUFFER, VARIABLES DE CONTROL **************************

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

// ************************ FUNCIONES LCD **************************************


void LCD_Init(void);
/*
 * Función LCD_Init()
 *  Permite inicializar el LCD y la libreria para su correcta ejecución.
 *  Esta función se debe ejecutar al principio y antes de utilizar las demas
 *  funciones de la libreria.
 */

void LCD_Write(char value, char mode);
/*
 * Función LCD_Write()
 *  Permite enviar la informacion al LCD según la configuracion establecida
 *  [8-bits/4-bits].
 *  Antes de ejecutarse esta función, se debe establecer RS si la informacion es
 *  dato o comando.
 *
 *  value: Dato o comando a enviar.
 *  mode:  Para modo 4-bits, si es 1, solo envía el nibble alto, y si es 0,
 *         envía los 2 nibbles.
 *
 */

void LCD_Text(void *text);
/*
 * Función LCD_Text()
 *   Visualiza en el LCD una cadena de caracteres o texto.
 *  text: texto o cadena de caracteres a visualizar
 *
 *  Por ejemplo, se desea visualizar el mensaje "hola" en el LCD.
 *  LCD_Text("hola");
 *
 */

#define LCD_Text_pos(row,col,text) LCD_SetCursor(row,col);LCD_Text(text)
/*
 * Función LCD_Text_pos()
 *  Visualiza en el LCD una cadena de caracteres o texto en determinada posición
 *  según (row,col).
 *
 *  row:  Fila
 *  col:  Columna
 *  text: Texto o cadena de caracteres a visualizar
 *  
 *  Por ejemplo, se desea visualizar "hola" a partir de la fila 1 y columna 3
 *  LCD_Text_pos(0,2,"hola");
 *
 */

void LCD_CustomChar(void *pt);
/*
 * 
 * Función LCD_CustomChar()
 *  Permite almacenar en la memoria CGRAM del LCD, un caracter personalizado.
 *  Antes de ejecutar esta función, se debe ejecutar LCD_CustomMem(...) para
 *  especificar en que posicion de la memoria se va a almacenar el nuevo
 *  caracter.
 *
 *  pt: Array[7] de datos que conforman el caracter personalizado.
 *
 */


#define LCD_CreateChar(pos,pt)   LCD_CustomMem(pos); LCD_CustomChar(pt)
/*
 * Función LCD_CreateChar()
 *  Permite almacenar en la memoria CGRAM del LCD un caracter personalizado en
 *  una posicion determinada de dicha memoria.
 *  
 *  pos:  Posición en memoria CGRAM del LCD para almacenar el caracter
 *        personalizado.
 *
 */

#define LCD_PrintNumber(num) LCD_print_number((unsigned long)num,num>0?0:1u)
/*
 * Función LCD_PrintNumber()
 *  Permite visualizar en el LCD un número entero [+/-].
 *  
 *  num: Número entero a visualizar en el LCD.
 *  
 */

#define LCD_PrintNumber_pos(row,col,num) LCD_SetCursor(row,col);LCD_PrintNumber(num)
/*
 * Función LCD_PrintNumber_pos()
 *  Permite visualizar en el LCD un número entero [+/-] en determinada posición
 *  según (row,col).
 *  row:  Fila
 *  col:  Columna
 *  num:  Número entero a visualizar en el LCD.
 *  
 *  Por ejemplo, se desea visualizar -123 a partir de la fila 2 y columna 5
 *  LCD_PrintNumber_pos(1,4,-123);
 *
 */

unsigned char LCD_Busy(void);
/*
 * Función LCD_Busy()
 *  Si RW esta configurado a un pin del uC, esta función permite la comprobación
 *  de si el LCD se encuentra disponible para recibir una nueva instrucción o
 *  comando.
 *  Si RW no está configurado, realiza un retardo para esperar a que el LCD se
 *  encuentre desocupado.
 */

#define LCD_Write_Nibble(dato)  LCD_RS = LCD_CMD; LCD_Write(dato,0)
/*
 * Función LCD_Write_Nibble()
 *  Permite enviar, en modo 4-bits, solo el nibble alto, y en modo 8-bits, el
 *  dato completo (2 nibbles) al LCD. Dicho dato se envia al LCD en modo COMANDO
 *  [RS=0].
 *  
 *  dato: COMANDO a enviar al LCD
 *  
 */

#define LCD_DISPLAY_CTRL()      LCD_Command((unsigned)DISPLAY_CTRL | _displaycontrol)
/*
 * Función LCD_DISPLAY_CTRL()
 *  Envia al LCD el COMANDO DISPLAY_CONTROL previamente configurado con las
 *  condiciones ngresadas en _displaycontrol.
 *
 *  Por ejemplo, se desea configurar el LCD para que el cursor este encendido,
 *  no haya parpadeo del cursor y se habilite la visualizacion de las letras en
 *  memoria.
 *
 *  _displaycontrol = DISPLAY_ON | CURSOR_ON | BLINK_OFF;
 *  LCD_DISPLAY_CTRL();
 */

#define LCD_ENTRY_MODE()        LCD_Command((unsigned)ENTRY_MODE | _displaymode)
/*
 * Función LCD_ENTRY_MODE()
 *  Envia al LCD el COMANDO ENTRY_MODE previamente configurado con las
 *  condiciones ingresadas en _displaymode.
 *
 *  Por ejemplo, se desea configurar el LCD para que el cursor se desplace a la
 *  izquierda y no haya desplazamiento de la pantalla.
 *
 *  _displaymode = CURSOR_INC | DISPLAY_SHIFT_OFF;
 *  LCD_ENTRY_MODE();
 */

#define LCD_Clear()             LCD_Command(CLEAR_DISPLAY)
/*
 * Función LCD_Clear()
 *  Permite Limpear la pantalla y regresar el cursor a la posicion inicial
 *  [fila 1, columna 1].
 *  
 */

#define LCD_Home()              LCD_Command(RETURN_HOME)
/*
 * Función LCD_Home()
 *  Permite regresar el cursor y pantalla a la posicion inicial
 *  [fila 1, columna 1].
 *  
 */

#define LCD_Display()           _displaycontrol |= DISPLAY_ON; LCD_DISPLAY_CTRL()
/*
 * Función LCD_Display()
 *  Permite configurar al LCD para mostrar el mensaje a visualizar en la
 *  pantalla.
 *  
 */

#define LCD_noDisplay()         _displaycontrol &= ~DISPLAY_ON; LCD_DISPLAY_CTRL()
/*
 * Función LCD_noDisplay()
 *  Permite configurar al LCD para ocultar los caracteres de la pantalla.
 *  
 */

#define LCD_Cursor()            _displaycontrol |= CURSOR_ON; LCD_DISPLAY_CTRL()
/*
 * Función LCD_Cursor()
 *  Permite configurar al LCD para mostrar el cursos de la pantalla.
 *
 */

#define LCD_noCursor()          _displaycontrol &= ~CURSOR_ON; LCD_DISPLAY_CTRL()
/*
 * Función LCD_noCursor()
 *  Permite configurar al LCD para ocultar el cursos de la pantalla.
 *  
 */

#define LCD_Blink()             _displaycontrol |= BLINK_ON; LCD_DISPLAY_CTRL()
/*
 * Función LCD_Blink()
 *  Permite configurar el LCD para parpadear el cursor de la pantalla si es que
 *  se encuentra habilitado su visualización.
 *  
 */

#define LCD_noBlink()           _displaycontrol &= ~BLINK_ON; LCD_DISPLAY_CTRL()
/*
 * Función LCD_noBlink()
 *  Permite configurar el LCD para no parpadear el cursor de la pantalla si es
 *  que se encuentra hilitado su visualización.
 *  
 */

#define LCD_scrollDisplayLeft()  LCD_Command(DISPLAY_SHIFT_L)
/*
 * Función LCD_scrollDisplayLeft()
 *  Permite desplazar la pantalla a la izquierda para mostrar los caracteres
 *  ocultos en memoria.
 *  
 */

#define LCD_scrollDisplayRight() LCD_Command(DISPLAY_SHIFT_R)
/*
 *  Función LCD_scrollDisplayRight()
 *  Permite desplazar la pantalla a la derecha para mostrar los caracteres
 *  ocultos en memoria.
 *  
 */

#define LCD_leftToRight()       _displaymode |= CURSOR_INC;; LCD_ENTRY_MODE()
/*
 * Función LCD_leftToRight()
 *  Permite configurar al LCD para que el cursor se desplace de izquierda a
 *  derecha al escribir un caracter.
 *  
 */

#define LCD_rightToLeft()       _displaymode &= ~CURSOR_INC; LCD_ENTRY_MODE()
/*
 * Función LCD_rightToLeft()
 *  Permite configurar al LCD para que el cursor se desplace de derecha a
 *  izquierda al escribir un caracter.
 *  
 */

#define LCD_Autoscroll()        _displaymode |= DISPLAY_SHIFT_ON;; LCD_ENTRY_MODE()
/*
 * Función LCD_Autoscroll()
 *  Permite configurar al LCD para que la pantalla se desplace automaticamente
 *  al escribir un nuevo caracter. El cursor permanecerá estático en su posicion
 *  actual.
 *  
 */

#define LCD_noAutoscroll()      _displaymode &= ~DISPLAY_SHIFT_ON; LCD_ENTRY_MODE()
/*
 * Función LCD_noAutoscroll()
 *  Permite configurar al LCD para que la pantalla no se desplace
 *  automaticamente al escribir un nuevo caracter. El cursor se desplazará
 *  dependiendo de la configuración previa.
 *  
 */

#define LCD_Command(dato)       while(LCD_Busy()); LCD_RS = LCD_CMD; LCD_Write(dato,1)
/*
 * Función LCD_Command()
 *  Permite enviar informacion al LCD en modo COMANDO [RS=0].
 *  
 */

#define LCD_Data(dato)          while(LCD_Busy()); LCD_RS = LCD_DATA; LCD_Write(dato,1)
/*
 * Función LCD_Data()
 *  Permite enviar informacion al LCD en modo DATA [RS=1].
 *  
 */

#define LCD_Char                LCD_Data
/*
 * Función LCD_Char()
 *  Permite enviar caracteres al LCD segun Tabla ASCII.
 *
 *  Por ejemplo, se desea visualizar el caracter 'L' en el LCD.
 *  LCD_Char('L')
 *  
 */

#define LCD_Char_pos(row,col,c) LCD_SetCursor(row,col); LCD_Data(c)
/*
 * Función LCD_Char_pos()
 *  Permite enviar caracteres al LCD segun Tabla ASCII en una posicion
 *  determinada.
 *
 *  row:  Fila
 *  col:  Columna
 *  c: caracter aa visualizar
 *  
 *  Por ejemplo, se desea visualizar 'P' en la fila 1 y columna 4.
 *  LCD_Text_pos(0,3,'P');
 *
 */

#define LCD_SetCursor(row,col)      LCD_Command(CURSOR_ADDR + (LINE_OFFSET * row) + col)
/*
 * Función LCD_SetCursor()
 *  Permite configurar el LCD para posicionar el cursos en la fila y columna a
 *  especificar.
 *  
 *  row:  Fila
 *  col:  Columna
 *  
 *  Por ejemplo, se desea posicionar el cursor en la fila 1 y columna 4.
 *  LCD_SetCursor(0,3);
 *
 */

#define LCD_CustomMem(index)    LCD_Command(CGRAM_ADDR | ((index & 0x7) << 3))
/*
 * Función LCD_SetCursor()
 *  Permite configurar el LCD para posicionar el cursos en la fila y columna a
 *  especificar.
 *  
 *  index:  posicion en la memoria CGRAM del LCD.
 *  
 *  Por ejemplo, se desea especificar al LCD que se ingresará un caracter
 *  personalizado en la posicion 3 de la memoria CGRAM.
 *  LCD_CustomMem(2);
 *
 */

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
//******************************************************************************