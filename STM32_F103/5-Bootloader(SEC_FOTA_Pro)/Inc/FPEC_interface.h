/**************************************************************/
/***********     Author    :  Mohamed Kamal             **********/
/***********     Version   :  V0.1                   **********/
/***********     Date      :  17-10-2023             **********/
/***********     File      :  FPEC_interface         **********/
/**************************************************************/

#ifndef _FPEC_INTERFACE_H
#define _FPEC_INTERFACE_H


/*****************************************************************/
/******                        Functions                    ******/
/*****************************************************************/
void MFPEC_vidFlashPageErase(u8 Cpy_u8PageNum);
void MFPEC_voidEraseAppArea(void);

/*Lenth= number of elemnts in the Data Array*/
void MFPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);
u16* MFPEC_vidReadFlashRecord(u32 Copy_u32Address,u8 Copy_u8Length);

/*****************************************************************/
/******                Function's parameters                ******/
/*****************************************************************/


#endif
