#ifndef RTOS_PRIVATE_H
#define RTOS_PRIVATE_H


typedef struct
{

	u16 Priodicity;
	void (*ptr)(void);
	u8 FirstDelay;
	u8 State;

}Task_t;




static void Scheduler(void);












#endif
