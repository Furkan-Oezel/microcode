#include <stdint.h>
#include <TM4C123.h>

volatile uint32_t *const SYSCTL_RCGC = (uint32_t*) 0x400FE608;

typedef struct{
	volatile uint32_t useless_array[255];
    volatile uint32_t DATA;
	volatile uint32_t DIR;
	volatile uint32_t IS;
	volatile uint32_t IBE;
	volatile uint32_t IEV;
	volatile uint32_t IM;
	volatile uint32_t RIS;
	volatile uint32_t MIS;
	volatile uint32_t ICR;
	volatile uint32_t AFSEL;
	volatile uint32_t bigleap[55];
	volatile uint32_t DR2R;
	volatile uint32_t DR4R;
	volatile uint32_t DR8R;
	volatile uint32_t ODR;
	volatile uint32_t PUR;
	volatile uint32_t PDR;
	volatile uint32_t SLR;
	volatile uint32_t DEN;
}crazy_register_map;

crazy_register_map* const GPIO_F = (crazy_register_map*) 0x40025000;

void enable(int pin);
void init_as_output(int pin);
void turn_LED_ON(int pin);
void turn_LED_OFF(int pin);
void wait(int loops);

int main()
{
	int number_of_loops = 1500000;

	//activating system clk
	*SYSCTL_RCGC |= (1 << 5);	

    /* initiating RGB LEDs
	****************************************
	/ correesponding GPIO Pin for each LED /
	/ red:   PF1                           /
	/ blue:  PF2                           / 
	/ green: PF3                           /
	/**************************************/

	enable(1);
	enable(2);
	enable(3);

	init_as_output(1);	
	init_as_output(2);  
	init_as_output(3);  

	while (1)
	{
		turn_LED_ON(1);
		wait(number_of_loops);

		turn_LED_ON(3);
		wait(number_of_loops);

		turn_LED_OFF(1);
		wait(number_of_loops);

		turn_LED_ON(2);
		wait(number_of_loops);

		turn_LED_OFF(3);
		wait(number_of_loops);

		turn_LED_ON(1);
		wait(number_of_loops);

		turn_LED_OFF(2);		
	}
}

void enable(int pin){
	GPIO_F->DEN |= (1 << pin);
}

void init_as_output(int pin){
	GPIO_F->DIR |= (1 << pin);
}

void turn_LED_ON(int pin){
	GPIO_F->DATA |= (1 << pin);
}

void turn_LED_OFF(int pin){
	GPIO_F->DATA &= ~(1 << pin);
}

void wait(int loops){
	for(int n=0; n<loops; n++){}
}