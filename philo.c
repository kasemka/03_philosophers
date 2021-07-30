#include "philo.h"


int	main(int argc, char **argv)
{
	t_hold		hold;

	if (argc < 5 || argc > 6)
		return (0);
	if (init_struct(argc, argv, &hold) == 1)
		return (1);
	if (init_forks(&hold) == 1)
		return (1);
	if (init_philos(&hold) == 1)
		return (1);
	if (start_process(&hold) == 1)
		return (1);
	end_threads(&hold);
	return (0);
}
