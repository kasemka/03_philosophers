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
	int					i;

	i = 0;
	hold->forks = malloc(sizeof(pthread_mutex_t) * hold->forks_n);
	if (hold->forks == NULL)
		return (malloc_fail());
	while (i < hold->forks_n)
	{
		if (pthread_mutex_init(&hold->forks[i], NULL) != 0)
		{
			clear_mutex_forks(hold, i - 1);
			return (1);
		}
		i++;
	}
	return (0);
}
