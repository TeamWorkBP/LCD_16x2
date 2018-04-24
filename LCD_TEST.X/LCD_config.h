//##############################################################################
//    filename:        lcd_config.h
//##############################################################################
//    configuración de la libreria LCD_16x2  (pins, retardos, etc)
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

#ifndef _LCD_CONFIG_H
#define _LCD_CONFIG_H

#include <xc.h>

#define LCD_TIMEOUT 100     // max # de revisiones "busy"

#define LCD_DELAY_15MS() __delay_ms(15)
#define LCD_DELAY_5MS() __delay_ms(5)
#define LCD_DELAY_1US() Nop()//;Nop();Nop();Nop()
#warning "Make certain to define LCD-Delays properly !!!"

//Definir los pines de conexion del microcontrolador al LCD

//#define LCD_USE_8BIT_DATA

#define	LCD_E		LATDbits.LATD3
#define	LCD_E_DIR	TRISDbits.TRISD3
#define	LCD_RW		LATAbits.LATA0
#define	LCD_RW_DIR	TRISAbits.TRISA0
#define	LCD_RS		LATDbits.LATD2
#define	LCD_RS_DIR	TRISDbits.TRISD2         

#define	LCD_D4_IN	PORTDbits.RD4
#define	LCD_D5_IN	PORTDbits.RD5
#define	LCD_D6_IN	PORTDbits.RD6
#define	LCD_D7_IN	PORTDbits.RD7

#define	LCD_D4_OUT	LATDbits.LATD4
#define	LCD_D5_OUT	LATDbits.LATD5
#define	LCD_D6_OUT	LATDbits.LATD6
#define	LCD_D7_OUT	LATDbits.LATD7

#define	LCD_D4_DIR	TRISDbits.TRISD4
#define	LCD_D5_DIR	TRISDbits.TRISD5
#define	LCD_D6_DIR	TRISDbits.TRISD6
#define	LCD_D7_DIR	TRISDbits.TRISD7

#ifdef LCD_USE_8BIT_DATA
    #define	LCD_D0_IN	PORTDbits.RD0
    #define	LCD_D1_IN	PORTDbits.RD1
    #define	LCD_D2_IN	PORTDbits.RD2
    #define	LCD_D3_IN	PORTDbits.RD3

    #define	LCD_D0_OUT	LATDbits.LATD0
    #define	LCD_D1_OUT	LATDbits.LATD1
    #define	LCD_D2_OUT	LATDbits.LATD2
    #define	LCD_D3_OUT	LATDbits.LATD3

    #define	LCD_D0_DIR	TRISDbits.TRISD0
    #define	LCD_D1_DIR	TRISDbits.TRISD1
    #define	LCD_D2_DIR	TRISDbits.TRISD2
    #define	LCD_D3_DIR	TRISDbits.TRISD3

    #define LCD_DIR_IN()    TRISD = 0xFF
    #define LCD_DIR_OUT()   TRISD = 0x00
    #warning "Configuracion LCD-8BIT !!!"
#else
    #define LCD_DIR_IN()    TRISD |= 0xF0
    #define LCD_DIR_OUT()   TRISD &= 0x0F
    #warning "Configuracion LCD-4BIT !!!"
#endif

#endif //_LCD_CONFIG_H
