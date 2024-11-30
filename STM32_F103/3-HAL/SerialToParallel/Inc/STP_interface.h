/*******************************************************/ 
/* Author : Mohamed Kamal                            */
/* Date   : 14/9/2023                                  */
/* Version: 1.0                                        */
/* File   : STP_interface.h                            */
/*******************************************************/ 
#ifndef     STP_INTERFACE_H
#define     STP_INTERFACE_H

//SERIAL TO PARALLEL


/* Enable Clock and initialize GPIO pins */
void STP_voidInit(void);

/* Send data and halt proram till transfer complete*/
void STP_voidSendSync(u8 cpy_data);

#endif //End Of File