/**************************************************************/
/***********     Author    :  Mohamed Kamal             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  26-10-2023             **********/
/***********     File      :  BTL_program            **********/
/**************************************************************/

/*Include Lib Layer*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*Include MCAL Layer*/
#include "RCC_interface.h"
#include "UART_interface.h"
#include "FPEC_interface.h"
#include "GBIO_interface.h"
/*Include HAL Layer*/
//#include "ESP_interface.h
/*Include Component Files*/
#include "BTL_interface.h"
#include "BTL_config.h"
#include "BTL_private.h"




/*****************************************************************
* Name:          ABTL_vidInit                                    *
*                (App Layer Bootloader Init)                     *
*				                                                 *
* Description:   1-Init RCC:									 *
*                   ,enable CLK for UART, FPEC, PORTA            *
*			     2-Init UART: 									 *
*                   ,and configure relevant GBIO Pins		     *
*				                                                 *
* Notes:         You Must:  									 *
* 				  1-Configure RCC SRC Clk To HSI				 *
* 				  2-Configure UART BaudRate to 9600              *
******************************************************************/
void ABTL_vidInit(void)
{
	/* RCC Init*/
	MRCC_voidInitSysClock();
	MRCC_voidEnableClock(MRCC_APB2,14);  //UART1
	MRCC_voidEnableClock(MRCC_APB2,2);   //GBIOA
	MRCC_voidEnableClock(MRCC_AHB,4);    //FPEC

	/*UART Init*/
	MGBIO_vidSetPinDir(MGBIOA,MGBIO_PIN09,MGBIO_MODE_10MHZ_OUT_AF_PP);  //Tx
	MGBIO_vidSetPinDir(MGBIOA,MGBIO_PIN10,MGBIO_MODE_IN_FLOATING);      //Rx
	MUSART1_vidInit();

	/*ESP Init*/
	/*
	HESP_vidInit();
	HESP_vidConnectAP("SALAH","asklaA#1@");
	*/
}


void ABTL_vidStart(void)
{
	u8 Loc_u8TrueOnlyOnce=1;
	u8 Loc_u8BTLTimeUpFlag=0;


	/*Keep reading records and flash it until the end of the Hex File*/
	while (1)
	{

		Loc_u8BTLTimeUpFlag = ABTL_u8ReceiveRecordSynch();
		if (Loc_u8BTLTimeUpFlag == 1)
		{
			vidJumpToApp();
		}
		if (Loc_u8TrueOnlyOnce == 1)
		{
			MFPEC_voidEraseAppArea();
			Loc_u8TrueOnlyOnce=0;
		}


		vidParseRecord();
		MUSART1_vidSendTextSynch ("k");
	}

}  //END Func





/*****************************************************************/
/******                    Helping Functions                ******/
/*****************************************************************/

void vidParseRecord(void)
{
/*
	u8 Loc_u8FinishFlag=0;

	//Get Each record and parse it, until the last record
	while (Loc_u8FinishFlag !=1 )
	{

		Loc_u8FinishFlag = pu8GetSingleRecord(Cpy_u8BufData);


		if (Loc_u8FinishFlag !=1 )
		{
*/
			switch (u8SingleRecord[8])
			{
				case '0': vidFlashDataRecord(u8SingleRecord);   break;
				case '1':  MUSART1_vidSendTextSynch ("k");
					       vidJumpToApp();                      break;
			} //END Switch

}  //Func END


void vidFlashDataRecord(u8* Copy_u8BufData)
{
	u8 DigitLow,DigitHigh,CC,i;
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	u8 DataCounter = 0;
	u8 ValidateCorrectFlashing=0;
	u16* PointerToFlashedRecord;

	/* Get Character Count */
	DigitHigh = AsciToHex (Copy_u8BufData[1]);
	DigitLow  = AsciToHex (Copy_u8BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;

	/* Get Address */
	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
	DataDigit3 = AsciToHex (Copy_u8BufData[6]);

	/* Clear Low Part of Address */
	u32RecordAddressForParser = u32RecordAddressForParser & 0xFFFF0000;
	u32RecordAddressForParser = u32RecordAddressForParser | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);

	for (i=0;i<CC/2; i++)
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		DataDigit2 = AsciToHex (Copy_u8BufData[4*i+11]);
		DataDigit3 = AsciToHex (Copy_u8BufData[4*i+12]);

		Data[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4);
		DataCounter++;
	}

	MFPEC_voidFlashWrite(u32RecordAddressForParser, Data , CC/2);

/*
	while (ValidateCorrectFlashing != 1)
	{
		MFPEC_voidFlashWrite(u32RecordAddressForParser, Data , CC/2);
		PointerToFlashedRecord = MFPEC_vidReadFlashRecord(u32RecordAddressForParser,CC/2);


		if ( (PointerToFlashedRecord[0]!= 0xffff) && (PointerToFlashedRecord[1]!= 0xffff) && (PointerToFlashedRecord[7]!= 0xffff) )
	    {
			ValidateCorrectFlashing=1;
		}

	}
	ValidateCorrectFlashing=0;
*/
}

void vidJumpToApp(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08001800;

	addr_to_call = *(Function_t*)(0x08001804);
	addr_to_call();
}

u8 AsciToHex(u8 Copy_u8Asci)
{
	u8 Result;
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{
		Result = Copy_u8Asci - 48;
	}

	else
	{
		Result = Copy_u8Asci - 55;
	}

	return Result;
}



/*
u8  pu8GetSingleRecord(u8* Cpy_pu8ManyRecords)
{
	static u32 Loc_u32CharCounter=0;
	u8 Loc_u8TempCounter=0;

	while (Cpy_pu8ManyRecords[Loc_u32CharCounter] != ']'  )
	{

		if (Cpy_pu8ManyRecords[Loc_u32CharCounter] == ':' && Cpy_pu8ManyRecords[Loc_u32CharCounter-1] < '0'    )
		{
			while ( Cpy_pu8ManyRecords[Loc_u32CharCounter+1] != ':' && Cpy_pu8ManyRecords[Loc_u32CharCounter+1] != ']'  )
			{

				u8SingleRecord[Loc_u8TempCounter]= Cpy_pu8ManyRecords[Loc_u32CharCounter];
				Loc_u8TempCounter++;
				Loc_u32CharCounter++;

			}
			return 0;
		}
		Loc_u32CharCounter++;
	}

	Loc_u32CharCounter=0;
	return 1;
}
*/


u8 ABTL_u8ReceiveRecordSynch(void)
{
	u8 Loc_u8RecCharCounter=0;
	u16 Loc_u16BTLTimeUp=0;
	u16 Loc_u16MaxTime=0x0FFF;

	while (Loc_u16BTLTimeUp < Loc_u16MaxTime)
	{

		MUSART1_vidReceiveSynch(&u8SingleRecord[Loc_u8RecCharCounter],200);
		if (u8SingleRecord[Loc_u8RecCharCounter] == 255)
		{
			Loc_u16BTLTimeUp++;
		}
		else if ( u8SingleRecord[Loc_u8RecCharCounter] != '\n' )
		{
			Loc_u8RecCharCounter++;
		}
		else if ( u8SingleRecord[Loc_u8RecCharCounter] == '\n' )
		{
			return 0;
		}

	}
	return 1;
}




