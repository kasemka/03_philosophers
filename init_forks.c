#include "philo.h"

void	clear_mutex_forks(t_hold *hold, int i)
{
	if (i >= 0)
	{
		while (i >= 0)
		{
			pthread_mutex_destroy(&hold->forks[i]);
			i--;
		}
	}
	free(hold->forks);
}

int	init_forks(t_hold *hold)
{
	pthread_mutex_t		*forks_arr;
	int					i;

	i = 0;
	forks_arr = malloc(sizeof(pthread_mutex_t) * hold->forks_n);
	if (forks_arr == NULL)
		return (malloc_fail());
	while (i < hold->forks_n)
	{
		if (pthread_mutex_init(&forks_arr[i], NULL) != 0)
		{
			clear_mutex_forks(hold, i - 1);
			return (1);
		}
		i++;
	}
	hold->forks = forks_arr;
	return (0);
}
