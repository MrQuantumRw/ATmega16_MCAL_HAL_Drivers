/*
 * Module     :  ICU
 * File Name  : icu.c
 *
 * Description: Source file for the AVR ICU driver
 * Created on : 2 May 2021
 * Author     : Omar Hesham
 */
#include"icu.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables (Pointer to function) to hold the address of the call back function in the application */
static void (*g_callBackPtr)(void) = NULL_PTR ;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
/*Use ISR of input capture to call back ( execute )the App.c function */

ISR(TIMER1_CAPT_vect)
{
	 /*Call the Call Back function in the application after the edge is detected */
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
*                      Functions Prototypes                           *
*******************************************************************************/
/*
		 * Description : Function to initialize the ICU driver
		 * 	1. Configure ICP1 / PD6 n input pin
		 * 	2. Initialize Timer1 Registers :mode (Normal)
		 * 	3. Set the required clock. (n = 1)
		 * 	4. Set the required edge detection.
		 * 	3. Enable the Input Capture Interrupt.
		 * 	4. Initial Value for Timer1
		 * 	5. Initial Value for the input capture register
		 *
		 */
void Icu_init(const Icu_ConfigType *Config_Ptr)
{
	/*Configure ICP1 / PD6 n input pin*/
	DDRD &=~(1<<PD6);

	/*Timer1 Mode : normal */
	TCCR1A |= (1<<FOC1A)|(1<<FOC1B);

	/* Timer1 clock*/
	TCCR1B  = (TCCR1B & 0xF8) | (Config_Ptr->clock);

	/*Set the required edge detection.*/
	TCCR1B  = (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<6);

	/* Enable the Input Capture Interrupt */
	TIMSK |= (1<<TICIE1);

	/* Initial Value for Timer1 */
	TCNT1 = 0 ;

	/* Initial Value for the input capture register */
	ICR1 = 0 ;

}

/*
 * Description : function to set call Back function address
 *  NOte:
   1. this function is define at ICU.c  but called at App.c  ( Direct call)
   2. argument: the address of App.c function
   3. Discretion : holed the address of call back function at g_callBackPtr
 */

void Icu_setCallBack(void (*a_Ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_Ptr ;
}

/*
 * Description : function to set the required edge detection
 * Arguments   :(enum) const  Icu_EdgeType  edgeType
 */

void Icu_setEdgeDetectionType(const Icu_EdgeType a_edgeType)
{
	/* insert the required edge type in ICES1 bit in TCCR1B Register */
	TCCR1B  = (TCCR1B & 0xBF) | ((a_edgeType)<<6);
}

/*
 * Description : function to get ICR1 that save value to Timer1 counter at edge detection Time
 * Return      :  ICR1 ;
 */

uint16 Icu_getInputCaptureValue(void)
{
	return ICR1 ;
}


/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void)
{
	TCNT1 = 0 ;
}

/*
 * Description : function to Deactivate ICU Module
 */

void Icu_DeInit(void)
{
	/* Clear All Timer1 Registers */
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
		ICR1 = 0;

		/* Disable the Input Capture interrupt */
		TIMSK &= ~(1<<TICIE1);
}

