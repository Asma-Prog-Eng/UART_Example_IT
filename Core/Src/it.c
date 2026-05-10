/*
 * it.c
 *
 *  Created on: May 3, 2026
 *      Author: asmae
 */

#include "stm32f1xx_hal.h"

// override the default handler, = the infinite loop
// When the SysTick interrupt is triggered, control is transferred to this handler,
//and the system gets stuck in this loop. Consequently, other operations,
// like printing messages, cannot proceed beyond a certain point.

extern UART_HandleTypeDef huart2;

void SysTick_Handler(void) {

	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

// usart tranceiving data is enabled in interrupt mode
// so relevant interrupt handler is called

void USART2_IRQHandler(void) {


	HAL_UART_IRQHandler(&huart2);


}
