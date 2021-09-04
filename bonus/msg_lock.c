#include "philo.h"

void	msg(t_philo *philo, char c)
{
	unsigned long long	time_diff;

	pthread_mutex_lock(&philo->hold->msg);
	time_diff = (cur_time_mcs() - philo->hold->start_time) / 1000;
	if (c == 'l' && philo->hold->stop_sim == 0)
		printf("%llu philo %i has taken a left fork\n", time_diff, philo->name);
	else if (c == 'r' && philo->hold->stop_sim == 0)
		printf("%llu philo %i has taken a right fork\n", time_diff, philo->name);
	else if (c == 'e' && philo->hold->stop_sim == 0)
		printf("%llu philo %i is eating\n", time_diff, philo->name);
	else if (c == 't' && philo->hold->stop_sim == 0)
		printf("%llu philo %i is thinking\n", time_diff, philo->name);
	else if (c == 's' && philo->hold->stop_sim == 0)
		printf("%llu philo %i is sleeping\n", time_diff, philo->name);
	pthread_mutex_unlock(&philo->hold->msg);
}
