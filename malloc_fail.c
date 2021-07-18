#include "philo.h"

int	malloc_fail(void)
{
	write(1, "malloc fail\n", 12);
	return (1);
}
