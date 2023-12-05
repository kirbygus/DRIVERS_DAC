
/*#ifndef GPIO2023_H
#define GPIO2023_H
#pragma once*/



/* Archivos de cabecera importantes. */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#pragma once
#include "ConfigDAC.h"

/* Board Support Package. */
#include "BSP.h"

extern volatile uint32_t * const ON_DAC1;
extern volatile uint32_t * const ON_DAC2;
extern volatile uint32_t * const SENS_SAR_DAC1;
extern volatile uint32_t * const SENS_SAR_DAC2;
extern volatile uint32_t * const DAC_CLK_INVF;
extern volatile uint32_t * const CLK_CONF_REG;

/************************************************
//Escrinimos en el regisstro
 ************************************************/
/* Enciende DAC */
/****************************************************************************
* Function: TURN_ON_DAC
* Preconditions: Ninguna
* Overview: Prendemos el DAC
* Input: 0 =  DAC 1 Y 1 = el DAC 2
* Output: Ninguna
*
*****************************************************************************/
#define TURN_ON_DAC(B)	if(B==0) /* Selecciona cual DAC encender*/ *ON_DAC1 |= (((int)pow((double)2,(double)DacON))+((int)pow((double)2,(double)DacONF))); \
						else if (B==1)   *ON_DAC2 |= (((int)pow((double)2,(double)DacON)))+((int)pow((double)2,(double)DacONF));

			/* Apaga DAC */
/****************************************************************************
* Function: TURN_OFF_DAC
* Preconditions: Ninguna
* Overview: Apagamos el DAC
* Input: 0 =  DAC 1 Y 1 = el DAC 2
* Output: Ninguna
*
*****************************************************************************/
#define TURN_OFF_DAC(B)	if(B==0) /* Selecciona cual DAC Apagar */ *ON_DAC1 &= ~(((int)pow((double)2,(double)DacON))+((int)pow((double)2,(double)DacONF))); \
						else if (B==1)   *ON_DAC2 &= ~(((int)pow((double)2,(double)DacON))+((int)pow((double)2,(double)DacONF)));



/****************************************************************************
* Function: DAC_DMA
* Preconditions: Ninguna
* Overview: Desactivamos/Prendemos DMA (Direct Acces Memory)
* Input: 0 =  Apagado Y 1 = Encendido
* Output: Ninguna
* Nota:  SENS_SAR_DAC1
*****************************************************************************/
#define DAC_DMA(B)	if(B==1) /* Use or Not DMA*/ *SENS_SAR_DAC1  |= (int)pow((double)2,(double)22); \
						else if (B==0)   *SENS_SAR_DAC1 &= ~(int)pow((double)2,(double)22);\

/****************************************************************************
* Function: DAC_CLK_INV_FH
* Preconditions: Ninguna
* Overview: inversión del reloj del DAC, Forces PDAC_CLK to be 1
* Input: 0 =  Apagado Y 1 = Encendido
* Output: Ninguna
* Nota:  SENS_SAR_DAC1
*****************************************************************************/
#define DAC_CLK_INV_FH(B)	if(B==1) /* Force HIGH*/ *SENS_SAR_DAC1 |= (int)pow((double)2,(double)24); \
						else if (B==0)   *SENS_SAR_DAC1 &= ~(int)pow((double)2,(double)24);
/****************************************************************************
* Function: DAC_CLK_INV_FL
* Preconditions: Ninguna
* Overview: inversión del reloj del DAC, Forces PDAC_CLK to be 0
* Input: 0 =  Apagado Y 1 = Encendido
* Output: Ninguna
* Nota:  SENS_SAR_DAC1
*****************************************************************************/
#define DAC_CLK_INV_FL(B)	if(B==1) /* Force LOW*/ *SENS_SAR_DAC1 |= (int)pow((double)2,(double)23); \
						else if (B==0)   *SENS_SAR_DAC1 &= ~(int)pow((double)2,(double)23);
/* Valor al DAC */
					// Prueba NO SIRVE
/****************************************************************************
* Function: OUT_DAC1
* Preconditions: Ninguna
* Overview: Da un valor de salida en el PIN DAC1
* Input: 0-255
* Output: Ninguna
* Nota:  Prueba NO SIRVE como deberia
* * Nota: 2^19 = 524288 que es donde se debe escribir en el registro
*****************************************************************************/
#define OUT_DAC1(B) 	 /* Salida Dac1*/ *ON_DAC1 |= ((524288)*(B));
/****************************************************************************
* Function: OUT_DAC2
* Preconditions: Ninguna
* Overview: Da un valor de salida en el PIN DAC2
* Input: 0-255
* Output: Ninguna
* Nota:  Prueba NO SIRVE como deberia
* * * Nota: 2^19 = 524288 que es donde se debe escribir en el registro
*****************************************************************************/
#define OUT_DAC2(B) 	 /* Salida Dac2*/ *ON_DAC2 |= ((524288)*(B));

//#define ROUT_DAC1 	 /* GPIO 0-31*/ *ON_DAC1 &= ~ (524287);
//#define ROUT_DAC1	 /* GPIO 0-31*/ *ON_DAC2 &= ~ (524287);


/* Generador de Onda "CW" */
/****************************************************************************
* Function: Enable_CW
* Preconditions: Ninguna
* Overview: Activamos el generador de Onda Sinusoidal
* Input: 1 = encendido, 0 = apagado
* Output: Ninguna
*****************************************************************************/
#define Enable_CW(B)	if(B==1) /* Enable CW*/ *SENS_SAR_DAC1 |= (int)pow((double)2,(double)16); \
						else if (B==0)   *SENS_SAR_DAC1 &= ~(int)pow((double)2,(double)16);
/****************************************************************************
* Function: CW_DAC1
* Preconditions: Ninguna
* Overview: Conectamos el generador al DAC 1 (PIN25)
* Input: 1 = encendido, 0 = apagado
* Output: Ninguna
*****************************************************************************/
#define CW_DAC1(B)	if(B==1) /* SELECT SOURCE DAC1 */ *SENS_SAR_DAC2 |= (int)pow((double)2,(double)24); \
						else if (B==0)   *SENS_SAR_DAC2 &= ~(int)pow((double)2,(double)24);
/****************************************************************************
* Function: CW_DAC1
* Preconditions: Ninguna
* Overview: Conectamos el generador al DAC 1 (PIN26)
* Input: 1 = encendido, 0 = apagado
* Output: Ninguna
*****************************************************************************/
#define CW_DAC2(B)	if(B==1) /* SELECT SOURCE DAC2 */ *SENS_SAR_DAC2 |= (int)pow((double)2,(double)25); \
						else if (B==0)   *SENS_SAR_DAC2 &= ~(int)pow((double)2,(double)25);
/****************************************************************************
* Function: USE_DMA
* Preconditions: Ninguna
* Overview: Se usa DMA para mostrar el valor por el PIN DAC
* Input: 1 = encendido, 0 = apagado
* Output: Ninguna
*****************************************************************************/
#define USE_DMA(B)	if(B==1) /* USE OR NOT DMA*/ *SENS_SAR_DAC1 |= (int)pow((double)2,(double)16); \
						else if (B==0)   *SENS_SAR_DAC1 &= ~(int)pow((double)2,(double)16);


/* Las siguientes funciones solo funcionan paraCalibrar "CW" */


/****************************************************************************
* Function: DAC_CLK_INV1
* Preconditions: Ninguna
* Overview: Invertimos la senal de reloj del generador DAC1
* Input: 00: does not invert any bits, 01: inverts all bits, 10: inverts MSB, 11: inverts
all bits except for MSB

* Output: Ninguna
* * * Nota:  Vease el PDF para mas nformacion
* * Nota:  Calibrar "CW"
*****************************************************************************/
#define DAC_CLK_INV1(B)	if(B==0) /* Invertir Senal DAC1*/ *SENS_SAR_DAC2 &= ~ (((int)pow((double)2,(double)21))+((int)pow((double)2,(double)20))); \
						else if (B==1)   *SENS_SAR_DAC2 |= (int)pow((double)2,(double)20);\
						else if (B==2)   *SENS_SAR_DAC2 |= (int)pow((double)2,(double)21);\
						else if (B==3)   *SENS_SAR_DAC2 |=  (((int)pow((double)2,(double)21))+((int)pow((double)2,(double)20)));
/****************************************************************************
* Function: DAC_CLK_INV2
* Preconditions: Ninguna
* Overview: Invertimos la senal de reloj del generador DAC2
* Input:  00: does not invert any bits, 01: inverts all bits, 10: inverts MSB, 11: inverts
all bits except for MSB

* Output: Ninguna
* * * Nota:  Vease el PDF para mas nformacion
* * Nota:  Calibrar "CW"
*****************************************************************************/
#define DAC_CLK_INV2(B)	if(B==0) /* Invertir Senal DAC2*/ *SENS_SAR_DAC2 &= ~ (((int)pow((double)2,(double)22))+((int)pow((double)2,(double)23))); \
						else if (B==1)   *SENS_SAR_DAC2 |= (int)pow((double)2,(double)22);\
						else if (B==2)   *SENS_SAR_DAC2 |= (int)pow((double)2,(double)23);\
						else if (B==3)   *SENS_SAR_DAC2 |=  (((int)pow((double)2,(double)22))+((int)pow((double)2,(double)23)));
/****************************************************************************
* Function: DAC_CLK_Scale1
* Preconditions: Ninguna
* Overview: Se escala la senal de reloj del generador DAC1
* Input: 00: no scale; 01: scale to 1/2; 10: scale to 1/4; 11: scale to 1/8. (R/W).

* Output: Ninguna
* * * Nota:  Vease el PDF para mas nformacion
* * Nota:  Calibrar "CW"
*****************************************************************************/
#define DAC_CLK_Scale1(B)	if(B==0) /* Escalar Senal*/  *SENS_SAR_DAC2 &= ~ (((int)pow((double)2,(double)17))+((int)pow((double)2,(double)16))); \
						else if (B==1)   *SENS_SAR_DAC2 |= (int)pow((double)2,(double)16);\
						else if (B==2)   *SENS_SAR_DAC2 |= (int)pow((double)2,(double)17);\
						else if (B==3)   *SENS_SAR_DAC2 |=  (((int)pow((double)2,(double)16))+((int)pow((double)2,(double)17)));
/****************************************************************************
* Function: DAC_CLK_Scale2
* Preconditions: Ninguna
* Overview: Se escala la senal de reloj del generador DAC2
* Input: 00: no scale; 01: scale to 1/2; 10: scale to 1/4; 11: scale to 1/8. (R/W).

* Output: Ninguna
* * * Nota:  Vease el PDF para mas nformacion
* * Nota:  Calibrar "CW"
*****************************************************************************/
#define DAC_CLK_Scale2(B)	if(B==0) /* Escalar Senal*/  *SENS_SAR_DAC2 &= ~ (((int)pow((double)2,(double)18))+((int)pow((double)2,(double)19))); \
		else if (B==1)   *SENS_SAR_DAC2 |= (int)pow((double)2,(double)18);\
		else if (B==2)   *SENS_SAR_DAC2 |= (int)pow((double)2,(double)19);\
		else if (B==3)   *SENS_SAR_DAC2 |=  (((int)pow((double)2,(double)18))+((int)pow((double)2,(double)19)));
/****************************************************************************
* Function: DAC_CLK_Offset1
* Preconditions: Ninguna
* Overview: Offset en la senal del generador, DC offset for DAC2 CW generator
* Input: 0-96

* Output: Ninguna
* * * Nota:  Vease el PDF para mas nformacion
* * Nota:  Calibrar "CW"
*****************************************************************************/
#define DAC_CLK_Offset1(O)	if(O<96) /* Offset*/ *SENS_SAR_DAC2 |= O; \
						else if (O>96)   *SENS_SAR_DAC2 |= O;
/****************************************************************************
* Function: DAC_CLK_Offset2
* Preconditions: Ninguna
* Overview: Offset en la senal del generador, DC offset for DAC2 CW generator
* Input: 0-255

* Output: Ninguna
* * * Nota:  Vease el PDF para mas nformacion
* * Nota:  Calibrar "CW"
*****************************************************************************/
#define DAC_CLK_Offset2(O)	if(O<128) /* Offset*/ *SENS_SAR_DAC2 |= 256*O;  \
						else if (O>127)   *SENS_SAR_DAC2 |= ((256*255)-(256*(O-128)))  ;//(O)+(int)pow((double)2,(double)8);


/****************************************************************************
* Function: CK8M_ON
* Preconditions: Ninguna
* Overview: CK8M force power up. Forzar encendido 8MHz
* Input: 1 = Activado

* Output: Ninguna
* * * Nota:  Vease el PDF para mas nformacion, vease la imagen 7 del PDF
* * Nota:  Calibrar "CW"
*****************************************************************************/
#define CK8M_ON /* Forzar encendido 8MHz*/ *CLK_CONF_REG |= (int)pow((double)2,(double)26);
/****************************************************************************
* Function: CK8M_OFF
* Preconditions: Ninguna
* Overview: CK8M force Down up. Forzar Apagado 8MHz
* Input: 1 = Activado,
* Output: Ninguna
* * * Nota:  Vease el PDF para mas nformacion, vease la imagen 7 del PDF
* * Nota:  Calibrar "CW"
*****************************************************************************/
#define CK8M_OFF /* Forzar Apagado 8MHz*/ *CLK_CONF_REG |= (int)pow((double)2,(double)6);

#define FREC_DAC(B)	 /* Ajustamos la frecuencia de ONDA DAC */ *SENS_SAR_DAC1 |= B;

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
* Function: Dac_enable_CH
* Preconditions: Ninguna
* Overview: Activa uno de los 2 canales conectados a GPIO 25 y 26
* Input: Canal (0 o 1)
* Output: Ninguna
*
*****************************************************************************/
void Dac_enable_CH(dac_channel_x channel);

/****************************************************************************
* Function: Dac_disable_CH
* Preconditions: Ninguna
* Overview: Desactiva uno de los 2 canales conectados a GPIO 25 y 26
* Input: Canal (0 o 1)
* Output: Ninguna
*
*****************************************************************************/
void Dac_disable_CH(dac_channel_x channel);

/****************************************************************************
* Function: Dac_out_voltage
* Preconditions: Haber llamado a la funcion Dac_enable_CH
* Overview: Saca un valor de voltaje de 0 a 3.3v segun la conversion del DAC
* Input: Canal y valor de 0-255 a convertir
* Output: Ninguna
*
*****************************************************************************/
void Dac_out_voltage(dac_channel_x channel, uint8_t value);

/****************************************************************************
* Function: Dac_dis_gpio
* Preconditions: Ninguna
* Overview: Deshabilita las funciones de GPIO del pin asociado al canal
* habilitado
* Input: Canal (0 o 1)
* Output: Ninguna
*
*****************************************************************************/
void Dac_dis_gpio(dac_channel_x channel);

/****************************************************************************
* Function: Dac_get_number
* Preconditions: Ninguna
* Overview: Obtiene el # de pin GPIO que corresponde al canal
* Input: Canal (0 o 1)
* Output: Ninguna
*
*****************************************************************************/
void Dac_get_number(dac_channel_x channel, gpio_num_x *gpio_num);

/****************************************************************************
* Function: Dac_ON
* Preconditions: Ninguns
* Overview: Enciende el módulo DAC
* Input: Canal (0 o 1)
* Output: Ninguna
*
*****************************************************************************/
void Dac_ON(dac_channel_x channel);

/****************************************************************************
* Function: Dac_OFF
* Preconditions: Ninguns
* Overview: Apaga el módulo DAC
* Input: Canal (0 o 1)
* Output: Ninguna
*
*****************************************************************************/
void Dac_OFF(dac_channel_x channel);

/****************************************************************************
* Function: ON_CW
* Preconditions: Haber habilitado el DAC a usar
* Overview: Predne el generador de onda
* Input: Canal, frecuencia, offset, scale
* Output: Ninguna
*
*****************************************************************************/

void ON_CW(dac_channel_x channel,int frecuencia,int Offset,int Scale);
/****************************************************************************
* Function: Config_CW
* Preconditions: haber habilitado "ON_CW"
* Overview: Funcion que se activa dentro de "ON_CW"
* Input: LOS PARAMETROS = (Canal, frecuencia, offset, scale)
* Output: Ninguna
*
*****************************************************************************/
void Config_CW(void *parametros);

#ifdef __cplusplus
}
#endif
