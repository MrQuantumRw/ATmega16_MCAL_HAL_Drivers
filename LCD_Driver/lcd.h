/*
 *  Module : lcd.h
 *
 *  Created on: 13 Jun 2021
 *     
 *  Author: OMAR HESHAM
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

 /*************************************************************************
  * 					LCD PINS configuration                            *
  ************************************************************************/
 //Control pins RS,RW,E
#define RS PD4
#define RW PD5
#define E PD6

#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_PORT_DIR DDRD

#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR DDRC

#define DATA_BITS_MODE 4
#define UPPER_PORT_PINS

// Choose LCD Size [2x16 or 4x20]
#define LCD_ROW 2
#define LCD_COLUMN 16


 /*************************************************************************
  * 					        LCD COMANDS                               *
  ************************************************************************/
#define CLEAR 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_init(void);
void LCD_command(uint8 command);
void LCD_displayChar(uint8 data);
void LCD_displayString(uint8 *Str);
void LCD_clear(void);
void LCD_displayStringRowColumn(const uint8 *Str,uint8 row,uint8 clo);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_intgerToString(uint8 data);




#endif /* LCD_H_ */
