/*
 * Module : adc.c
 *
 * Created on: 16 Jun 2021
 * 
 * Author: OMAR HESHAM
 */

#include"adc.h"


/*
 * Description :Function to Initiate ADC Module
 *
 * @Arguments: Configuration Structure
 *
 * @Steps:		ADMUX : 1. select VREF
     			        2. select Adjust

	           ADCSRA :  1. Enable ADC
						 2. select Auto Trigger
						 3. select Interrupt Enable
						 4. Select Prescaler
 *
 */
void ADC_init(ADC_ConfigType *config)
{
	/*                ADMUX Register:  ADC Multiplexer Selection
	**  Bit7:6 – REFS1:0:  VREF Reference Selection Bits [external AVcc = 1 , Internal 2.6V = 3 ]   <Inti Function:Config>
	**	Bit 5 – ADLAR: ADC Left Adjust Result   [ Right Adjust = 0 , Left Adjust = 1 ]              <Inti Function:Config>
	**	Bits 4:0 – MUX4:0: Analog Channel [ADC0:ADC7]==>[0:7]
	**/
    ADMUX = ((config->V_Ref)<<REFS0)|((config->D_Adjust)<<ADLAR);
/*
                          ADCSRA :  ADC Control and Status Register A
**	Bit 7 – ADEN: ADC Enable 						<Inti Function:Static>
**	Bit 6 – ADSC: ADC Start Conversion          	<Read Function>  note : 25 delay cycle needed
**	Bit 5 – ADATE: ADC Auto Trigger Enable      	<Inti Function:Configure>
**	Bit 4 – ADIF: ADC Interrupt Flag            	<Read Function>  Monitor flag and clear by software
**	Bit 3 – ADIE: ADC Interrupt Enable				<Inti Function:Configure>
**	Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits	<Inti Function:Configure> [DIV_2=1,DIV_4,DIV_8,DIV_16,DIV_32,DIV_64,DIV_128]
**
*/
	ADCSRA = (1<<ADEN)|((config->A_Trigger)<<ADATE)|((config->Interrupt)<<ADIE)|((config->Clock)<<ADPS0);

}

/*
 * Description :Function to Initiate ADC Module
 *
 * @Arguments: channel index (0:7)
 *
 * @Steps:	ADMUX : 1.select Channel

	        ADCSRA:	2.Start conversion
			        3.Monitor ADIF
		        	4.Clear ADIF (write One)
 *
 * @  return:  ADC  (uint16 value)
 *
 */


uint16 ADC_read(uint8 channel)
{
	ADMUX = (ADMUX & 0xE0) | (channel);
	SET_BIT(ADCSRA,ADSC);
	while(BIT_IS_CLEAR(ADCSRA,ADIF));

	SET_BIT(ADCSRA,ADIF);

	return ADC ;
}
