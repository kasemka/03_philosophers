#include "philo.h"

int	init_forks(t_hold *hold)
{
	pthread_mutex_t		*forks_arr;
	int					i;

	i = 0;
	forks_arr = malloc(sizeof(pthread_mutex_t) * hold->forks_n);
	if (forks_arr == NULL)
		return (malloc_fail());
	while (i <  hold->forks_n)
	{
		pthread_mutex_init(&forks_arr[i], NULL);
		i++;
	}
	hold->forks = forks_arr;
	return (0);
}

