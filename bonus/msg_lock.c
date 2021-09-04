#include "philo_bonus.h"

void	msg(t_hold *hold, char c)
{
	unsigned long long	time_diff;

	sem_wait(hold->print);
	time_diff = (cur_time_mcs() - hold->start_time) / 1000;
	if (c == 'f' && hold->stop_sim == 0)
		printf("%llu philo %i has taken first fork\n", time_diff, hold->name);
	else if (c == 'a' && hold->stop_sim == 0)
		printf("%llu philo %i has taken second fork\n", time_diff, hold->name);
	else if (c == 'e' && hold->stop_sim == 0)
		printf("%llu philo %i is eating\n", time_diff, hold->name);
	else if (c == 't' && hold->stop_sim == 0)
		printf("%llu philo %i is thinking\n", time_diff, hold->name);
	else if (c == 's' && hold->stop_sim == 0)
		printf("%llu philo %i is sleeping\n", time_diff, hold->name);
	sem_post(hold->print);
}
