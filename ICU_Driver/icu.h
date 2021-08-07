/*
 * icu.h
 *
 *  Created on: 2 May 2021
 *      Author: Omar Hesham
 */

#ifndef ICU_H_
#define ICU_H_


#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_Clock;

typedef enum
{
	FALLING,RISING
}Icu_EdgeType;

typedef struct
{
	Icu_Clock clock;
	Icu_EdgeType edge;
}Icu_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */

void Icu_init(const Icu_ConfigType *Config_Ptr);

/*
 * Description : function to set call Back function address
 *  NOte:
   1. this function is define at ICU.c  but called at App.c  ( Direct call)
   2. argument: the address of App.c function
   3. Discretion : holed the address of call back function at g_callBackPtr
 */

void Icu_setCallBack(void (*a_Ptr)(void));

/*
 * Description : function to set the required edge detection
 * Arguments   :(enum) const  Icu_EdgeType  edgeType
 */

void Icu_setEdgeDetectionType(const Icu_EdgeType edgeType);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void);

/*
 * Description : function to get ICR1 that save value to Timer1 counter at edge detection Time
 * Return      :  ICR1 ;
 */

uint16 Icu_getInputCaptureValue(void);


/*
 * Description : function to Deactivate ICU Module
 */

void Icu_DeInit(void);

#endif /* ICU_H_ */
