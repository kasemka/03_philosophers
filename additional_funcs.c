#include "philo.h"

unsigned long long	cur_time_ms(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec*1000 + cur_time.tv_usec/1000);
}

unsigned long long	cur_time_mcs(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec*1000000 + cur_time.tv_usec);
}

unsigned long long	time_diff(t_philo *philo)
{
	struct timeval			cur_time;
	unsigned long long		diff;

	gettimeofday(&cur_time, NULL);
	diff = ((cur_time.tv_sec*1000000 + cur_time.tv_usec) - philo->hold->start_time) / 1000;
	return (diff);
} //remove