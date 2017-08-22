/*
 * pwm.c
 *
 *  Created on: 18 ago. 2017
 *      Author: INTI
 */

#include "pwm.h"
#include "LPC17xx.h"

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
