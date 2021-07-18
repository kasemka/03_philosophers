#include "philo.h"

int	check_input(t_hold hold, int argc)
{
	if (hold.philos_n <= 0 || hold.time_die <= 0 || hold.time_eat <= 0 \
	|| hold.time_sleep == 0)
		return (1);
	if (argc == 6 && hold.eat_num <= 0)
		return (1);
	return (0);
}

int	init_philosophers(t_hold hold)
{
	int	i;

	i = 0;
	hold.philos = (t_philo *)malloc(sizeof(t_philo) * hold.philos_n);
	if (hold.philos == NULL)
		return (malloc_fail());
	hold.philos[0].name = 1;
	while (i < hold.philos_n)
	{
		hold.philos[i].name = i;
		// pthread_create(hold.philos[i].t, NULL))
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_hold		hold;

	if (argc < 5 || argc > 6)
		return (0);
	hold.philos_n = ft_atoi(argv[1]);
	hold.time_die = ft_atoi(argv[2]);
	hold.time_eat = ft_atoi(argv[3]);
	hold.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		hold.eat_num = ft_atoi(argv[5]);
	if (check_input(hold, argc) == 1)
		return (1);
	if (init_philosophers(hold) == 1)
		return (1);
	printf("hello world!\n");
	return (0);
}
