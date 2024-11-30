/********************************************************/ 
/* Author : Mohamed Kamal                             */
/* Date   : 5/9/2023                                    */
/* Version: 1.0                                         */
/* File   : STP_program.c                               */
/********************************************************/ 

// 1- include Libraries 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// 2- include interface file of needed lower layers
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "STK_interface.h"

// 3- include driver files
#include "STP_interface.h"
#include "STP_private.h"
#include "STP_config.h"

void STP_voidInit(void){
    // Enable clock 
    #if SERIAL_PORT == 0
        RCC_voidEnableClock(t_APB2, APB2ENR_IOPAEN);
    #elif SERIAL_PORT == 1
        RCC_voidEnableClock(t_APB2, APB2ENR_IOPBEN);
    #elif SERIAL_PORT == 2
        RCC_voidEnableClock(t_APB2, APB2ENR_IOPCEN); 
    #endif

    GPIO_voidInitPortPinDirection(SERIAL_PORT ,  SERIAL_DATA_PIN , OUTPUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPortPinDirection(SERIAL_PORT ,  SERIAL_SHIFT_CLOCK , OUTPUT_PUSH_PULL_2MHZ);
    GPIO_voidInitPortPinDirection(SERIAL_PORT ,  SERIAL_STORAGE_CLOCK , OUTPUT_PUSH_PULL_2MHZ);

    STK_voidInit();
}

void STP_voidSendSync(u8 cpy_data){
    s8 local_counter ;
    u8 local_bit;
    for(local_counter = 7 ; local_counter >=0 ;local_counter-- ){
        // Send bit by bit starting from MSB 
        local_bit = GET_BIT (cpy_data , local_counter);
        GPIO_voidSetPortPinValue(SERIAL_PORT , SERIAL_DATA_PIN , local_bit);

        // Create a pulse 
        GPIO_voidSetPortPinValue (SERIAL_PORT , SERIAL_SHIFT_CLOCK , 1);
        STK_voidSetBusyWait(1);
        GPIO_voidSetPortPinValue (SERIAL_PORT , SERIAL_SHIFT_CLOCK , 0);
        STK_voidSetBusyWait(1);
    }   

    // Create a pulse 
    GPIO_voidSetPortPinValue (SERIAL_PORT , SERIAL_STORAGE_CLOCK , 1);
    STK_voidSetBusyWait(1);
    GPIO_voidSetPortPinValue (SERIAL_PORT , SERIAL_STORAGE_CLOCK , 0);
    STK_voidSetBusyWait(1);

}