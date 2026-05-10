/*
 * main_app.c
 *  UART driver in interrupt mode
 *  Transmit a user message through usart 2 (PA2 = tx, PA3 = rx)
 *  Baud rate = 115200
 *  Board  : Nucleo 64, STM32F103Rb
 *  Serial Terminal : Tera Term
 *  Created on: May 3, 2026
 *      Author: asmae
 */

void SystemClockConfig(void);

void UART2_Init(void);
void Error_handler(void);

#include "stm32f1xx_hal.h"
#include "msp.h"
#include "it.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0


UART_HandleTypeDef huart2;

uint8_t received_data;

uint8_t data_buffer[100];

uint16_t received_data_completed;

uint16_t count ;

int main(void){

	char *user_data = "\n\n**********The application is running***********\r\n\n";


	HAL_Init();
	UART2_Init();


	// transmit startup message

	HAL_UART_Transmit(&huart2, (uint8_t*) user_data, (uint16_t) strlen(user_data), HAL_MAX_DELAY ) ;


	while(1){

	// initialize data reception completion flag

    received_data_completed = FALSE;

    // clearing data buffer
    for(int i=0 ; i < count ; i++) {
    	data_buffer[i] = 0;
    }

    // the user entered char. is received in interrupt mode

	while ( received_data_completed != TRUE) {

		HAL_UART_Receive_IT(&huart2, &received_data ,1);

	}

	}


    return 0 ;

}



void UART2_Init(void)
{
	// high level usart 2 inits. callback

	 huart2.Instance =  USART2;
	 huart2.Init.BaudRate = 115200;
	 huart2.Init.WordLength = UART_WORDLENGTH_8B ;
	 huart2.Init.StopBits = UART_STOPBITS_1;
	 huart2.Init.Parity = UART_PARITY_NONE ;
	 huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	 huart2.Init.Mode = UART_MODE_TX_RX  ;
	 HAL_UART_Init(&huart2);
	 if( HAL_UART_Init(&huart2)!= HAL_OK){

		 // there is a problem
		 Error_handler();

	 }

	 // low level usart 2 inits. callback
	 HAL_UART_MspInit(&huart2);
}


void Error_handler(void){

	// Infinite loop if error occurs, blinking a led can be used too here instead

	while(1);
}

// uart interrupt processing

// if user type "enter" key the complete message stored in data_buffer is transmitted to
// the serial terminal
// else entered char. is stored in the data buffer

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	if (received_data == '\r') {

		data_buffer[count++] = '\r';
		HAL_UART_Transmit(&huart2, data_buffer, count, HAL_MAX_DELAY );
		received_data_completed = TRUE;

	}

	else {

		data_buffer[count++] = received_data;

	}


}
