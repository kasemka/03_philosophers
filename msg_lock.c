#include "philo.h"

void	msg(t_philo *philo, char c)
{
	unsigned long long	time_diff;

	pthread_mutex_lock(&philo->hold->msg);
	time_diff = (cur_time_mcs() - philo->hold->start_time) / 1000;
	if (c == 'l')
		printf("%llu philo %i has taken a left fork\n", time_diff, philo->name);
	else if (c == 'r')
		printf("%llu philo %i has taken a right fork\n", time_diff, philo->name);
	else if (c == 'e')
		printf("%llu philo %i is eating\n", time_diff, philo->name);
	else if (c == 't')
		printf("%llu philo %i is thinking\n", time_diff, philo->name);
	else if (c == 's')
		printf("%llu philo %i is sleeping\n", time_diff, philo->name);
	pthread_mutex_unlock(&philo->hold->msg);
}
