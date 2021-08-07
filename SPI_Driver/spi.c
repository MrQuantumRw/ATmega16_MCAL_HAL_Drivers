/*
 * Module :
 *
 * File Name : spi.c
 *
 * Description : Source file for the SPI AVR driver
 *
 * Created on: 11 May 2021
 *      
 * Author:  Omar Hesham
 */


#include "spi.h"
void SPI_initMaster(void)
{
/******** Configure SPI Master Pins *********
		 *  SS(PB4)   --> Output
		 * MOSI(PB5) --> Output
		 * MISO(PB6) --> Input
		 * SCK(PB7) --> Output
		 ********************************************/
		DDRB |= (1<<PB4);
		DDRB |= (1<<PB5);
		DDRB &= (~(1<<PB6));
		DDRB |= (1<<PB7) ;
		   /******************** SPCR Description *****************
	 * Bit7: SPIE = 0 				 : Disable SPI interrupt
	 * Bit6: SPE  = 1 				 : Enable SPI Module
	 * Bit5: DORD = Configured 		 : select data order (LSB=1,MSB=0)
	 * Bit4: MSTR = Configured 		 : select Master =1 or Slave=0
	 * Bit3: CPOL = Configured 		 : select Polarity [0 :IDLE is LOW] [1 : IDLE High]
	 * Bit2: CPHA = Configured 		 : select sampling (capture) edge [0:Rising ,1: Falling]
	 * Bit1,0: SPR1,SPR0 :Configured : select Clock rate
	 ********************************************************/
	 SPCR = (1<<SPE)|(1<<MSTR);
}

void SPI_initSlave(void)
{
		/******** Configure SPI Slave Pins *********
		 * SS(PB4)   --> Input
		 * MOSI(PB5) --> Input
		 * MISO(PB6) --> Output
		 * SCK(PB7) --> Input
		 ********************************************/
		DDRB &= (~(1<<PB4));
		DDRB &= (~(1<<PB5));
		DDRB |= (1<<PB6);
		DDRB &= (~(1<<PB7));
		   /******************** SPCR Description *****************
	 * Bit7: SPIE = 0 				 : Disable SPI interrupt
	 * Bit6: SPE  = 1 				 : Enable SPI Module
	 * Bit5: DORD = Configured 		 : select data order (LSB=1,MSB=0)
	 * Bit4: MSTR = Configured 		 : select Master =1 or Slave=0
	 * Bit3: CPOL = Configured 		 : select Polarity [0 :IDLE is LOW] [1 : IDLE High]
	 * Bit2: CPHA = Configured 		 : select sampling (capture) edge [0:Rising ,1: Falling]
	 * Bit1,0: SPR1,SPR0 :Configured : select Clock rate
	 ********************************************************/
	 SPCR = (1<<SPE);

}

void SPI_configMaster(const SPI_ConfigType *a_ConfigPtr)
{
	/******** Configure SPI  Pins *********/


		/******** Configure SPI Master Pins *********
		 *  SS(PB4)   --> Output
		 * MOSI(PB5) --> Output
		 * MISO(PB6) --> Input
		 * SCK(PB7) --> Output
		 ********************************************/
		DDRB |= (1<<PB4);
		DDRB |= (1<<PB5);
		DDRB &= (~(1<<PB6));
		DDRB |= (1<<PB7) ;
	       // PORTB &= (~(1<<PB4)) ;
	   /******************** SPCR Description *****************
	 * Bit7: SPIE = 0 				 : Disable SPI interrupt
	 * Bit6: SPE  = 1 				 : Enable SPI Module
	 * Bit5: DORD = Configured 		 : select data order (LSB,MSB)
	 * Bit4: MSTR = Configured 		 : select Master or Slave
	 * Bit3: CPOL = Configured 		 : select Polarity [0 :IDLE is LOW] [1 : IDLE High]
	 * Bit2: CPHA = Configured 		 : select sampling (capture) edge [0:Rising ,1: Falling]
	 * Bit1,0: SPR1,SPR0 :Configured : select Clock rate
	 ********************************************************/
	SPCR =(1<<SPE)|((a_ConfigPtr->Order)<<DORD)|((a_ConfigPtr->StatusConfig)<<MSTR)|((a_ConfigPtr->PolarityConfig)<<CPOL)| ((a_ConfigPtr->Phase_Config)<<CPHA)| ((a_ConfigPtr->Clock_Config)<<0);


	/******************** SPSR Description *****************
	 * Bit0 : SPI2X : set 1 if Double speed is needed
	 ******************************************************/

	#if(SPI_SPEED==DOUBLE)
		SPSR |=(1<<SPI2X) ;
	#endif

}
void SPI_configSlave(const SPI_ConfigType *a_ConfigPtr)
{
		/******** Configure SPI Slave Pins *********
		 * SS(PB4)   --> Input
		 * MOSI(PB5) --> Input
		 * MISO(PB6) --> Output
		 * SCK(PB7) --> Input
		 ********************************************/
		DDRB &= (~(1<<PB4));
		DDRB &= (~(1<<PB5));
		DDRB |= (1<<PB6);
		DDRB &= (~(1<<PB7));
	   /******************** SPCR Description *****************
	 * Bit7: SPIE = 0 				 : Disable SPI interrupt
	 * Bit6: SPE  = 1 				 : Enable SPI Module
	 * Bit5: DORD = Configured 		 : select data order (LSB,MSB)
	 * Bit4: MSTR = Configured 		 : select Master or Slave
	 * Bit3: CPOL = Configured 		 : select Polarity [0 :IDLE is LOW] [1 : IDLE High]
	 * Bit2: CPHA = Configured 		 : select sampling (capture) edge [0:Rising ,1: Falling]
	 * Bit1,0: SPR1,SPR0 :Configured : select Clock rate
	 ********************************************************/
	SPCR = (SPCR & 0xBF) |(1<<SPE); // Enable SPI
	SPCR = (SPCR & 0xDF) |((a_ConfigPtr->Order)<<DORD);
	SPCR = (SPCR & 0xEF) |((a_ConfigPtr->StatusConfig)<<MSTR);
	SPCR = (SPCR & 0xF7) |((a_ConfigPtr->PolarityConfig)<<CPOL);
	SPCR = (SPCR & 0xFB) | ((a_ConfigPtr->Phase_Config)<<CPHA);
	SPCR = (SPCR & 0xFC) | ((a_ConfigPtr->Clock_Config)<<0);




	/******************** SPSR Description *****************
	 * Bit0 : SPI2X : set 1 if Double speed is needed
	 ******************************************************/

	#if(SPI_SPEED==DOUBLE)
		SPSR |=(1<<SPI2X) ;
	#endif
}


void SPI_init(const SPI_ConfigType *a_ConfigPtr)
{
	/******** Configure SPI  Pins *********/
	if(a_ConfigPtr->StatusConfig == MASTER)
	{
		/******** Configure SPI Master Pins *********
		 *  SS(PB4)   --> Output
		 * MOSI(PB5) --> Output
		 * MISO(PB6) --> Input
		 * SCK(PB7) --> Output
		 ********************************************/
		DDRB |= (1<<PB4);
		DDRB |= (1<<PB5);
		DDRB &= (~(1<<PB6));
		DDRB |= (1<<PB7) ;
	       // PORTB &= (~(1<<PB4)) ;
	   /******************** SPCR Description *****************
	 * Bit7: SPIE = 0 				 : Disable SPI interrupt
	 * Bit6: SPE  = 1 				 : Enable SPI Module
	 * Bit5: DORD = Configured 		 : select data order (LSB,MSB)
	 * Bit4: MSTR = Configured 		 : select Master or Slave
	 * Bit3: CPOL = Configured 		 : select Polarity [0 :IDLE is LOW] [1 : IDLE High]
	 * Bit2: CPHA = Configured 		 : select sampling (capture) edge [0:Rising ,1: Falling]
	 * Bit1,0: SPR1,SPR0 :Configured : select Clock rate
	 ********************************************************/
     SPCR =(1<<SPE)|((a_ConfigPtr->Order)<<DORD)|((a_ConfigPtr->StatusConfig)<<MSTR)|((a_ConfigPtr->PolarityConfig)<<CPOL)| ((a_ConfigPtr->Phase_Config)<<CPHA)| ((a_ConfigPtr->Clock_Config)<<0);


	}
	else if(a_ConfigPtr->StatusConfig == SLAVE)
	{


		DDRB &= (~(1<<PB4));
		DDRB &= (~(1<<PB5));
		DDRB |= (1<<PB6);
		DDRB &= (~(1<<PB7));
	   /******************** SPCR Description *****************
	 * Bit7: SPIE = 0 				 : Disable SPI interrupt
	 * Bit6: SPE  = 1 				 : Enable SPI Module
	 * Bit5: DORD = Configured 		 : select data order (LSB,MSB)
	 * Bit4: MSTR = Configured 		 : select Master or Slave
	 * Bit3: CPOL = Configured 		 : select Polarity [0 :IDLE is LOW] [1 : IDLE High]
	 * Bit2: CPHA = Configured 		 : select sampling (capture) edge [0:Rising ,1: Falling]
	 * Bit1,0: SPR1,SPR0 :Configured : select Clock rate
	 ********************************************************/
	SPCR =(1<<SPE)|((a_ConfigPtr->Order)<<DORD)|((a_ConfigPtr->StatusConfig)<<MSTR)|((a_ConfigPtr->PolarityConfig)<<CPOL)| ((a_ConfigPtr->Phase_Config)<<CPHA)| ((a_ConfigPtr->Clock_Config)<<0);

	}



	/******************** SPSR Description *****************
	 * Bit0 : SPI2X : set 1 if Double speed is needed
	 ******************************************************/

	#if(SPI_SPEED==DOUBLE)
		SPSR |=(1<<SPI2X) ;
	#endif

}
void SPI_sendByte(const uint8 data)
{

	SPDR = data ;  //send data by SPI
	//PORTA &= ~(1<<PA3);
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is sent correctly)
}

void SPI_sendString(const uint8 *Str)
{
	uint8 i = 0 ;

	while(Str[i]!='\0')
	{
		SPI_sendByte(Str[i]);
		i++;

	}
}
uint8 SPI_receiveByte(void)
{
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1(data is receive correctly)
	return SPDR ; //return the received byte from SPI data register
}
void SPI_receiveString(uint8 *Str)
{
	uint8 i = 0 ;
	Str[i] = SPI_receiveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = SPI_receiveByte();
	}
	Str[i] = '\0';
}
