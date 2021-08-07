/*
 * Module : timer.h
 *
 * Created on: 22 Jun 2021
 * 
 * Author: OMAR HESHAM
 */

#ifndef TIMER_H_
#define TIMER_H_


#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/************************************************************************************************
 *                                      User Defined Variables                                  *
 ************************************************************************************************/

typedef enum
{
  TIMER0,TIMER1,TIMER2
}Timer_Selection;

typedef enum
{
	DISABLE_OCx_PIN , ENABLE_OCx ,ENABLE_OC1B_PIN =1 ,ENABLE_OC1A_PIN ,ENABLE_OC1A_OC1B_PIN
}Timer_OC_Pin_Status;

typedef enum
{
  WG_NORMAL,
  T_16Bit_MODE_1,T_16Bit_MODE_2,T_16Bit_MODE_3,
  T_16Bit_MODE_4,T_16Bit_MODE_5,T_16Bit_MODE_6,
  T_16Bit_MODE_7,T_16Bit_MODE_8,T_16Bit_MODE_9,
  T_16Bit_MODE_10,T_16Bit_MODE_11,T_16Bit_MODE_12,
  T_16Bit_MODE_13,T_16Bit_MODE_14,T_16Bit_MODE_15,
  T_8Bit_WG_PHASE_CORRECT=0x40,T_8Bit_WG_CTC=0x08,T_8Bit_WG_PWM=0x48
}Timer_WGConfig;



typedef enum
{
  OCx_NORMAL ,OCx_TOGGLE ,OCx_CLEAR_ON_MATCH ,OCx_SET_ON_MATCH ,
  Toggle_OC1A_OC1B=5 ,ClearOnMatch_OC1A_OC1B=10 ,SetONMatch_OC1A_OC1B=15
}Timer_OC_Pin_Opertion;

typedef enum
{
  STOP_CLOCK,FCU_CLOCK,DIV_8,T2_DIV_32=3,DIV_64=3,DIV_256=4,T2_DIV_64=4,T2_DIV_128=5,DIV_1024=5,T2_DIV_256=6,T2_DIV_1024=7
}Timer_ClockConfig;


typedef enum
{
  DISABLE_COMP_INT,ENABLE_COMP_INT
}Timer_COMP_INT_Config;


typedef enum
{
  DISABLE_COMPA_INT,ENABLE_COMPA_INT
}Timer_COMPA_INT_Config;

typedef enum
{
  DISABLE_COMPB_INT,ENABLE_COMPB_INT
}Timer_COMPB_INT_Config;

typedef enum
{
  DISABLE_OVF_INT,ENABLE_OVF_INT
}Timer_OVF_INT_Config;



typedef struct
{
  Timer_Selection Timer_Type;
  uint16 Intial_Val ;
  uint8  Compare_OCx_Val;
  uint16 Compare_OCRA_Val ;
  uint16 Compare_OCRB_Val;
  Timer_OC_Pin_Status Pin_OC_Status ;
  Timer_OC_Pin_Opertion Pin_OC_Operation;
  Timer_WGConfig  T_WG_Mode;
  Timer_ClockConfig T_Clock;
  Timer_COMP_INT_Config T_COMP_INT;
  Timer_COMPA_INT_Config T_COMPA_INT;
  Timer_COMPB_INT_Config T_COMPB_INT;
  Timer_OVF_INT_Config T_OVF_INT;
}Timer_ConfigType;

#endif /* TIMER_H_ */
