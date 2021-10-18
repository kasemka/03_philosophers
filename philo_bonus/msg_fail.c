#include "philo_bonus.h"

int	invalid_input(void)
{
	write(1, "invalid input\n", 14);
	return (1);
}

int	malloc_fail(void)
{
	write(1, "malloc fail\n", 12);
	return (1);
}
