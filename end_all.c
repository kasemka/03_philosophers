#include "philo.h"

void	end_threads(t_hold *hold)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	pthread_join(hold->starving, NULL);
	while (i < hold->philos_n)
	{
		pthread_detach(hold->philos[i].t);
		i++;
	}
	pthread_mutex_destroy(&hold->msg);
	while (j < hold->forks_n)
	{
		pthread_mutex_destroy(&hold->forks[j]);
		j++;
	}
	// free(hold->philos); 
	// free(forks);
}