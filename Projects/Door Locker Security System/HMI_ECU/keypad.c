
 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 *  Created on: 7 May 2021
 *
 * Author: Omar Hesham
 *
 *******************************************************************************/

#include "keypad.h"


/***********************************************************************
 *              		Function Prototype                              *
 ***********************************************************************/
#if (N_col==3)
/*
 * Description : convert each index to the actual written value on the keypad.
 */
  static uint8 KeyPad_4x3_adjustKeyNumber(uint8 a_ButtonIndex);

#elif(N_col==4)
  /*
   * Description : convert each index to the actual written value on the keypad.
   */
  static uint8 KeyPad_4x4_adjustKeyNumber(uint8 a_ButtonIndex);
#endif


/***********************************************************************
*              		Function Prototype                              *
***********************************************************************/
uint8 keyPad_getPressedKey(void)
{
	uint8 row,col;

	while(1)
	{// while(1) will be terminated  by "return"
		for(col=0;col<N_col;col++)
		{
			/* active only one column (pin) to be output, and rows pin are inputs  */
			KEYPAD_PORT_DIR = ((0b00010000)<<col);  //EX. C0 -> DDRA = (16<<0) -> PA4 output
			/* set Logic 0 to the activated column , and pull up internal input pins(rows pin)*/
			KEYPAD_PORT_WRITE = (~(0b00010000<<col)) ; // C0 -> PORTA = (1110 1111 ) PA4 = 0 ALL pins PullUP

			for(row=0;row<N_row;row++)
			{
				if(BIT_IS_CLEAR(KEYPAD_PORT_READ,row))
				{
					#if (N_col==3)
					    return ((KeyPad_4x3_adjustKeyNumber(((row*N_col)+col+1))));
					#elif (N_col==4)
					    return KeyPad_4x4_adjustKeyNumber(((row*N_col)+col+1));
				    #endif
				}
			}
		}
	}
}


#if (N_col==3)
/*
 * Description : convert each index to the actual written value on the keypad.
 */
  static uint8 KeyPad_4x3_adjustKeyNumber(uint8 a_ButtonIndex)
  {
	  switch (a_ButtonIndex)
	  {
	  	  case 10 : return '*'; // ASCII Code of *
	  	  	  	  	break ;
	  	  case 11 : return 0 ;
	  	  	  	    break ;
	  	  case 12 : return '#';
		  	  	    break ;
	  	  default : return (a_ButtonIndex);
	  }

  }

#elif(N_col==4)
  /*
   * Description : convert each index to the actual written value on the keypad.
   */
    static uint8 KeyPad_4x4_adjustKeyNumber(uint8 a_ButtonIndex)
    {
    	switch(a_ButtonIndex)
    		{
    			case 1: return 7;
    					break;
    			case 2: return 8;
    					break;
    			case 3: return 9;
    					break;
    			case 4: return '%'; // ASCII Code of %
    					break;
    			case 5: return 4;
    					break;
    			case 6: return 5;
    					break;
    			case 7: return 6;
    					break;
    			case 8: return '*'; /* ASCII Code of '*' */
    					break;
    			case 9: return 1;
    					break;
    			case 10: return 2;
    					break;
    			case 11: return 3;
    					break;
    			case 12: return '-'; /* ASCII Code of '-' */
    					break;
    			case 13: return 13;  /* ASCII of Enter */
    					break;
    			case 14: return 0;
    					break;
    			case 15: return '='; /* ASCII Code of '=' */
    					break;
    			case 16: return '+'; /* ASCII Code of '+' */
    					break;
    			default: return a_ButtonIndex;
    		}
    }
#endif
