/**************************************************************/
/***********     Author    :  Mohamed Kamal             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  26-10-2023             **********/
/***********     File      :  BTL_private            **********/
/**************************************************************/

#ifndef _BTL_PRIVATE_H
#define _BTL_PRIVATE_H



/****************************************/
/*         User Defined Variables       */
/****************************************/
typedef void (*Function_t)(void);


/****************************************/
/*         Global Variables             */
/****************************************/
Function_t addr_to_call = 0;    //used to jump to the app area
u32 u32RecordAddressForParser= 0x08000000;  //The parser uses it to store the Address from the record, to be sent to the FPEC
u16 Data[20];    //The parser uses it to store the data from the record, to be sent to the FPEC
u8  u8SingleRecord[50];
u8 u8OK[3]="ok";
/*************************************/
/*      Private Helping Functions    */
/*************************************/
//u8  pu8GetSingleRecord(u8* Cpy_pu8ManyRecords);
u8 ABTL_u8ReceiveRecordSynch(void);
void vidParseRecord(void);
void vidJumpToApp(void);
u8 AsciToHex(u8 Copy_u8Asci);
void vidReadFlashRecord(u16 Cpy_u16RecLineNum);
void vidFlashDataRecord(u8* Copy_u8BufData);



#endif
