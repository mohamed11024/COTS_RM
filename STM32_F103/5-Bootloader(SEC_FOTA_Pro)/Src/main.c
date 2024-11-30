/*
 * main.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Mo
 */

/*Include App Layer*/
#include "BTL_interface.h"


void main (void)
{
	/*Bootloader Init*/
	 ABTL_vidInit();

	 /*BootLoader Start*/
	 ABTL_vidStart();

} //END Main




