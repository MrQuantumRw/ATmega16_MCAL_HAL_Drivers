/*
 * usart.c
 *
 *  Created on: 6 May 2021
 *  Author: Omar Hesham
 */

#include "usart.h"

void UART_init(const Usart_ConfigType * Config_Ptr)
{
                	//UCSRA Description //

  //USART speed mode select for Asynchronous operation
	UCSRA |= (USART_SPEED << U2X); //shift the value of USART_SPEED to U2X Bit 1 ;

	                //UCSRB Description //

/* 7.RXCIE = 0 Disable USART RX Complete Interrupt Enable
*  6.TXCIE = 0 Disable USART TX Complete Interrupt Enable
*  5.UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
*  4.RXEN  = 1 Receiver Enable
*  3.TXEN  = 1 Transmitter Enable
*  2.UCSZ2 = Data mode inserted as required from the user
*  1:0.RXB8 & TXB8 not used for 8-bit data mode
*/

	UCSRB |=(1<<RXEN) |(1<<TXEN);
	if(Config_Ptr->SIZE == BIT_9)
	{
		UCSRB = (UCSRB & 0xF8) | (Config_Ptr->SIZE); //clear frist 3 bits then add value of SIZE
	}

        	     //UCSRC Description //
 /* 7.  URSEL   = 1 The URSEL must be one when writing the UCSRC
 *  6.  UMSEL   = Operation method inserted as required from the user
 *  5:4 UPM1:0  = Parity bit inserted as required from the user
 *  3.  USBS    = Stop bit inserted as required from the user
 *  2:1 UCSZ1:0 = Data Frame mode inserted as required from the user
 *  0   UCPOL   = Clock Polarity for Synchronous mode
 */

	UCSRC |= (1<<URSEL) ;
	UCSRC  = (UCSRC & 0xBF) | (USART_MODE<<UMSEL) ; // Clear UMSEL bit 6 then set value of USART_MODE
	UCSRC  = (UCSRC & 0xCF) | ((Config_Ptr->PARITY)<<4) ;
	UCSRC  = (UCSRC & 0xF7) | ((Config_Ptr->STOP_BIT)<< USBS) ;
	UCSRC  = (UCSRC & 0xF9) | ((Config_Ptr->SIZE)<<1) ;

	#if(MODE==Synchronous_Master)
		UCSRC |= (USART_POLARITY<<0);
	#endif
		/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
			UBRRH = BAUD_PRESCALER>>8;
			UBRRL = BAUD_PRESCALER;


}


//Call This function with Sender: Request to Send (RTS)
uint8 UART_RTS(void)
{
	UART_sendByte(10);//send RTC Request
	while(UART_recieveByte() != 11){}  //wait for CTS Response
	return 1 ;
}

// Call this function with Receiver : Clear To Send (CTS)
uint8 UART_CTS(void)
{
	while(UART_recieveByte() != 10){}  //wait for RTS
	UART_sendByte(11);//send CTS
    return 1 ;
}


void UART_sendByte(const uint8 data)
{

	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */

	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	UDR = data ;
}

uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this
		 * flag is set to one */
		while(BIT_IS_CLEAR(UCSRA,RXC)){}
		/* Read the received data from the Rx buffer (UDR) and the RXC flag
		   will be cleared after read this data */
	    return UDR;
}


void UART_sendString(const uint8 *Str)
{

  while(*Str != '\0')
  {
	  UART_sendByte(*Str);
	  Str++;
  }
}

void UART_receiveString(uint8 *Str) // Receive until #
{
  uint8 i = 0 ;
  Str[i] = UART_recieveByte();
  while(Str[i] != '#')  // read till special character ,because null character doesn't sent .
  {
	  i++;
	  Str[i] = UART_recieveByte();
  }
  Str[i] = '\0';  // Null Character doesn't sent by UART , see UART_sendByte() function.
}
