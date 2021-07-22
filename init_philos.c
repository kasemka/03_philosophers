#include "philo.h"

void	*print_name(void *i)
{
	int index = *(int *)i;
	printf("hello philo %d\n", index);
	return (NULL);
}

int	init_philos(t_hold *hold)
{
	int		i;
	int		name; 

	i = 0;
	name = 1;
	hold->philos = (t_philo *)malloc(sizeof(t_philo) * hold->philos_n);
	if (hold->philos == NULL)
		return (malloc_fail());
	while (i < hold->philos_n)
	{
		hold->philos[i].name = name;
		hold->philos[i].fork_left = &hold->forks[i];
		hold->philos[i].fork_right = &hold->forks[i + 1];
		hold->philos[i].msg = &hold->msg;
		i++;
		name++;
	}
	hold->philos[hold->philos_n - 1].fork_right = &hold->forks[0];
	return (0);
}
