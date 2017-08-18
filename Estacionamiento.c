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


// TODO: insert other include files here


// TODO: insert other definitions and declarations here
#define PCPWM1 (1 << 6)
#define PCLK_PWM1_BY8 ((1 << 13)|(1 << 12))
#define PCLK_PWM1_BY4 ~(PCLK_PWM1_BY8)
#define PCLK_PWM1 ((0 << 13)|(1 << 12))
#define PCLK_PWM1_BY2 ((1 << 13)|(0 << 12))
#define LER0_EN		1 << 0
#define LER1_EN		1 << 1
#define LER2_EN		1 << 2
#define LER3_EN		1 << 3
#define LER4_EN		1 << 4
#define LER5_EN		1 << 5
#define LER6_EN		1 << 6
#define PWMENA1		1 << 9
#define PWMENA2		1 << 10
#define PWMENA3		1 << 11
#define PWMENA4		1 << 12
#define PWMENA5		1 << 13
#define PWMENA6		1 << 14
#define TCR_CNT_EN	0x00000001
#define TCR_RESET	0x00000002
#define TCR_PWM_EN	0x00000008
#define INITPWMVAL	0
#define	ENDPWMVAL	200
#define True 		1
#define False 		0

#define msgDOC		""




int flag;
int pulse;

void InitPWM();
void SetPWM(int);
void LeeTarjeta(char*);

int main(void) {

//Como primera medida configuramos los pines que vamos a utilizar para nuestra aplicación
	//Los pines utilizados para el display se configuran a través de la librería libLCD
	/* D4 p2.5 (J6-47)
	 * D5 p2.6 (J6-48)
	 * D6 p2.7 (J6-49)
	 * D7 p2.8 (J6-50)
	 * RS p2.0 (J6-42)
	 * EN p2.1 (J6-43)	 		*/
	// Inicializamos el display y actualizamos el valor del clock
	LCD_Init();
	LCD_Tim1DeInit();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	LCD_Tim1Init();
	LCD_SendInstruction(LCD_DISPLAY_CLEAR);
	// Inicializamos la placa
	Board_Init();
	/* Configuración del GPIO P0.18 como entrada */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, GPIOINT_PORT0, 18);
	/* Configuración de la interrupción por flanco descendente */
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIOINT_PORT0, 1 << 18);
	/* Habilitación de las interrupciones de los GPIO en el NVIC */
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);

	// Defino las variables a utilizar
	int puesto[6];
	int estaLibre;
	char nuevo_ID[8];
	char anterior_ID[8];


























while (1){

	for(i=0;i<8;i++){
		anterior_ID[i]=nuevo_ID[i];
	}

	LeeTarjeta(&nuevo_ID);
	if(strcmp(anterior_ID,nuevo_ID)!=0){

		if(strcmp(nuevo_ID, "47CAA7F4")==0){

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

void InitPWM()
	{
	//enable PWM1 Power
	LPC_SC ->PCON |= PCPWM1;
	//PWM peripheral clk = PCLK
	LPC_SC ->PCLKSEL0 &= (PCLK_PWM1_BY4);
	//Pin select
	//Pone el P2.2 a funcionar como PWM1.3
	LPC_PINCON->PINSEL4 |= (0x1<<4);
	LPC_PINCON->PINSEL4 &= ~(0x1<<5);
	// count frequency:Fpclk
	// Un contador se va incrementando a velocidad PCLK (SystemCoreClock/PCLKdiv) y se resetea provocando un incremento en TC en el valor PR+1, voy a usar una f de 10 kHz...
	SystemCoreClockUpdate();
	LPC_PWM1->PR = (SystemCoreClock/(4*10000)) - 1 ;
	// Match Control Register controla qué acción se produce cuando se matchea con cada match. En este caso reset en MR0
	LPC_PWM1->MCR = 1 << 1;
	// set PWM cycle - uso 200 porque a 10kHz, 200 ciclos tardan 20ms
	LPC_PWM1->MR0 = ENDPWMVAL;
	//Debe cambiar a 1,5ms entonces...
	LPC_PWM1->MR3 = 15;
	//Load Shadow register content
	//Latch Enable Register, si los valores de los MR cambian durante la ejecución, no se actualizan si no están habilitados en el LER
	LPC_PWM1->LER = LER3_EN;
	//Enable PWM outputs
	LPC_PWM1->PCR = PWMENA3;
	//Enable PWM Timer
	LPC_PWM1->TCR = TCR_CNT_EN | TCR_PWM_EN;
}

void SetPWM(int PWMval)
//@brief Cambia la posición del Match 3 por el valor que reciba cuando se la llame.
{
			LPC_PWM1->MR3 = PWMval;
			LPC_PWM1->LER = LER3_EN;
		}

void LeeTarjeta(char *id){}
