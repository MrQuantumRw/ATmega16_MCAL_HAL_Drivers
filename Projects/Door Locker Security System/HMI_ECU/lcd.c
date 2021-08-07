/*
 *  Module : lcd.c
 *
 *  Created on: 13 Jun 2021
 *     
 *  Author: OMAR HESHAM
 */


/************************************************
 * 		            Main Steps          		*
 ***********************************************/
/*
 * init function
 * 1. configure data port "Output"
 * 2. Configure the control pins(E,RS,RW) as output
 * 3. command : 2 lines , 8 bit data mode , 5*8 dot display
 * 4. command : cursor off
 * 5. command : clear
 */



#include"lcd.h"

void LCD_init(void)
{
	//configure control pins direction ==> output
	LCD_CTRL_PORT_DIR |= (1<<RS)|(1<<RW)|(1<<E);
#if (DATA_BITS_MODE==4)

	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_DIR = 0xF0 ;   //configure the 4 high pins to be output
    #else
	LCD_DATA_PORT_DIR = 0x0F ;
    #endif
	LCD_command(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
	LCD_command(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
#elif(DATA_BITS_MODE == 8)

	LCD_DATA_PORT_DIR = 0xFF ; // Eight bits output
	LCD_command(TWO_LINE_LCD_Eight_BIT_MODE) ; // 2 lines, 8 bit data mode , 5*8 dots
#endif
	LCD_command(CURSOR_OFF);
	LCD_command(CLEAR) ;
}

/*
 *  * command function
 * 1. clear RS , instruction mode
 * 2. clear RW , write data to LCD
 * 3. delay Tas= 50ns , 1ms
 * 4. set E
 * 5. delay  Tpw - Tdws = 190ns , 1 ms
 * 6. DATA PORT = command , send command tp data pins
 * 7. delay Tdsw = 100ns  for processing data
 * 8. Disable E .
 * 9. Delay  Th = 13ns , 1ms
 *
 */
void LCD_command(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS); // Instruction MODE RS=0
	CLEAR_BIT(LCD_CTRL_PORT,RW); // write data to LCD
	_delay_ms(1);                // delay Tas= 50ns
	SET_BIT(LCD_CTRL_PORT,E);    // Enable E delay
	_delay_ms(1);                // Tpw - Tdws = 190ns

#if(DATA_BITS_MODE==4)

	#ifdef UPPER_PORT_PINS          //if upper pins of data port is defined
	       LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);      // reset higher pins , then cast higer 4 its of command
	#else                          // if Lower pins of data port is defined
	     LCD_DATA_PORT = (LCD_DATA_PORT & 0XF0) | ((command & 0xF0)>>4);  // reset lower pins , then shift higher 4 bits of command
   #endif

	_delay_ms(1);                // delay Tdsw = 100ns  for processing data
	CLEAR_BIT(LCD_CTRL_PORT,E);  // Disable E
	_delay_ms(1) ;               // Delay  Th = 13ns
	SET_BIT(LCD_CTRL_PORT,E);    // Enable E delay
	_delay_ms(1);                // Tpw - Tdws = 190ns
/* SEND lower 4 bits of command*/
	#ifdef UPPER_PORT_PINS          //if upper pins of data port is defined
	       LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F)<<4);      // reset higher pins , then cast higer 4 its of command
	#else                          // if Lower pins of data port is defined
	     LCD_DATA_PORT = (LCD_DATA_PORT & 0XF0) | (command & 0x0F);  // reset lower pins , then shift higher 4 bits of command
   #endif

	_delay_ms(1);                // delay Tdsw = 100ns  for processing data
	CLEAR_BIT(LCD_CTRL_PORT,E);  // Disable E
	_delay_ms(1) ;               // Delay  Th = 13ns

#elif (DATA_BITS_MODE == 8)

   LCD_DATA_PORT = command ;    // send command to data pins
	_delay_ms(1);                // delay Tdsw = 100ns  for processing data
	CLEAR_BIT(LCD_CTRL_PORT,E);  // Disable E
	_delay_ms(1) ;
#endif
}
/*
 *  * Data fuction
 *1. Enable RS , data mode
 * 2. clear RW , write data to LCD
 * 3. delay Tas= 50ns , 1ms
 * 4. set E
 * 5. delay  Tpw - Tdws = 190ns , 1 ms
 * 6. DATA PORT = data , send command tp data pins
 * 7. delay Tdsw = 100ns  for processing data
 * 8. Disable E .
 * 9. Delay  Th = 13ns , 1ms
 *
 */
void LCD_displayChar(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,RS);     //Enable RS , data mode
	CLEAR_BIT(LCD_CTRL_PORT,RW); // write data to LCD
	_delay_ms(1);                // delay Tas= 50ns
	SET_BIT(LCD_CTRL_PORT,E);    // Enable E delay
	_delay_ms(1);                // Tpw - Tdws = 190ns
#if(DATA_BITS_MODE== 4)

//Send Higher 4 bits of data
	#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F)|( data & 0xF0) ;    // send DATA to data pins
    #else
		LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0)|( (data & 0xF0) >> 4 ) ;    // send DATA to data pins
	#endif
		_delay_ms(1);                // delay Tdsw = 100ns  for processing data
		CLEAR_BIT(LCD_CTRL_PORT,E);  // Disable E
		_delay_ms(1) ;
//Send Lower 4 bits of data
	SET_BIT(LCD_CTRL_PORT,E);    // Enable E delay
	_delay_ms(1);
	#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F)|( (data & 0x0F) << 4) ;    // send DATA to data pins
	#else
		LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0)|( (data & 0x0F) ) ;    // send DATA to data pins
	#endif
		_delay_ms(1);                // delay Tdsw = 100ns  for processing data
		CLEAR_BIT(LCD_CTRL_PORT,E);  // Disable E
		_delay_ms(1) ;

 #elif (DATA_BITS_MODE== 8 )
	LCD_DATA_PORT = data ;    // send command to data pins
	_delay_ms(1);                // delay Tdsw = 100ns  for processing data
	CLEAR_BIT(LCD_CTRL_PORT,E);  // Disable E
	_delay_ms(1) ;
#endif
}
void LCD_displayString(uint8 *Str)
{
	uint8 i = 0 ;
	while(Str[i] != '\0')
	{
		LCD_displayChar(Str[i]);
		i++ ;
	}
}
void LCD_clear(void)
{
	LCD_command(CLEAR);
}


void LCD_displayStringRowColumn(const uint8 *Str,uint8 row,uint8 col)
{
	LCD_goToRowColumn(row,col);
	LCD_displayString(Str);
}


/*
 * LCD_location  = 0b10000000 + Address = 0x80 + Address
 *
 * for LCD 2*16 ==> Row Address [0x00,0x40]
 * for LCD 4*16 ==> Row Address [0x00,0x40,0x10,0x50]
 * for LCD 4*20 ==> Row Address [0x00,0x40,0x14,0x54]
 */
void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 address ;
#if( (LCD_ROW ==2 ) && (LCD_COLUMN==16) )
	switch(row)
   {

         case 0 :
    	        address = col ;
    	        break ;
         case 1 :
        	    address = 0x40+col ;
        	    break;

         case 2 :
        	    address = 0x10+col ;
        	    break;
         case 3 :
        	    address = 0x50+col ;
        	    break ;
   }
#elif((LCD_ROW == 4 ) && (LCD_COLUMN == 20) )

	switch(row)
   {

         case 0 :
    	        address = col ;
    	        break ;
         case 1 :
        	    address = 0x40+col ;
        	    break;

         case 2 :
        	    address = 0x14+col ;
        	    break;
         case 3 :
        	    address = 0x54+col ;
        	    break ;
   }
#endif
   /* Location command = 0b10000000 + Address = 0x80 + Address  = SET_CURSOR_LOCATION + ADDREEESS*/
   LCD_command((SET_CURSOR_LOCATION|address)) ;
}


void LCD_intgerToString(uint8 data)
{
  uint8 buff[16] ;
  itoa(data,buff,10);
  LCD_displayString(buff);

}

