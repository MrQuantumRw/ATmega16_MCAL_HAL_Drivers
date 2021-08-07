/*
 * Module     :  
 *  
 * File Name  :  external_eeprom.h
 *
 * Created on : 4 Jun 2021
 *
 * Author     : OMAR HESHAM 
 */

#include"std_types.h"

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_



/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 address,uint8 data);
uint8 EEPROM_readByte(uint16 address,uint8 *data);
#endif /* EXTERNAL_EEPROM_H_ */
