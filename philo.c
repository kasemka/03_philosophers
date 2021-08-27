#include "philo.h"

int	main(int argc, char **argv)
{
	t_hold		hold;

	if (parse(argc, argv) == 1)
		return (1);
	if (init_struct(argc, argv, &hold) == 1)
		return (1);
	if (init_forks(&hold) == 1)
		return (1);
	if (init_philos(&hold) == 1)
		return (1);
	if (start_process(&hold) == 1)
		return (1);
	return (end_threads(&hold));
}
