
#include <Driver_DAC_2023.h>
#include "GPIO2023.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/dac.h"


/****************************************************************************
* Function: Punteros que accede a los registros
* Preconditions: Ninguna
* Overview: Enmascara un registro de memoria de la ESP32 para poder identificarlo mejor
* Input:
* Output:
*En la documetacion podremos ver todos los BITS del registro y ver que hace cada uno de estos, esto solo enmascara para poder ver/usar de una manera mas comoda estos registros
*****************************************************************************/

volatile uint32_t * const ON_DAC1  = (uint32_t*)0x3FF48484;		//ON DAC
volatile uint32_t * const ON_DAC2  = (uint32_t*)0x3FF48488;		//ON DAC
volatile uint32_t * const SENS_SAR_DAC1  = (uint32_t*)0x3FF48898;		//ON DAC #640-DAC control-SENS_SAR_DAC_CTRL1_REG
volatile uint32_t * const SENS_SAR_DAC2  = (uint32_t*)0x3FF4889C;		//ON DAC #640-output control-SENS_SAR_DAC_CTRL2_REG DAC
volatile uint32_t * const CLK_CONF_REG  = (uint32_t*)0x3FF48070;		//Configuracion del Reloj en RTC

/****************************************************************************
* Function: dac_signal_conn_x
* Preconditions: Ninguna
* Overview: Llenado de estructura que define los canales de GPIO donde se encuentra el DAC (25 y 26)
* Input: Canal (0 o 1)
* Output: Ninguna
*
*****************************************************************************/

const dac_signal_conn_x dac_periph_signal =
{
    .dac_channel_io_num[0] = DAC_CHANNEL_1_GPIO,
    .dac_channel_io_num[1] = DAC_CHANNEL_2_GPIO,
};

/****************************************************************************
* Function: Dac_get_number
* Preconditions: Ninguna
* Overview: Obtiene el # de pin GPIO que corresponde al canal
* Input: Canal (0 o 1)
* Output: Ninguna
*
*****************************************************************************/
void Dac_get_number(dac_channel_x channel, gpio_num_x *gpio_num)
{
    *gpio_num = (gpio_num_x)dac_periph_signal.dac_channel_io_num[channel];
}

/****************************************************************************
* Function: Dac_dis_gpio
* Preconditions: Ninguna
* Overview: Deshabilita las funciones de GPIO del pin asociado al canal habilitado y calcula el GPIO del canal seleccionado
* Input: Canal (0 o 1)
* Output: Ninguna
*Nota: CANAL 0 = GPIO 25        CANAL 1 = GPIO 26
*****************************************************************************/
void Dac_dis_gpio(dac_channel_x channel)
{
	 gpio_num_x gpio_num = 0;
	    Dac_get_number(channel, &gpio_num);
	    rtc_gpio_init(gpio_num);
	    rtc_gpio_set_direction(gpio_num, RTC_GPIO_MODE_DISABLED);
	    rtc_gpio_pullup_dis(gpio_num);
	    rtc_gpio_pulldown_dis(gpio_num);
}

/****************************************************************************
* Function: Dac_enable_CH
* Preconditions: Ninguna
* Overview: Activa uno de los 2 canales conectados a GPIO 25 y 26
* Input: Canal (0 o 1)
* Output: Ninguna
*NOTA: Aqui se manda a llamar la funcion "Dac_dis_gpio" la cual desactiva lo relacionado con GPIO en estos pines (25 y 26).
*NOTA: Mientras que la siguiente funcion "Dac_ON" es la que manda a prender nuestro canal del DAC seleccionado
*****************************************************************************/
void Dac_enable_CH(dac_channel_x channel)
{

	Dac_dis_gpio(channel);  // Deshabilitar funciones del GPIO
	Dac_ON(channel);  //Prendemos el DAC con una estructuras
	//Antes se usaban estas funicones por separado pero ahora se incluten en "Dac_ON" para mayor comodidad
	//TURN_ON_DAC(channel);		//Prender DAC con Registro
	//TURN_ON_FORCE_DAC(channel);	//Prender DAC con Registro
	//
}

/****************************************************************************
* Function: Dac_ON
* Preconditions: Haber desacctivado las funciones de GPIO en el canal a usar
* Overview: Enciende el modulo DAC en el canal especificado
* Input: Canal (0 o 1)
* Output: Ninguno
*
*****************************************************************************/
void Dac_ON(dac_channel_x channel)
{
	Dac_dis_gpio(channel);  // Deshabilitar funciones del GPIO
	//Aqui se enciende el DAC escribiendo en el Registro
	TURN_ON_DAC(channel);
	//Antes se usaban estas funicones por separado pero ahora se incluten en "TURN_ON_DAC" para mayor comodidad
		//TURN_ON_DAC(channel);		//Prender DAC con Registro
		//TURN_ON_FORCE_DAC(channel);	//Prender DAC con Registro
	///Aqui se enciende el DAC usando estructuras
	//RTCIO.pad_dac[channel].dac_xpd_force = 1; // activación forzada de la alimentación (power-down) del DAC.
	//RTCIO.pad_dac[channel].xpd_dac = 1;			// activación de la alimentación (power-down) del DAC.

}

/****************************************************************************
* Function: Dac_OFF
* Preconditions: Haber desacctivado las funciones de GPIO en el canal a usar
* Overview: Apaga el modulo DAC en el canal especificado
* Input: Canal (0 o 1)
* Output: Ninguno
*
*****************************************************************************/
void Dac_OFF(dac_channel_x channel)
{
	//Aqui se apaga el DAC escribiendo en el Registro
	TURN_OFF_DAC(channel);
	///Aqui se apaga el DAC usando estructuras
    //RTCIO.pad_dac[channel].dac_xpd_force = 0;  // activación forzada de la alimentación (power-down) del DAC.
    //RTCIO.pad_dac[channel].xpd_dac = 0;	// activación de la alimentación (power-down) del DAC.
}
/****************************************************************************
* Function: Dac_out_voltage
* Preconditions: Haber llamado a la funcion Dac_ON
* Overview: Saca un valor de voltaje de 0 a 3.3v segun la conversion del DAC
* Input: Canal y valor de 0-255 a convertir
* Output: Ninguna
*
*****************************************************************************/
void Dac_out_voltage(dac_channel_x channel, uint8_t value)
{
	//Primero se comprueba si el canala usar es el 0 o el 1
      if (channel == DAC_CANAL_1)
    {
    	//Apagamos el generador de onda de el PIN del canal ya que no se usaara, se usara una salida fija
        CW_DAC1(0); //Desconctamos el Dac1 del generador

        //Mandamos el valor ingresado y almacenado en "value" para la salida del pin, esto se realiza con estucturas
        RTCIO.pad_dac[channel].dac = value;
        //Esta funcion solo funciona para valores fijos
        //OUT_DAC1(value);
    }
      //Primero se comprueba si el canala usar es el 0 o el 1
    else if (channel == DAC_CANAL_2)
    {
    	//Apagamos el generador de onda de el PIN del canal ya que no se usaara, se usara una salida fija
    	CW_DAC2(0); //Desconctamos el Dac1 del generador

    	   //Mandamos el valor ingresado y almacenado en "value" para la salida del pin, esto se realiza con estucturas
        RTCIO.pad_dac[channel].dac = value;
        //Esta funcion solo funciona para valores fijos
        //OUT_DAC2(value);
    }
}

int clk_8m_div = 0;      // RTC 8M clock divider (division is by clk_8m_div+1, i.e. 0 means 8MHz frequency)
//int frequency_step = 100;  // Frequency step for CW generator															#638

int invert = 1;          // invert MSB to get sine waveform  // 3: invert 180°
int Cw= 1;
/* - 00: does not invert any bits,
* - 01: inverts all bits,
* - 10: inverts MSB,
* - 11: inverts all bits except for MSB
* */
int INV_ON=3;
int INV_ON2=3;
//
//REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_CK8M_DIV_SEL, clk_8m_div);
   					//SET_PERI_REG_BITS(SENS_SAR_DAC_CTRL1_REG, SENS_SW_FSTEP, frequency_step, SENS_SW_FSTEP_S);
/****************************************************************************
* Function: CW generator (Generador de onda
* Preconditions: Haber habilitado el DAC con Dac_ON
* Overview: Activamos el Generador para una Onda Sinusoidal con la frecuencia que se especifique
* Input: Canal (0 o 1)
* * Input: frecuencia
* * Input: Offset
* * Input: Escala
* Output: Ninguna
*
*****************************************************************************/
void ON_CW(dac_channel_x channel,int frecuencia,int Offset,int Scale){ //CANAL-FREC-OFFSET-ESCALA
	//Instanciamos la estructura con los valores del usuario
	 ParametrosConfigCW parametros;
	 parametros.channel = channel; //Valor del canal
	    parametros.frecuencia = frecuencia;	// Valor de la frecuencia
	    parametros.Offset = Offset;	//Valor del Offset
	    parametros.Scale = Scale;	// Valor de la escala
	    //Solo se puede pasar un puntero como parametros por eso se crea una estructura con los valores deseados y que se guarden en esta (puntero = parametros)
	   //Se crea una tarea que mande a llamarejecutar el generador de onda con los valores que se guardadron en la esctructura
	    xTaskCreate(Config_CW, "Config_CW", 1024*3, &parametros, 10, NULL);
	    //Este es el tamaño del stack (pila) 3KB (1kb = 1024) * (3) = 3kb
}
//Ahora nuestra funcion aceptara un puntero en donde estaran todos nuestros datos necesarios para hacer funcionar el generador de onda
void Config_CW(void *parametros){
	// Convierte el puntero a la estructura de parámetros
	    ParametrosConfigCW *misParametros = (ParametrosConfigCW *)parametros;

	    // Accede a los parámetros de la estructura
	    dac_channel_x channel = misParametros->channel;	//Valor del canal
	    int frecuencia = misParametros->frecuencia;	// Valor de la frecuencia
	    int Offset = misParametros->Offset;	 //Valor del Offset
	    int Scale = misParametros->Scale; 	// Valor de la escala  #638

	 // Se habilita el generador de ONDA (este se usa en ambos canales)por lo que se hace solo 1 vez sin importar e canal a usar
	    Enable_CW(1);	//Funcion que prende/Habillita el Generador de Onda
	    DAC_DMA(0);		//Apagamos la funicon de DMA en el Dac ya que quien se encargara d ela salida es el Generador
	    	CK8M_OFF;		//Se desactiva el incremento de el generador de onda por 8M

	    switch(channel) {
	        case DAC_CANAL_1:
	            // Se conecta el generador a el canal 1
	        	CW_DAC1(1);
	        	DAC_CLK_Scale1(Scale); //Amplitud
	        	DAC_CLK_Offset1(Offset);//Offset
	        	DAC_CLK_INV1(INV_ON); // Se invierte MSB o viceversa para que el generador funcione

	            break;
	        case DAC_CANAL_2:
	        	 // Se conecta el generador a el canal 2
	        	CW_DAC2(1);
	        	 // Se invierte MSB o viceversa para lograr tener una onda mejor
	        	//SENS.sar_dac_ctrl2.dac_inv2 = 2;
	        	DAC_CLK_Scale2(Scale);//Amplitud
	        	DAC_CLK_Offset2(Offset);//Offset
	        	DAC_CLK_INV2(INV_ON2);// Se invierte MSB o viceversa para que el generador funcione

	            break;
	        default :
	        	printf("......\n");
	    }
	    //Ya por ultimo con un while se manda a la salida del DAC (PIN) el valor de la frecuencia que se establecio
	            while(1){

	                   // Se ajusta la frecuencia
	            	FREC_DAC(frecuencia)
	                   vTaskDelay(2000/10);	//función de FreeRTOS,hacer que una tarea se suspenda (se detenga) durante un período de tiempo específico antes de volver a ejecutarse

	            }
	    }

