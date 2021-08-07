/*
 * Module     :  
 *  
 * File Name  :  external_eeprom.c
 *
 * Created on : 4 Jun 2021
 *
 * Author     : OMAR HESHAM 
 */

#include"external_eeprom.h"
#include"i2c.h"

void EEPROM_init(void)
{
	// Initialise TWI
   	TWI_init();
}


   /******************************************************************************
    *****************     write Byte sequence  **********************************
      1. send Start
      2. read status (Start_ACK)
	  3. send frist 8bits EEPROM address with R/W= 0 (write)
      4. read status  (slave_ write_ACK)
	  5. write send 8 bits EEPROM address
      6. read status  (Data_Wirt_ACK)
      7. send 1 Byte data to EEPROM
      8. read status (Data_Wirt_ACK)
      9. send STOP

   */

uint8 EEPROM_writeByte(uint16 address,uint8 data)
{
	// generate start condition
	TWI_start();

	//Check Start ACK
	if(TWI_getStatus()!=TW_START)
	{
		return ERROR ;
	}

	// 3. send firs)t 8bits EEPROM address with R/W= 0 (write)
	TWI_write((uint8) ( 0xA0 | ((address & 0x0700) >>7)) );

	// 4. read status  (slave_ write_ACK)
	if(TWI_getStatus() != TW_MT_SLA_W_ACK)
	{
		return ERROR ;
	}

	// 5. write send 8 bits EEPROM address
	TWI_write((uint8) address);

	// 6. read status  (Data_Wirt_ACK)
	if(TWI_getStatus()!=TW_MT_DATA_ACK)
	{
		return ERROR;
	}

	//7. send 1 Byte data to EEPROM
	TWI_write(data);

	// 8. read status  (Data_Wirt_ACK)
	if(TWI_getStatus()!=TW_MT_DATA_ACK)
	{
		return ERROR;
	}

	//9. send STOP
	TWI_stop();
		  _delay_ms(10);// According to DataSheet 4ms wait to write on EEPROM


	return SUCCESS ;

}

/**********************************************************
 ****************   Read Byte sequence  **********************************
      1. send Start
      2. read status (Start_ACK)
	  3. send EEPROM address with R/W= 0 (write)
      4. read status  (slave_ write_ACK)
	  5. send Memory Location to read from
      6. read status  (Data_Wirt_ACK)
      7. repeat start
      8. read status
      9. send EEPROM (SLAVE) address with R/W=1 (read)
      10.read status (SLAVE_read ACK)
      11.call TWI_readWithNACK() function to read from EEPROM
      12.read status (Master read with NACK )
      13.send STOP

 */
/*
 * Description : function to read a Byte from External EEPROM
 *
 * Arguments   : 1. 16bit address of EEPROM
 *               2. pointer to uint8 variable to store read value from EEPROM
 */
uint8 EEPROM_readByte(uint16 address,uint8 *data)
{
	// generate start condition
	TWI_start();

	//Check Start ACK
	if(TWI_getStatus()!=TW_START)
	{
		return ERROR ;
	}

	// 3. send firs)t 8bits EEPROM address with R/W= 0 (write)
    TWI_write((uint8) ( 0xA0 | ((address & 0x0700) >>7)) );

	// 4. read status  (slave_ write_ACK)
	if(TWI_getStatus() != TW_MT_SLA_W_ACK)
	{
		return ERROR ;
	}
	// 5. write send 8 bits EEPROM address
		TWI_write((uint8) address);

	// 6. read status  (Data_Wirt_ACK)
	if(TWI_getStatus()!=TW_MT_DATA_ACK)
	{
			return ERROR;
	}

	//  7. repeat start
	TWI_start();

	// 8. read status (repeat start ACK)
	if(TWI_getStatus() != TW_REP_START)
	{
		return ERROR;
	}

	// 9. send EEPROM (SLAVE) address with R/W=1 (read)
	TWI_write((uint8) (((0xA0) | ((address & 0x0700)>>7))|1));

	//10.read status (SLAVE_read ACK)
	if(TWI_getStatus() != TW_MT_SLA_R_ACK)
	{
		return ERROR;
	}

	 //11.call TWI_readWithNACK() function to read from EEPROM
	*data = TWI_readWithNACK() ;

	//   12.read status (Master read with NACK )
	if(TWI_getStatus() != TW_MR_DATA_NACK)
	{
		return ERROR ;
	}
	// 13.send STOP
	TWI_stop();

    return SUCCESS ;
}

