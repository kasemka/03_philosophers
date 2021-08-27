#include "philo.h"

int	end_threads(t_hold *hold)
{
	int	j;

	j = 0;
	if (pthread_join(hold->starving, NULL) != 0)
		return (pthread_join_fail());
	while (j < hold->philos_n)
	{
		if (pthread_join(hold->philos[j].t, NULL) != 0)
			return (pthread_join_fail());
		j++;
	}
	if (hold->philos_n == 1)
		pthread_mutex_unlock(&hold->forks[0]);
	j = 0;
	while (j < hold->forks_n)
	{
		if (pthread_mutex_destroy(&hold->forks[j]) != 0)
			return (mutex_destroy_fail());
		j++;
	}
	if (pthread_mutex_destroy(&hold->msg) != 0)
		return (mutex_destroy_fail());
	free(hold->philos);
	free(hold->forks);
	return (0);
}
