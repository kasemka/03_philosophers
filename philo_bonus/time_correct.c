#include "philo_bonus.h"

// curremt time in microseconds
unsigned long long	cur_time_mcs(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec * 1000000 + cur_time.tv_usec);
}

// usleep for goal_time - current_time in microseconds
void	ft_usleep(unsigned long long time)
{
	unsigned long long	goal_time;

	goal_time = cur_time_mcs() + time;
	while (cur_time_mcs() < goal_time)
		usleep(50);
}
