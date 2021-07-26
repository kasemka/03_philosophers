#include "philo.h"

// curremt time in microseconds
unsigned long long	cur_time_mcs(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec*1000000 + cur_time.tv_usec);
}

// retuns difference of current time and last eat time, milliseconds
unsigned long long	time_diff(t_philo *philo)
{
	struct timeval			cur_time;
	unsigned long long		diff;

	gettimeofday(&cur_time, NULL);
	diff = ((cur_time.tv_sec*1000000 + cur_time.tv_usec) - philo->hold->start_time) / 1000;
	return (diff);
} 

// usleep for goal_time - current_time in microseconds
void ft_usleep(unsigned long long time)
{
	unsigned long long	goal_time;

	goal_time = cur_time_mcs() + time;
	while (cur_time_mcs() < goal_time)
		usleep(1);
}