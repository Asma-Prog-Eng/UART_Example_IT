/*
 * msp.c
 *
 *  Created on: May 3, 2026
 *      Author: asmae
 */


/**
  * @brief  Initialize the MSP.
  * @retval None
  */

#include "stm32f1xx.h"
#include "msp.h"


 // low level processor specific inits

void HAL_MspInit(void)
{
	// 1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// 2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 0x7 << 16; //usg fault, memory fault and bus fault system exceptions

	// 3. Configure the priority for the system exceptions
	 HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	 HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	 HAL_NVIC_SetPriority(UsageFault_IRQn, 0,0);

}

// low level inits. of the USART2 peripheral

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {

	 GPIO_InitTypeDef gpio_uart;

	// 1. Enable the clock for the USART2 peripheral

	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// 2. Do the pin muxing configuration
	//AFIO_REMAP_DISABLE(AFIO_MAPR_USART2_REMAP);
	// UART_TX
	gpio_uart.Pin = GPIO_PIN_2 ;
	gpio_uart.Mode = GPIO_MODE_AF_PP ;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	AFIO_REMAP_DISABLE(AFIO_MAPR_USART2_REMAP);
	HAL_GPIO_Init(GPIOA,&gpio_uart);
	// UART_RX
	gpio_uart.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA,&gpio_uart);
	// @brief Disable the remapping of USART2 alternate function CTS, RTS, CK, TX and RX.
	// @note  DISABLE: No remap (CTS/PA0, RTS/PA1, TX/PA2, RX/PA3, CK/PA4)
	//AFIO_REMAP_DISABLE(AFIO_MAPR_USART2_REMAP);


	// 3. Enable the IRQ and set up the priority (NVIC settings)

	  NVIC_EnableIRQ(USART2_IRQn);
	  HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}
