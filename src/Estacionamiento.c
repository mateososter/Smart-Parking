/*
===============================================================================
 Name        : Estacionamiento.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "chip.h"
#include "board.h"
#include "LPC17xx.h"
#include <cr_section_macros.h>
#include "lcd.h"
#include "string.h"
#include "pwm.h"

// TODO: insert other include files here


// TODO: insert other definitions and declarations here

#define True 		1
#define False 		0
#define msgDOC		""
#define msgDISC		""
#define msgALU		""

int flag;
int pulse;

void LeeTarjeta(char*);

int main(void) {

	// Inicializamos la placa
		Board_Init();

	/*	===================================================================*
	 *	Configuramos los pines que vamos a utilizar para nuestra aplicación*
	 *	===================================================================*/

	/*	Los pines utilizados para el display se configuran a través de la librería libLCD
	 * 	D4 p2.5 (J6-47)
	 * 	D5 p2.6 (J6-48)
	 * 	D6 p2.7 (J6-49)
	 * 	D7 p2.8 (J6-50)
	 * 	RS p2.0 (J6-42)
	 * 	EN p2.1 (J6-43)	 												*/
	/* Configuración del GPIO P0.18 como entrada */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, GPIOINT_PORT0, 18);
	/* Configuración de la interrupción por flanco descendente */
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIOINT_PORT0, 1 << 18);

	/*	===================================================================	*
	 *	Habilitamos las interrupciones e inicializamos el display			*
	 *	===================================================================	*/

	/* Habilitación de las interrupciones de los GPIO en el NVIC */
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);
	// Inicializamos el display y actualizamos el valor del clock
	LCD_Init();
	LCD_Tim1DeInit();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	LCD_Tim1Init();
	LCD_SendInstruction(LCD_DISPLAY_CLEAR);

	// Defino las variables a utilizar
	int puesto[6];
	int estaLibre;
	char nuevo_ID[8];
	char anterior_ID[8];

	CerrarBarrera();
	RefrescarLuces();

while (1){

	for(i=0;i<8;i++){
		anterior_ID[i]=nuevo_ID[i];
	}

	LeeTarjeta(nuevo_ID);
	if(strcmp(anterior_ID,nuevo_ID)!=0){

		if(strcmp(nuevo_ID, "47CAA7F4")==0){
			estaLibre=BuscarLugar();
			Iluminar(estaLibre);
			MostrarMensaje(DISCAP);
			AbrirBarrera();
			MostrarMensaje(STDBY);

		}


		}

	}


}

















}

void EINT3_IRQHandler (void)
{
	/* Toggleo el LED si hubo un flanco descendente en el GPIO P0.18 */
	if (Chip_GPIOINT_GetStatusFalling(LPC_GPIOINT, GPIOINT_PORT0) && (1 << 18)) {
		Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIOINT_PORT0, 1 << 18);
		pulse++;
		flag=1;}
}

void LeeTarjeta(char *id){

}
