#include "philo.h"

void	msg(t_philo *philo, char c)
{
	pthread_mutex_lock(philo->msg);
	printf("\033[0;32m");
	if (c == 'l')
		printf("%llu philo %i has taken a left fork\n", time_diff(philo), \
		philo->name);
	else if (c == 'r')
		printf("%llu philo %i has taken a right fork\n", time_diff(philo), \
		philo->name);
	else if (c == 'e')
		printf("%llu philo %i is eating\n", time_diff(philo), philo->name);
	else if (c == 't')
		printf("%llu philo %i is thinking\n", time_diff(philo), philo->name);
	else if (c == 's')
		printf("%llu philo %i is sleeping\n", time_diff(philo), philo->name);
	else if (c == 'd')
	{
		printf("%llu philo %i died\n", time_diff(philo), philo->name);
		return ;
	}
	pthread_mutex_unlock(philo->msg);
}
