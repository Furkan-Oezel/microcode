#include <stdint.h>
#include <TM4C123.h>

/**
 * @brief calculate easy sum and multiply with 2
 *        
 * @param first operand
 * @param second operand
 * @param third operand
 * @param fourth operand
 * 
 * @return calculation
 */
uint32_t calc_sum_x2(uint32_t a, uint32_t b, uint32_t c, uint32_t d);

int main()
{
	uint32_t A = 0;
	uint32_t B = 1;
	uint32_t C = 2;
	uint32_t D = 3;

	uint32_t ret_value;

	ret_value = calc_sum_x2(A, B, C, D);

	while(1)
	{

	}
}
