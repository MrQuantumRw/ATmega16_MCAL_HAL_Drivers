/*
 * Module : timer.c
 *
 * Created on: 22 Jun 2021
 * 
 * Author: OMAR HESHAM
 */
#include"timer.h"

static volatile void (*g0_callBackPtr)(void) = NULL_PTR ;
static volatile void (*g2_callBackPtr)(void) = NULL_PTR ;
static volatile void (*g3_callBackPtr)(void) = NULL_PTR ;

void Timer_init(Timer_ConfigType *Timer_Config)
{

   if((Timer_Config->Timer_Type)==TIMER0)
   {
	   TCCR0  = ((Timer_Config->Pin_OC_Status)<<FOC0)|(Timer_Config->T_WG_Mode)|((Timer_Config->Pin_OC_Operation)<<COM00)|((Timer_Config->T_Clock)<<CS00);
	   TIMSK |=((Timer_Config->T_OVF_INT)<<TOIE0)|((Timer_Config->T_COMP_INT)<<OCIE0);
	   TCNT0  = Timer_Config->Intial_Val ;
	   OCR0   = Timer_Config->Compare_OCx_Val ;
	   DDRB |= (1<<PB3);      //OC0 As Output
   }

   else if((Timer_Config->Timer_Type)==TIMER2)
   {
	   TCCR2  = ((Timer_Config->Pin_OC_Status)<<FOC2)|(Timer_Config->T_WG_Mode)|((Timer_Config->Pin_OC_Operation)<<(COM20))|((Timer_Config->T_Clock)<<CS20);
	   TIMSK |= ((Timer_Config->T_OVF_INT)<<TOIE2)|((Timer_Config->T_COMP_INT)<<OCIE2);
	   TCNT2 = Timer_Config->Intial_Val;
	   OCR2  = Timer_Config->Compare_OCx_Val;
	   DDRD |=(1<<PD7);      //OC2 as Output
   }

   else if ((Timer_Config->Timer_Type)== TIMER1)
   {
	   TCCR1A  = ((Timer_Config->Pin_OC_Status)<<FOC1B)|(((Timer_Config->T_WG_Mode)&0x03)<<WGM10)|((Timer_Config->Pin_OC_Operation)<<COM1B0);
	   TCCR1B |= (((Timer_Config->T_WG_Mode)>>2)<<WGM12)|((Timer_Config->T_Clock)<<CS10);
	   TIMSK  |= ((Timer_Config->T_OVF_INT)<<TOIE1)|((Timer_Config->T_COMPA_INT)<<OCIE1A)|((Timer_Config->T_COMPB_INT)<<OCIE1B);
	   TCNT1   = Timer_Config->Intial_Val ;
	   if((Timer_Config->T_WG_Mode == T_16Bit_MODE_8)||(Timer_Config->T_WG_Mode == T_16Bit_MODE_10)||(Timer_Config->T_WG_Mode == T_16Bit_MODE_12)||(Timer_Config->T_WG_Mode == T_16Bit_MODE_14))
	   {
		   ICR1  = Timer_Config->Compare_OCRA_Val ;
		   DDRD |=(1<<PD6) ; //ICP as Output
	   }

	   else
	   {
		   if((Timer_Config->Pin_OC_Status == ENABLE_OC1A_PIN) || (Timer_Config->Pin_OC_Status == ENABLE_OC1A_OC1B_PIN))
		   {
			   OCR1A = Timer_Config->Compare_OCRA_Val ;
			   DDRD |= (1<<PD5) ;
		   }
		   else if((Timer_Config->Pin_OC_Status == ENABLE_OC1B_PIN) || (Timer_Config->Pin_OC_Status == ENABLE_OC1A_OC1B_PIN))
		   {
			   OCR1B = Timer_Config->Compare_OCRB_Val;
			   DDRD |= (1<<PD4) ;
		   }

	   }
   }


}

void Timer_setCallBack(void (*fun_ptr)(void),const Timer_ConfigType *Timer_Config)
{
	if((Timer_Config->Timer_Type)==TIMER0)
	{
		g0_callBackPtr = fun_ptr ;
	}

	else if((Timer_Config->Timer_Type)==TIMER2)
	{
	   g2_callBackPtr = fun_ptr ;
	}

	else if(Timer_Config->Timer_Type == TIMER1 )
	{
		g3_callBackPtr = fun_ptr ;
	}


}



ISR(TIMER0_OVF_vect)
{
	if(g0_callBackPtr != NULL_PTR)
	{
		(*g0_callBackPtr)();
	}
}

ISR(TIMER2_OVF_vect)
{
	if(g2_callBackPtr != NULL_PTR)
	{
		(*g2_callBackPtr)();
	}
}


ISR(TIMER1_OVF_vect)
{
	if(g3_callBackPtr != NULL_PTR)
	{
		(g3_callBackPtr)() ;
	}

}


