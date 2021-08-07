/*
 * Module     :  
 *  
 * File Name  :  i2c.c
 *
 * Created on : 29 May 2021
 *
 * Author     : OMAR HESHAM 
 */

#include"i2c.h"

/*
 * Description  : initiate TWI with fast mode = 400 Kb/s
 * Steps        1. No Scaler TWPS = 0
 *              2. Bit Rate  TWBR = 2
 *              3. set MC it's own address = 0b0000010
 *              4. Enable IWT .
 */

void TWI_init(void)
{
	TWBR = 0x02 ;
    TWSR = 0x00 ;
	TWAR = 0b00000010 ; // address as a slave
	TWCR = (1<<TWEN) ;
}


/*
 * Description : function to Generate Start condition
 * steps : 1.CLear INT flag by writing one
 *         2.Generate Start condition
 *         3.Enable TWI
 *         4.wait for TWINT to be High
 */
void TWI_start(void)
{

	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(  ( TWCR & (1<<TWINT) ) == 0 ) ;

}

/*
 * Description : function to generate Stop condition
 * Steps: 1.CLear INT flag by writing one
 *        2.Generate Stop condition
 *        3.Enable TWI
 *        4. DO NOT wait for TWINT to be High
 */
void TWI_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	// while(  ( TWCR & (1<<TWINT) ) == 0 ) ; // WROOOOOOOOOOONG Don't check flag TWIF with STOP condition
}

/*
 * CLear INT flag by writing one
 * Enable TWI
 * writing SLA+W to TWDR.
 * wait for TWINT  flag to be set ( SLA+W sent successfully)
 *
 * NOTE for Updata: try to  separate  write function into 2 function
 *                    TWI_writeAddress(uint8 address, READ/WRITE ) ,READ/WRITE as macros
 *                    TWI_writeData(uint8 data)  ;
 */
void TWI_write(uint8 data)
{
	TWDR =  data ;  // 7bit slave address , W wite condition
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(  ( TWCR & (1<<TWINT) ) == 0 ) ;
}

/*
 * Description : To check the response of communication
 * Step   :  Masking to eliminate first 3 bits of TWSR and get the last 5 bits (status bits)
 * Return : TWSR
 */
uint8 TWI_getStatus(void)
{
	uint8 status ;
	status = (TWSR & 0xF8) ;
	return  status ;
}

/*
 * Description : At Master receiver mode,   To read 1 Byte of data from slave,followed by ACK
 * NOTE   :  this function used with ACK . if wanted to receiver more than 1 Byte .
 *
 * Steps : 1.Before Reading TWDR ,clear TWINT  = 1 .
 *         2.Enable ACK bit, Enable TW
 *         3.wait for TWINT flag to be set (data read / deleiverd successfully)
 *
 * Return : data register value . TWDR
 *
 */

uint8 TWI_readWithACK(void)
{
	 TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	 while(  ( TWCR & (1<<TWINT) ) == 0 ) ;
	 return TWDR;
}


/*
 * Description : At Master receiver mode  To read 1 Byte of data from slave ending by NACK
 * NOTE   :  this function used with NACK,as indication that Master will not receive any more
 *
 * Steps : 1.Before Reading TWDR ,clear TWINT  = 1 .
 *         2.Enable ACK bit, Enable TW
 *         3.wait for TWINT flag to be set (data read / deleiverd successfully)
 *
 * Return : data register value . TWDR
 *
 */

uint8 TWI_readWithNACK(void)
{
        TWCR = (1<<TWINT)|(1<<TWEN);
        while(  ( TWCR & (1<<TWINT) ) == 0 ) ;
        return TWDR;
}

