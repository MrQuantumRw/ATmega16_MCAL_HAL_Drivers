/*
 * Module     :  
 *  
 * File Name  :  i2c.h
 *
 * Created on : 29 May 2021
 *
 * Author     : OMAR HESHAM 
 */

#include"common_macros.h"
#include"micro_config.h"
#include"std_types.h"


#ifndef I2C_H_
#define I2C_H_

/************************************************************************************************
 *                              I2C Status Macros                                               *
 ************************************************************************************************/
 /* I2C Status Bits in the TWSR Register */

#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request )                                  to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request )                                    to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received                                      from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave


/************************************************************************************************
 *                            Functions Prototypes                                              *
 ************************************************************************************************/
/* Module Required function
 * 1. Init function   : init clock speed
 * 2. start function  : To generate start condition
 * 3. Write function  : To write  1 Byte data on data register TWDR
 * 4. status function : To check the response of communication
 * 5. stop function   : To generate Stop condition
 * 6. read function   : Read data from slave , create 2 functions with ACK & with NACK
 *
 */

void TWI_init(void);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_getStatus(void);
uint8 TWI_readWithACK(void);
uint8 TWI_readWithNACK(void);



#endif /* I2C_H_ */
