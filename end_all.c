#include "philo.h"

int	end_threads(t_hold *hold, int flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (flag != 1)
	{
		if (flag == 0)
			pthread_join(hold->starving, NULL);
		while (i < hold->philos_n)
		{
			pthread_detach(hold->philos[i].t);
			i++;
		}
		pthread_mutex_destroy(&hold->msg);
	}
	while (j < hold->forks_n)
	{
		pthread_mutex_destroy(&hold->forks[j]);
		j++;
	}
	free(hold->philos);
	free(hold->forks);
	return (0);
}
