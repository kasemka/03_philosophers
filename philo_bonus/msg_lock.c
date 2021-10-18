#include "philo_bonus.h"

void	msg(t_hold *hold, char c)
{
	unsigned long long	time_diff;

	sem_wait(hold->print);
	time_diff = (cur_time_mcs() - hold->start_time) / 1000;
	if (c == 'f')
		printf("%llu philo %i has taken first fork\n", time_diff, hold->name);
	else if (c == 'a')
		printf("%llu philo %i has taken second fork\n", time_diff, hold->name);
	else if (c == 'e')
		printf("%llu philo %i is eating\n", time_diff, hold->name);
	else if (c == 't')
		printf("%llu philo %i is thinking\n", time_diff, hold->name);
	else if (c == 's')
		printf("%llu philo %i is sleeping\n", time_diff, hold->name);
	sem_post(hold->print);
}
