/*
 * uart.c
 *
 *  Created on: 31 ago. 2017
 *      Author: INTI
 */

#include "uart.h"

/* Function to initialize the UART0 at specifief baud rate */
void uart_init(uint32_t baudrate)
{
    uint32_t var_UartPclk_u32,var_Pclk_u32,var_RegValue_u32;

    LPC_SC->PCONP &= ~0x00000004; // Apaga uart0
    LPC_SC->PCONP |= 0x02000000;	//prende uart3
    LPC_PINCON->PINSEL0 &= ~0x00000005;
    LPC_PINCON->PINSEL0 |= 0x0000000A;            // Enable TxD0 P0.2 and p0.3

    LPC_UART3->FCR = (1<<SBIT_FIFO) | (1<<SBIT_RxFIFO) | (1<<SBIT_TxFIFO); // Enable FIFO and reset Rx/Tx FIFO buffers
    LPC_UART3->LCR = (0x03<<SBIT_WordLenght) | (1<<SBIT_DLAB);             // 8bit data, 1Stop bit, No parity


    /** Baud Rate Calculation :
       PCLKSELx registers contains the PCLK info for all the clock dependent peripherals.
       Bit6,Bit7 contains the Uart Clock(ie.UART_PCLK) information.
       The UART_PCLK and the actual Peripheral Clock(PCLK) is calculated as below.
       (Refer data sheet for more info)

       UART_PCLK    PCLK
         0x00       SystemFreq/4
         0x01       SystemFreq
         0x02       SystemFreq/2
         0x03       SystemFreq/8
     **/

    var_UartPclk_u32 = (LPC_SC->PCLKSEL1 >> 18) & 0x03;

    switch( var_UartPclk_u32 )
    {
    case 0x00:
        var_Pclk_u32 = SystemCoreClock/4;
        break;
    case 0x01:
        var_Pclk_u32 = SystemCoreClock;
        break;
    case 0x02:
        var_Pclk_u32 = SystemCoreClock/2;
        break;
    case 0x03:
        var_Pclk_u32 = SystemCoreClock/8;
        break;
    }


    var_RegValue_u32 = ( var_Pclk_u32 / (16 * baudrate ));
    LPC_UART3->DLL =  var_RegValue_u32 & 0xFF;
    LPC_UART3->DLM = (var_RegValue_u32 >> 0x08) & 0xFF;

    util_BitClear(LPC_UART3->LCR,(SBIT_DLAB));  // Clear DLAB after setting DLL,DLM
}


/* Function to transmit a char */
void uart_TxChar(char ch)
{
    while(util_IsBitCleared(LPC_UART3->LSR,SBIT_THRE)); // Wait for Previous transmission
    LPC_UART3->THR=ch;                                  // Load the data to be transmitted
}


/* Function to Receive a char */
char uart_RxChar()
{
    char ch;
    while(util_IsBitCleared(LPC_UART3->LSR,SBIT_RDR));  // Wait till the data is received
    ch = LPC_UART3->RBR;                                // Read received data
    return ch;
}

