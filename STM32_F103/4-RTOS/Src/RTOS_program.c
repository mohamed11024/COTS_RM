#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RTOS_interface.h"
#include "RTOS_private.h"
#include "RTOS_config.h"

#include "STK_interface.h"

Task_t u8Priority[NUM_TASKS] = {NULL};
void RTOS_voidCreateTask(u8 Copy_u8ID,u16 Copy_u16Priodicity,void (*ptr)(void),u8 Copy_u8FirastDelay)
{

	u8Priority[Copy_u8ID].Priodicity = Copy_u16Priodicity;
	u8Priority[Copy_u8ID].ptr = ptr;
	u8Priority[Copy_u8ID].FirstDelay = Copy_u8FirastDelay;




}
void RTOS_voidStart(void)
{

	STK_voidInit();
	STK_voidSetIntervalPeriodic(1000,Scheduler);


}

static void Scheduler(void)
{
	for(u8 i=0;i<NUM_TASKS;i++)
	{
		if((u8Priority[i].ptr != NULL) && (u8Priority[i].State == READY)){
			if((u8Priority[i].FirstDelay)==0)
			{
				u8Priority[i].FirstDelay = u8Priority[i].Priodicity-1;
				u8Priority[i].ptr();
			}
			else
			{
				u8Priority[i].FirstDelay--;
			}
		}

	}
}
