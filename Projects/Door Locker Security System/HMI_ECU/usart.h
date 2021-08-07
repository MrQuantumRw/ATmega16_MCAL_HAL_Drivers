/*
 * usart.h
 *
 *  Created on: 4 May 2021
 *      Author: Omar Hesham
 */

#ifndef USART_H_
#define USART_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define BAUDRATE 9600
#define MODE Asynchronous_Double_Speed
#define RTS 1
#define CTS 0

#define Asynchronous_Normal_Speed 0
#define Asynchronous_Double_Speed 1
#define Synchronous_Master 2

#if(MODE==0)
 #define USART_MODE 0
 #define USART_Speed 0
 #define BAUD_PRESCALER ((F_CPU/(16UL*(BAUDRATE)))-1)
#elif(MODE==1)
 #define USART_MODE 0
 #define USART_SPEED 1
 #define BAUD_PRESCALER ((F_CPU/(8UL*(BAUDRATE)))-1)
#elif(MODE==2)
 #define USART_MODE 1
 #define USART_POLARITY 0
 #define BAUD_PRESCALER ((F_CPU/(2UL*(BAUDRATE)))-1)
#endif

/*******************************************************************************
 *                      Types Declaration                                       *
 *******************************************************************************/

typedef enum
{
	BIT_5,BIT_6,BIT_7,BIT_8,BIT_9=7
}Frame_Size;

typedef enum
{
	DISABLE,EVEN=2,ODD=3
}Parity_Type;

typedef	enum
{
	BIT_1,BIT_2
}Stop_Bit_Num;


typedef struct

{
	Frame_Size SIZE;
	Stop_Bit_Num STOP_BIT;
	Parity_Type PARITY;
}Usart_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void UART_init(const Usart_ConfigType * Config_Ptr) ;

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str); // Receive until #

uint8 UART_RTS(void) ;

uint8 UART_CTS(void);

#endif /* USART_H_ */

