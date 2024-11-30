#ifndef LED_MATRIX_PRIVATE_H
#define LED_MATRIX_PRIVATE_H



#define LED_PORTA                0
#define LED_PORTB                1


#define GPIOA0                    0
#define GPIOA1                    1
#define GPIOA2                    2
#define GPIOA3                    3
#define GPIOA4                    4
#define GPIOA5                    5
#define GPIOA6                    6
#define GPIOA7                    7


#define GPIOB0                    0
#define GPIOB1                    1
#define GPIOB5                    5
#define GPIOB6                    6
#define GPIOB7                    7
#define GPIOB8                    8
#define GPIOB9                    9
#define GPIOB10                   10


static void LED_MATRIX_voidDisableAllColoumns(void);

static void LED_MATRIX_voidSetRowValues(uint8_t Copy_u8Value);











#endif
