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
#include "uart.h"

// TODO: insert other include files here


// TODO: insert other definitions and declarations here

#define True 		1
#define False 		0
#define NOLUG		10
#define COMPL		8
#define STDBY		6
#define ALU			4 //Puestos 4 y 5 corresponden a ALU
#define DOC			2 //Puestos 2 y 3 corresponden a DOC
#define DISC		0 //Puestos 0 y 1 corresponden a DISC

int flag;
int pulse;
int puesto[6];
long tim;
char nuevo_ID[8]={0,0,0,0,0,0,0,0};

void delay(int);
void CerrarBarrera();
void AbrirBarrera();
void RefrescarSensores();
void RefrescarLuces();
void MostrarMensajeStdBy();
void MostrarMensaje(int);
int BuscarLugar(int);
void Iluminar(int);
void LeeTarjeta();



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
	/* Configuración de las entradas */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 18);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 15);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 16);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 23);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 24);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 25);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 26);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 2, 13);

	/* Configuración de la interrupción por flanco descendente */
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIOINT_PORT0, 1 << 18);

	/* Configuración de las GPIO como salidas
	 *P0[2],	*P0[3],	 	*P0[21],	*P0[22],	*P0[27],	*P0[28] 	LED VERDES
	 *P0[4],	*P0[5],		*P0[10], 	*P0[11], 	*P1[30], 	*P1[31]		LED ROJOS
	 */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 30);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 31);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 2);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 3);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 21);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 22);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 27);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 28);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 2, 13);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 4);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 5);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 11);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 10);

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

	int estaLibre=0;
	char anterior_ID[8];


	CerrarBarrera();
	RefrescarSensores();
	RefrescarLuces();
	MostrarMensajeStdBy();

while (1){

	for(int i=0;i<8;i++){
		anterior_ID[i]=nuevo_ID[i];
	}

	LeeTarjeta();
	if(strcmp(anterior_ID,nuevo_ID)!=0){

		if(strcmp(nuevo_ID, "47CAA7F4")==0){		//ID correspondiente a un discapacitado
			RefrescarSensores();
			estaLibre=BuscarLugar(DISC);
			if (estaLibre!=10){
				MostrarMensaje(estaLibre);
				AbrirBarrera();
				Iluminar(estaLibre);
				MostrarMensajeStdBy();
			}
		}
		if(strcmp(nuevo_ID, "47CAA7F4")==0){		//ID correspondiente a un docente
			RefrescarSensores();
			estaLibre=BuscarLugar(DOC);
			if (estaLibre!=10){
				MostrarMensaje(estaLibre);
				AbrirBarrera();
				Iluminar(estaLibre);
				MostrarMensajeStdBy();
			}
		}
		if(strcmp(nuevo_ID, "47CAA7F4")==0){		//ID correspondiente a un alumno
			RefrescarSensores();
			estaLibre=BuscarLugar(ALU);
			if (estaLibre!=10){
				MostrarMensaje(estaLibre);
				AbrirBarrera();
				Iluminar(estaLibre);
				MostrarMensajeStdBy();
			}
		}
		if(strcmp(nuevo_ID, "47CAA7F4")==0){		//ID correspondiente a un discapacitado
			RefrescarSensores();
			estaLibre=BuscarLugar(DISC);
			if (estaLibre!=10){
				MostrarMensaje(estaLibre);
				AbrirBarrera();
				Iluminar(estaLibre);
				MostrarMensajeStdBy();
			}
		}

	}

}


}

	/*	===================================================================	*
	 *	Definición de funciones												*
	 *	===================================================================	*/

void delay(int time){
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);//Hace que cada 1 ms interrumpa
	tim=time;
	while (tim){	}
}

void EINT3_IRQHandler (void)
{
	/* Toggleo el LED si hubo un flanco descendente en el GPIO P0.18 */
	if (Chip_GPIOINT_GetStatusFalling(LPC_GPIOINT, GPIOINT_PORT0) && (1 << 18)) {
		Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIOINT_PORT0, 1 << 18);
		pulse++;
		flag=1;}
}

void CerrarBarrera(){
	InitPWM();
}

void AbrirBarrera(){
	int sensorBarrera;
	SetPWM(20);
	sensorBarrera= Chip_GPIO_GetPinState(LPC_GPIO, 2, 13);
	while(sensorBarrera==1){
		delay(500);
		sensorBarrera= Chip_GPIO_GetPinState(LPC_GPIO, 2, 13);
	}
	while(sensorBarrera==0){
		delay(500);
		sensorBarrera= Chip_GPIO_GetPinState(LPC_GPIO, 2, 13);
	}

	delay(500);
	SetPWM(15);

}
void RefrescarSensores(){

	puesto[0]= Chip_GPIO_GetPinState(LPC_GPIO, 0, 15);
	puesto[1]= Chip_GPIO_GetPinState(LPC_GPIO, 0, 16);
	puesto[2]= Chip_GPIO_GetPinState(LPC_GPIO, 0, 23);
	puesto[3]= Chip_GPIO_GetPinState(LPC_GPIO, 0, 24);
	puesto[4]= Chip_GPIO_GetPinState(LPC_GPIO, 0, 25);
	puesto[5]= Chip_GPIO_GetPinState(LPC_GPIO, 0, 26);
}

void RefrescarLuces(){

	if (puesto[0]){
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 0, 2); //Enciende LED verde
	} else {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 0, 4); //Enciende LED rojo
	}

	if (puesto[1]){
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 0, 3);
	} else {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 0, 5);
	}

	if (puesto[2]){
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 0, 21);
	} else {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 0, 10);
	}

	if (puesto[3]){
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 0, 22);
	} else {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 0, 11);
	}

	if (puesto[4]){
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 0, 27);
	} else {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 1, 30);
	}

	if (puesto[5]){
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 0, 28);
	} else {
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, 1, 31);
	}
}

void MostrarMensajeStdBy(){

	int libres=0;
	for (int i=0;i<6;i++){
		if (puesto[i]){
			libres++;
		}
	}
	LCD_SendInstruction(LCD_DISPLAY_CLEAR);
	LCD_GoToxy(0,0);
	LCD_Print(" HAY LUGARES:");
	LCD_GoToxy(0, 15);
	LCD_SendChar((char)libres);
}

void MostrarMensaje(int lugar){

	if (lugar<=5) {
		LCD_SendInstruction(LCD_DISPLAY_CLEAR);
		LCD_GoToxy(0,0);
		LCD_Print("BIENVENIDO");
		LCD_GoToxy(1, 0);
		LCD_Print("PASE AL LUGAR:");
		LCD_GoToxy(1, 15);
		LCD_SendChar((char)lugar);
	}
}

int BuscarLugar(int condicion){

	int lugar=10, i;			//A lugar le doy el valor 10 pero podría haberle dado cualquier valor distinto de 0...5
	switch(condicion){
	case DISC:
		i=0;
		break;
	case DOC:
		i=2;
		break;
	case ALU:
		i=4;
		break;
	}
	while(lugar==10||i<6){		//i<6 para que de una vuelta por el vector y salga. lugar=10 para que cuando encuentre el primer valor salga.
		if(puesto[i]){
			lugar=i;
		} else {
			i++;
		}
	}
	return lugar;
}

void Iluminar(int lugar){
	switch(lugar){
	case 0:
		while(puesto[0]==0){
			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 2);
			delay(500);
			RefrescarSensores();
		}
		break;
	case 1:
		while(puesto[1]==0){
			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 3);
			delay(500);
			RefrescarSensores();
		}
		break;
	case 2:
		while(puesto[2]==0){
			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 21);
			delay(500);
			RefrescarSensores();
		}
		break;
	case 3:
		while(puesto[3]==0){
			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 22);
			delay(500);
			RefrescarSensores();
		}
		break;
	case 4:
		while(puesto[4]==0){
			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 27);
			delay(500);
			RefrescarSensores();
		}
		break;
	case 5:
		while(puesto[5]==0){
			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 28);
			delay(500);
			RefrescarSensores();
		}
		break;
	}
}
void LeeTarjeta( ){

	int i;
	uart_init(9600);
	for(i=0;i<9;i++)
		nuevo_ID[i]=uart_RxChar();
	delay(10);
}

void SysTick_Handler(void){
	if(tim) tim--;
}
