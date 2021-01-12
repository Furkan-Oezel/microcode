#ifndef INIT_H
#define INIT_H
#include <stdint.h>

void init_gpiof(void);

uint32_t calculated_load(uint8_t t_duration);
void init_systick(uint8_t time_duration);

void init_interrupt(uint8_t pin, uint8_t sense);

void turn_on(uint8_t pin);
void turn_off(uint8_t pin);
void toggle(uint8_t pin);

#endif