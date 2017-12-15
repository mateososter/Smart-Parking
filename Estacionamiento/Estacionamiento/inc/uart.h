/*
 * uart.h
 *
 *  Created on: 31 ago. 2017
 *      Author: INTI
 */

#ifndef UART_H_
#define UART_H_

#include <lpc17xx.h>
#include "stdutils.h"

#define SBIT_WordLenght    0x00u
#define SBIT_DLAB          0x07u
#define SBIT_FIFO          0x00u
#define SBIT_RxFIFO        0x01u
#define SBIT_TxFIFO        0x02u

#define SBIT_RDR           0x00u
#define SBIT_THRE          0x05u

void uart_init(uint32_t);
void uart_TxChar(char);
char uart_RxChar();


#endif /* UART_H_ */
