/*
 * Module : adc.h
 *
 * Created on: 16 Jun 2021
 * 
 * Author: OMAR HESHAM
 */

#ifndef ADC_H_
#define ADC_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/************************************************************************************************
 *                                      User Defined Variables                                  *
 ************************************************************************************************/
typedef enum
{
	VREF_EX=1,VREF_IN=3
}Ref_Volt ;
typedef enum
{
  R_ADJUST,L_ADJUST
}Data_Adust;
typedef enum
{
  DISABLE_AUTO_TRIGGER,ENABLE_AUTO_TRIGGER
}Auto_Trigger ;

typedef enum
{
  DISABLE_INTRRUPT,ENABLE_INTRRUPT
}Interrupt_Enable ;

typedef enum
{
   DIV_2=1,DIV_4,DIV_8,DIV_16,DIV_32,DIV_64,DIV_128
}ADC_Clock ;    //ADC must operate in range 50-200Khz

typedef struct
{
	Ref_Volt V_Ref;
	Data_Adust D_Adjust;
	Auto_Trigger A_Trigger ;
	Interrupt_Enable  Interrupt;
    ADC_Clock Clock ;
}ADC_ConfigType;


/***********************************************************************************************
 * 									Functions Prototypes                                       *
 ***********************************************************************************************/

void ADC_init(ADC_ConfigType *config);
uint16 ADC_read(uint8 channel) ;



#endif /* ADC_H_ */
