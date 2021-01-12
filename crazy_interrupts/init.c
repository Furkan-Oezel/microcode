#include "TI/TM4C123.h"
#include "init.h"
#include "nicknames.h"

void init_gpiof(void)
{
    SYSCTL->RCGCGPIO |= (1 << GPIO_F);
    while(   !(SYSCTL->PRGPIO  &  (1 << GPIO_F))   )
    {
        // wait like a bitch if not ready
    }

    GPIOF->DIR |= (1 << RED);
    GPIOF->DIR |= (1 << GREEN);
    GPIOF->DIR |= (1 << BLUE);
    GPIOF->DIR &= ~(1 << LEFT_SW);

    GPIOF->LOCK = 0x4C4F434B;
    GPIOF->CR |= (1 << RIGHT_SW);
    GPIOF->DIR &= ~(1 << RIGHT_SW);

    GPIOF->AFSEL &= ~(1 << RED);
    GPIOF->AFSEL &= ~(1 << GREEN);
    GPIOF->AFSEL &= ~(1 << BLUE);
    GPIOF->AFSEL &= ~(1 << LEFT_SW);
    GPIOF->AFSEL &= ~(1 << RIGHT_SW);

    GPIOF->PUR |= (1 << LEFT_SW);
    GPIOF->PUR |= (1 << RIGHT_SW);

    GPIOF->DEN |= (1 << RED);
    GPIOF->DEN |= (1 << GREEN);
    GPIOF->DEN |= (1 << BLUE);
    GPIOF->DEN |= (1 << LEFT_SW);
    GPIOF->DEN |= (1 << RIGHT_SW);
}

/* =========================================================================================================== */
/* gewünschte Zeitdauer = (1 + Anzahl an Treppen) * Zeit die man für eine Treppe runtergehen braucht (1/f_clk) */
/* =========================================================================================================== */
uint32_t calculated_load(uint8_t t_duration)
{
    return t_duration * PSEUDO_CLK -1;
}

void init_systick(uint8_t time_duration)
{
    SysTick->CTRL = 0;              // narcosis before the operation begins...
    
    SysTick->LOAD = calculated_load(time_duration);

    SysTick->VAL = 0;

    SysTick->CTRL |= (1 << 2);      // Clock Source = System clock
    SysTick->CTRL |= (1 << 1);      // An interrupt is generated to the NVIC when SysTick counts to 0.
    SysTick->CTRL |= (1 << 0);      // and so it begins...
}

void init_interrupt(uint8_t pin, uint8_t sense)
{
    /* ================================================================== */
    /* To prevent false interrupts, the following steps should be taken   */
    /* when re-configuring GPIO edge and interrupt sense registers, part1 */
    /* ================================================================== */
    GPIOF->IM &= ~(1 << pin);       // masks port
    GPIOF->IS &= ~(1 << pin);       // resets to default
    GPIOF->IBE &= ~(1 << pin);      // resets to default
    /* ================================================================== */
    /*                          part1 finished                            */
    /* ================================================================== */

    if(sense == 0)
    GPIOF->IS &= ~(1 << pin);

    else
    GPIOF->IS |= (1 << pin);

    GPIOF->IBE &= ~(1 << pin);      // single edge
    GPIOF->IEV &= ~(1 << pin);      // fallig edge/low level
    GPIOF->IM |= (1 << pin);

    NVIC->ISER[0] |= (1 << 30);     // p. 104, GPIO Port F has Interrupt Number 30

    /* ================================================================== */
    /* To prevent false interrupts, the following steps should be taken   */
    /* when re-configuring GPIO edge and interrupt sense registers, part2 */
    /* ================================================================== */
    GPIOF->ICR &= ~(1 << pin);      // clears RIS Register
    GPIOF->IM |= (1 << pin);        // unmasks port => ready to go
    /* ================================================================== */
    /*                         part2 finished                             */
    /* ================================================================== */
}

void turn_on(uint8_t pin)
{
    GPIOF->DATA |= (1 << pin);
}

void turn_off(uint8_t pin)
{
    GPIOF->DATA &= ~(1 << pin);
}

void toggle(uint8_t pin)
{
    GPIOF->DATA ^= (1 << pin);
}