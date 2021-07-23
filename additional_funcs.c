#include "philo.h"

unsigned long long	cur_time_ms(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec*1000 + cur_time.tv_usec/1000);
}