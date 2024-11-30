#include <stdint.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Error_Type.h"


#include "GPIO_interface.h"
#include "STK_interface.h"
#include "LED_MATRIX_interface.h"
#include "LED_MATRIX_private.h"
#include "LED_MATRIX_config.h"








void LED_MATRIX_voidInit(void)
{
	GPIO_voidInitPortPinDirection(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW0_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW1_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW2_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW3_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW4_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW5_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW6_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW7_PIN,OUTPUT_PUSH_PULL_2MHZ);


	GPIO_voidInitPortPinDirection(LEDMATRIX_COL_PORT,LEDMATRIX_COL0_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_COL_PORT,LEDMATRIX_COL1_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_COL_PORT,LEDMATRIX_COL2_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_COL_PORT,LEDMATRIX_COL3_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_COL_PORT,LEDMATRIX_COL4_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_COL_PORT,LEDMATRIX_COL5_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_COL_PORT,LEDMATRIX_COL6_PIN,OUTPUT_PUSH_PULL_2MHZ);
	GPIO_voidInitPortPinDirection(LEDMATRIX_COL_PORT,LEDMATRIX_COL7_PIN,OUTPUT_PUSH_PULL_2MHZ);


}

void LED_MATRIX_voidDisplay(uint8_t *Copy_u8Data)
{

	LED_MATRIX_voidDisableAllColoumns();
	LED_MATRIX_voidSetRowValues(Copy_u8Data[0]);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL0_PIN,LOW);
	STK_voidSetBusyWait(2500);

	LED_MATRIX_voidDisableAllColoumns();
	LED_MATRIX_voidSetRowValues(Copy_u8Data[1]);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL1_PIN,LOW);
	STK_voidSetBusyWait(2500);

	LED_MATRIX_voidDisableAllColoumns();
	LED_MATRIX_voidSetRowValues(Copy_u8Data[2]);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL2_PIN,LOW);
	STK_voidSetBusyWait(2500);

	LED_MATRIX_voidDisableAllColoumns();
	LED_MATRIX_voidSetRowValues(Copy_u8Data[3]);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL3_PIN,LOW);
	STK_voidSetBusyWait(2500);

	LED_MATRIX_voidDisableAllColoumns();
	LED_MATRIX_voidSetRowValues(Copy_u8Data[4]);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL4_PIN,LOW);
	STK_voidSetBusyWait(2500);

	LED_MATRIX_voidDisableAllColoumns();
	LED_MATRIX_voidSetRowValues(Copy_u8Data[5]);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL5_PIN,LOW);
	STK_voidSetBusyWait(2500);

	LED_MATRIX_voidDisableAllColoumns();
	LED_MATRIX_voidSetRowValues(Copy_u8Data[6]);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL6_PIN,LOW);
	STK_voidSetBusyWait(2500);


	LED_MATRIX_voidDisableAllColoumns();
	LED_MATRIX_voidSetRowValues(Copy_u8Data[7]);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL7_PIN,LOW);
	STK_voidSetBusyWait(2500);





}
static void LED_MATRIX_voidDisableAllColoumns(void)
{
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL0_PIN,HIGH);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL1_PIN,HIGH);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL2_PIN,HIGH);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL3_PIN,HIGH);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL4_PIN,HIGH);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL5_PIN,HIGH);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL6_PIN,HIGH);
	GPIO_voidSetPortPinValue(LEDMATRIX_COL_PORT,LEDMATRIX_COL7_PIN,HIGH);

}

static void LED_MATRIX_voidSetRowValues(uint8_t Copy_u8Value)
{
	uint8_t Local_u8Bit;
	Local_u8Bit = GET_BIT(Copy_u8Value,0);
	GPIO_voidSetPortPinValue(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW0_PIN,Local_u8Bit);

	Local_u8Bit = GET_BIT(Copy_u8Value,1);
	GPIO_voidSetPortPinValue(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW1_PIN,Local_u8Bit);

	Local_u8Bit = GET_BIT(Copy_u8Value,2);
	GPIO_voidSetPortPinValue(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW2_PIN,Local_u8Bit);

	Local_u8Bit = GET_BIT(Copy_u8Value,3);
	GPIO_voidSetPortPinValue(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW3_PIN,Local_u8Bit);

	Local_u8Bit = GET_BIT(Copy_u8Value,4);
	GPIO_voidSetPortPinValue(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW4_PIN,Local_u8Bit);

	Local_u8Bit = GET_BIT(Copy_u8Value,5);
	GPIO_voidSetPortPinValue(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW5_PIN,Local_u8Bit);

	Local_u8Bit = GET_BIT(Copy_u8Value,6);
	GPIO_voidSetPortPinValue(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW6_PIN,Local_u8Bit);

	Local_u8Bit = GET_BIT(Copy_u8Value,7);
	GPIO_voidSetPortPinValue(LEDMATRIX_ROW_PORT,LEDMATRIX_ROW7_PIN,Local_u8Bit);





}

