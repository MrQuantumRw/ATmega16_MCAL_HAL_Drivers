/*
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Created on: 7 May 2021
 *
 * Author: Omar Hesham
 *
 *******************************************************************************/


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/********************************************************
 * 			HardWare Configuration                       *
 ********************************************************/
#define N_col 3
#define N_row 4

#define KEYPAD_PORT_DIR DDRA
#define KEYPAD_PORT_WRITE PORTA
#define KEYPAD_PORT_READ PINA


/************************************************************
 *             Functions Prototype                          *
 ************************************************************/

/* Description : function to get the pressed key on keypad
 * return	   : The actual value of written in the keypad
 */
uint8 keyPad_getPressedKey(void);


#endif /* KEYPAD_H_ */
