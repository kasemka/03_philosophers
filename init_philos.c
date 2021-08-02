#include "philo.h"

int	init_philos(t_hold *hold)
{
	int		i;

	i = 0;
	hold->philos = (t_philo *)malloc(sizeof(t_philo) * hold->philos_n);
	if (hold->philos == NULL)
	{
		clear_mutex_forks(hold, hold->forks_n);
		return (malloc_fail());
	}
	while (i < hold->philos_n)
	{
		hold->philos[i].name = i + 1;
		hold->philos[i].fork_left = &hold->forks[i];
		hold->philos[i].fork_right = &hold->forks[i + 1];
		hold->philos[i].hold = hold;
		hold->philos[i].eat_num = 0;
		i++;
	}
	hold->philos[hold->philos_n - 1].fork_right = &hold->forks[0];
	return (0);
}
