/*****************************************************************************
 *  FileName:        BSP.h
 *  Dependencies:    Ninguna
 *  Processor:       ESP32
 *  Board:           ESP32
 *  Program version: Eclipse
 *  Company:         TecNM /IT Chihuahua
 *  Description:     Incluye la capa de abstraccion de los drivers.
 *  Authors:         Kevin Galaviz, Wendy Marquez, Mario Marcial y Raul Rodriguez
 *   Created on:     Junio 2023
 *   Updated:
  **/
/************************************************************************************************
 * * Copyright (C) 2023 by Kevin Galaviz - TecNM /IT Chihuahua
 *
 * Se permite la redistribucion, modificacion o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 * Alfredo Chacon y el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/

#ifndef BSP_H
#define BSP_H
#pragma once

//Register Bits{{
#define BIT31   0x80000000
#define BIT30   0x40000000
#define BIT29   0x20000000
#define BIT28   0x10000000
#define BIT27   0x08000000
#define BIT26   0x04000000
#define BIT25   0x02000000
#define BIT24   0x01000000
#define BIT23   0x00800000
#define BIT22   0x00400000
#define BIT21   0x00200000
#define BIT20   0x00100000
#define BIT19   0x00080000
#define BIT18   0x00040000
#define BIT17   0x00020000
#define BIT16   0x00010000
#define BIT15   0x00008000
#define BIT14   0x00004000
#define BIT13   0x00002000
#define BIT12   0x00001000
#define BIT11   0x00000800
#define BIT10   0x00000400
#define BIT9     0x00000200
#define BIT8     0x00000100
#define BIT7     0x00000080
#define BIT6     0x00000040
#define BIT5     0x00000020
#define BIT4     0x00000010
#define BIT3     0x00000008
#define BIT2     0x00000004
#define BIT1     0x00000002
#define BIT0     0x00000001
//}}

#define BIT63    (0x80000000ULL << 32)
#define BIT62    (0x40000000ULL << 32)
#define BIT61    (0x20000000ULL << 32)
#define BIT60    (0x10000000ULL << 32)
#define BIT59    (0x08000000ULL << 32)
#define BIT58    (0x04000000ULL << 32)
#define BIT57    (0x02000000ULL << 32)
#define BIT56    (0x01000000ULL << 32)
#define BIT55    (0x00800000ULL << 32)
#define BIT54    (0x00400000ULL << 32)
#define BIT53    (0x00200000ULL << 32)
#define BIT52    (0x00100000ULL << 32)
#define BIT51    (0x00080000ULL << 32)
#define BIT50    (0x00040000ULL << 32)
#define BIT49    (0x00020000ULL << 32)
#define BIT48    (0x00010000ULL << 32)
#define BIT47    (0x00008000ULL << 32)
#define BIT46    (0x00004000ULL << 32)
#define BIT45    (0x00002000ULL << 32)
#define BIT44    (0x00001000ULL << 32)
#define BIT43    (0x00000800ULL << 32)
#define BIT42    (0x00000400ULL << 32)
#define BIT41    (0x00000200ULL << 32)
#define BIT40    (0x00000100ULL << 32)
#define BIT39    (0x00000080ULL << 32)
#define BIT38    (0x00000040ULL << 32)
#define BIT37    (0x00000020ULL << 32)
#define BIT36    (0x00000010ULL << 32)
#define BIT35    (0x00000008ULL << 32)
#define BIT34    (0x00000004ULL << 32)
#define BIT33    (0x00000002ULL << 32)
#define BIT32    (0x00000001ULL << 32)

#ifndef __ASSEMBLER__
#ifndef BIT
#define BIT(nr)                 (1UL << (nr))
#endif
#ifndef BIT64
#define BIT64(nr)               (1ULL << (nr))
#endif
#else
#ifndef BIT
#define BIT(nr)                 (1 << (nr))
#endif
#endif


















/************************************************
ENUMERACION PARA ACCESO A GPIO
 ************************************************/
typedef enum {
    GPIO_N_NC = -1,    /*!< Use to signal not connected to S/W */
    GPIO_N_0 = 0,     /*!< GPIO0, input and output */
    GPIO_N_1 = 1,     /*!< GPIO1, input and output */
    GPIO_N_2 = 2,     /*!< GPIO2, input and output */
    GPIO_N_3 = 3,     /*!< GPIO3, input and output */
    GPIO_N_4 = 4,     /*!< GPIO4, input and output */
    GPIO_N_5 = 5,     /*!< GPIO5, input and output */
    GPIO_N_6 = 6,     /*!< GPIO6, input and output */
    GPIO_N_7 = 7,     /*!< GPIO7, input and output */
    GPIO_N_8 = 8,     /*!< GPIO8, input and output */
    GPIO_N_9 = 9,     /*!< GPIO9, input and output */
    GPIO_N_10 = 10,   /*!< GPIO10, input and output */
    GPIO_N_11 = 11,   /*!< GPIO11, input and output */
    GPIO_N_12 = 12,   /*!< GPIO12, input and output */
    GPIO_N_13 = 13,   /*!< GPIO13, input and output */
    GPIO_N_14 = 14,   /*!< GPIO14, input and output */
    GPIO_N_15 = 15,   /*!< GPIO15, input and output */
    GPIO_N_16 = 16,   /*!< GPIO16, input and output */
    GPIO_N_17 = 17,   /*!< GPIO17, input and output */
    GPIO_N_18 = 18,   /*!< GPIO18, input and output */
    GPIO_N_19 = 19,   /*!< GPIO19, input and output */
    GPIO_N_20 = 20,   /*!< GPIO20, input and output */
    GPIO_N_21 = 21,   /*!< GPIO21, input and output */
    GPIO_N_22 = 22,   /*!< GPIO22, input and output */
    GPIO_N_23 = 23,   /*!< GPIO23, input and output */
    GPIO_N_25 = 25,   /*!< GPIO25, input and output */
    GPIO_N_26 = 26,   /*!< GPIO26, input and output */
    GPIO_N_27 = 27,   /*!< GPIO27, input and output */
    GPIO_N_28 = 28,   /*!< GPIO28, input and output */
    GPIO_N_29 = 29,   /*!< GPIO29, input and output */
    GPIO_N_30 = 30,   /*!< GPIO30, input and output */
    GPIO_N_31 = 31,   /*!< GPIO31, input and output */
    GPIO_N_32 = 32,   /*!< GPIO32, input and output */
    GPIO_N_33 = 33,   /*!< GPIO33, input and output */
    GPIO_N_34 = 34,   /*!< GPIO34, input mode only */
    GPIO_N_35 = 35,   /*!< GPIO35, input mode only */
    GPIO_N_36 = 36,   /*!< GPIO36, input mode only */
    GPIO_N_37 = 37,   /*!< GPIO37, input mode only */
    GPIO_N_38 = 38,   /*!< GPIO38, input mode only */
    GPIO_N_39 = 39,   /*!< GPIO39, input mode only */
    GPIO_N_MAX,
/** @endcond */
} gpio_n_t;

/************************************************
DefiniciÓn de botones.
 ************************************************/
#define BSP_BTN1 12		/*	BOTON 1 (GPIO12) */
#define BSP_BTN2 34		/*	BOTON 1 (GPIO34) */

#define BOARD_BTN_NORMAL_STATE_BTN2 0	// Estado normal del boton 2
/************************************************
Definición de led's plasmados en tarjeta.
************************************************/
#define BSP_LED0 18
#define BSP_LED1 5
#define BSP_LED2 17
#define BSP_LED3 16
#define BSP_LED4 4
#define BSP_LED5 2
#define BSP_LED6 15

#define BSP_LED_H 0		/* Led encendido */
#define BSP_LED_L 1		/* Led apagado   */

/****************************************************
Para configurar los GPIO como entrado o como salida
****************************************************/
#define GPIO_OUT 1
#define GPIO_IN 0

#endif	/* BSP_H_ */


#define DacONF 10
#define DacON 18
#define DacOut 19
#define N 524288
#define vv 133693440
