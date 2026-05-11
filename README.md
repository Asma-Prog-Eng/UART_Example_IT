# UART_Example_IT
Bare metal implementation of a UART receiver in interrupt mode for STM32 development board
## Features
UART2 initialization with baud rate = 115200 bps
Default pins are used : PA2= tx, PA3= rx
## Requirements
Hardware <br />
Nucleo STM32 development board (STM32F103x series) <br />
Software <br />
STM32CubeIDE or compatible toolchain <br />
Tera Term 
## Installation
Clone this repository:

git clone https://github.com/Asma-Prog-Eng/UART_Example_IT  <br />
Import project into STM32CubeIDE: <br /> File → Import... → Existing Projects into Workspace  <br />
Rebuild project dependenciesFile
## Usage
Initialization : UART2_init (), HAL_init()  <br />
Send data to the serial terminal : HAL_UART_Transmit()  <br />
Receive the user entered data : HAL_UART_Receive_IT()

## Project Structure
├── Core <br />
├── Inc <br />
→ it.h <br />
→ main_app.h <br />
→ msp.h <br />
→ stm32321f1xx.hal.h <br />
├── Src <br />
→ it.c <br />
→ main_app.c <br />
→ msp.c. <br />
→ syscall.c <br />
→ sysmem.c <br />
→ system_stm32f1xx.c <br />

## Troubleshooting
No data received: <br />
Verify baud rate settings in the serial terminal <br />

## Known Limitations
Limited to 8-bit data words 

## Contributing
Pull requests are welcome. For major changes, open an issue first.

License
MIT License
Copyright (c) [2026] [Asma Askri]
