#ifndef RTOS_INTERFACE_H
#define RTOS_INTERFACE_H




#define READY                      0
#define SUSPEND                    1
#define DELETE                     2




void RTOS_voidCreateTask(u8 Copy_u8ID,u16 Copy_u16Priodicity,void (*ptr)(void),u8 Copy_u8FirastDelay);
void RTOS_voidStart(void);











#endif
