/*
 * pwm.h
 *
 *  Created on: 18 ago. 2017
 *      Author: INTI
 */

#ifndef PWM_H_
#define PWM_H_

/*===================================*/
/* Definitions */
/*===================================*/

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

/*===================================*/
/* Function declarations */
/*===================================*/

void InitPWM();
void SetPWM(int);

/*=======================================================================================*/

#endif /* PWM_H_ */
