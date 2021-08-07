/*
 * Module :
 *
 * File Name : spi.h
 *
 * Description : 
 *
 * Created on: 16 May 2021
 *      
 * Author: Omar Hesham
 */
/*
 * Module : SPI
 *
 * File Name : spi.h
 *
 * Description : Header file for the SPI AVR driver
 *
 * Created on: 11 May 2021
 *
 * Author: Omar Hesham
 */

#ifndef SPI_H_
#define SPI_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define SPI_SPEED  NORMAL

#define NORMAL 0
#define DOUBLE 1

/*******************************************************************************
 *                      Types Declaration                                       *
 *******************************************************************************/

typedef enum
{
	MSB,LSB
}Data_Order;

typedef enum
{
	SLAVE,MASTER
}Status_ConfigType;

typedef enum
{
	IDLE_LOW,IDLE_HIGH
}Polarity_ConfigType;

typedef enum
{
	SAMPLE_RISING,SAMPLE_FALLIN
}Phase_ConfigType;

typedef enum
{
	DIV_4,DIV_16,DIV_64,DIV_128
}Clock_ConfigType;

typedef struct
{
        Data_Order Order ;
        Status_ConfigType StatusConfig;
	Polarity_ConfigType PolarityConfig;
	Phase_ConfigType Phase_Config ;
	Clock_ConfigType Clock_Config ;
}SPI_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void SPI_init(const SPI_ConfigType *a_ConfigPtr);
void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_configSlave(const SPI_ConfigType *a_ConfigPtr);
void SPI_configMaster(const SPI_ConfigType *a_ConfigPtr);
void SPI_init(const SPI_ConfigType *a_ConfigPtr);
void SPI_sendByte(const uint8 data);
void SPI_sendString(const uint8 *Str);
uint8 SPI_receiveByte(void);
void SPI_receiveString(uint8 *Str);


#endif /* SPI_H_ */

