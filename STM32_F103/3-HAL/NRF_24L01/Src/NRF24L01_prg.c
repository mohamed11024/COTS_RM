#include "NRF24L01_int.h"
#include "NRF24L01_cfg.h"
#include "NRF24L01_prv.h"

#include "STM32F103.h"
#include "RCC_int.h"
#include "SysTick_int.h"
#include "GPIO_int.h"
#include "SPI_int.h"

#include <stdint.h>


/*********************************Configuring Pins of SPI_1*********************************/
PinConfig_t CSN_1 =
{
		.PIN_Port = PORTA,
		.PIN_Mode = Output_mode_max_speed_50_MHz,
		.PIN_OutputType = General_purpose_output_push_pull,
		.PIN_Number = PIN4
};
PinConfig_t SCK_1 =
{
		.PIN_Port = PORTA,
		.PIN_Mode = Output_mode_max_speed_50_MHz,
		.PIN_OutputType = General_purpose_output_push_pull,
		.PIN_Number = PIN5
};
PinConfig_t MOSI_1 =
{
		.PIN_Port = PORTA,
		.PIN_Mode = Output_mode_max_speed_50_MHz,
		.PIN_OutputType = General_purpose_output_push_pull,
		.PIN_Number = PIN7
};
PinConfig_t MISO_1 =
{
		.PIN_Port = PORTA,
		.PIN_Mode = INPUT,
		.PIN_InputType = Input_with_pull_up_pull_down,
		.PIN_Number = PIN6
};

/*******************************************************************************************/

/**************************************Configuring SPI_1***********************************/
SPI_HandleTypeDef_t CONFG_SPI_1 =
{
		.SPI_ID = SPI_Channel_1,
		.MasterSlaveSelection = SPI_Master,
		.SPI_BaudRate = Fclk_over_8,
		.SingleMaster_MultiMaster = SPI_SSOutputEnable,
		.SPI_Enable = SPI_Enable

};
/******************************************************************************************/




/*********************************Configuring Pins of SPI_2*********************************/
PinConfig_t CSN_2 =
{
		.PIN_Port = PORTB,
		.PIN_Mode = Output_mode_max_speed_50_MHz,
		.PIN_OutputType = General_purpose_output_push_pull,
		.PIN_Number = PIN12
};
PinConfig_t SCK_2 =
{
		.PIN_Port = PORTB,
		.PIN_Mode = Output_mode_max_speed_50_MHz,
		.PIN_OutputType = General_purpose_output_push_pull,
		.PIN_Number = PIN13
};
PinConfig_t MOSI_2 =
{
		.PIN_Port = PORTB,
		.PIN_Mode = Output_mode_max_speed_50_MHz,
		.PIN_OutputType = General_purpose_output_push_pull,
		.PIN_Number = PIN15
};
PinConfig_t MISO_2 =
{
		.PIN_Port = PORTB,
		.PIN_Mode = INPUT,
		.PIN_InputType = Input_with_pull_up_pull_down,
		.PIN_Number = PIN14
};

/******************************************************************************************/

/**************************************Configuring SPI_1***********************************/
SPI_HandleTypeDef_t CONFG_SPI_2 =
{
		.SPI_ID = SPI_Channel_2,
		.MasterSlaveSelection = SPI_Master,
		.SPI_BaudRate = Fclk_over_8,
		.SingleMaster_MultiMaster = SPI_SSOutputEnable,
		.SPI_Enable = SPI_Enable

};

/******************************************************************************************/




/*********************************Configuring Pins of SPI_3*********************************/
PinConfig_t CSN_3 =
{
		.PIN_Port = PORTA,
		.PIN_Mode = Output_mode_max_speed_50_MHz,
		.PIN_OutputType = General_purpose_output_push_pull,
		.PIN_Number = PIN15
};
PinConfig_t SCK_3 =
{
		.PIN_Port = PORTB,
		.PIN_Mode = Output_mode_max_speed_50_MHz,
		.PIN_OutputType = General_purpose_output_push_pull,
		.PIN_Number = PIN3
};
PinConfig_t MOSI_3 =
{
		.PIN_Port = PORTB,
		.PIN_Mode = Output_mode_max_speed_50_MHz,
		.PIN_OutputType = General_purpose_output_push_pull,
		.PIN_Number = PIN5
};
PinConfig_t MISO_3 =
{
		.PIN_Port = PORTB,
		.PIN_Mode = INPUT,
		.PIN_InputType = Input_with_pull_up_pull_down,
		.PIN_Number = PIN4
};

/******************************************************************************************/

/**************************************Configuring SPI_3***********************************/
SPI_HandleTypeDef_t CONFG_SPI_3 =
{
		.SPI_ID = SPI_Channel_3,
		.MasterSlaveSelection = SPI_Master,
		.SPI_BaudRate = Fclk_over_8,
		.SingleMaster_MultiMaster = SPI_SSOutputEnable,
		.SPI_Enable = SPI_Enable

};

/******************************************************************************************/




void NRF_voidInit(SPI_ID_t SPI_id)
{

	RCC_APB2EnableCLK(AFIOEN);
	if(SPI_id == SPI_1)
	{
		RCC_APB2EnableCLK(SPI1EN);

		GPIO_u8PinInit(&CSN_1);
		GPIO_u8PinInit(&SCK_1);
		GPIO_u8PinInit(&MOSI_1);
		GPIO_u8PinInit(&MISO_1);

		SPI_vInit(&CONFG_SPI_1);

		GPIO_vSetOutputPinValue(PORTA, PIN4, OUTPUT_HIGH);



	}
	else if(SPI_id == SPI_2)
	{

		RCC_APB1EnableCLK(SPI2EN);

		GPIO_u8PinInit(&CSN_2);
		GPIO_u8PinInit(&SCK_2);
		GPIO_u8PinInit(&MOSI_2);
		GPIO_u8PinInit(&MISO_2);

		SPI_vInit(&CONFG_SPI_2);

		GPIO_vSetOutputPinValue(PORTB, PIN12, OUTPUT_HIGH);

	}


	else if(SPI_id == SPI_3)
	{
		RCC_APB1EnableCLK(SPI3EN);

		GPIO_u8PinInit(&CSN_3);
		GPIO_u8PinInit(&SCK_3);
		GPIO_u8PinInit(&MOSI_3);
		GPIO_u8PinInit(&MISO_3);

		SPI_vInit(&CONFG_SPI_3);

		GPIO_vSetOutputPinValue(PORTA, PIN15, OUTPUT_HIGH);


	}

}


uint8_t NRF_RD_CMD(SPI_ID_t SPI_id, uint8_t RegAdd)
{
	uint8_t Cmdval;

	SPI_voidCS(SPI_Channel_1, 0);

	Cmdval = SPI_vSendReceive(&CONFG_SPI_1,(RegAdd & nrf_read));


	SPI_voidCS(SPI_Channel_1, 1);



	return Cmdval;


}

















