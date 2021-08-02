#include "philo.h"

void	start_time_record(t_hold *hold)
{
	int	i;

	i = 0;
	hold->start_time = cur_time_mcs();
	while (i < hold->philos_n)
	{
		hold->philos[i].last_eat = cur_time_mcs();
		i++;
	}
}

void	eating(t_philo *philo)
{
	philo->last_eat = cur_time_mcs();
	msg(philo, 'e');
	philo->eat_num++;
	if (philo->eat_num == philo->hold->eat_num)
		philo->hold->min_eat++;
	ft_usleep(philo->hold->time_eat);
}

void	living(void *a_philo)
{
	t_philo		*philo;

	philo = (t_philo *)a_philo;
	while (philo->hold->is_dead == 0)
	{
		pthread_mutex_lock(philo->fork_left);
		msg(philo, 'l');
		if (philo->hold->philos_n == 1)
			break ;
		pthread_mutex_lock(philo->fork_right);
		msg(philo, 'r');
		eating(philo);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		msg(philo, 's');
		ft_usleep(philo->hold->time_sleep);
		msg(philo, 't');
	}
}

void	catch_dead(void *a_hold)
{
	t_hold				*hold;
	int					i;
	unsigned long long	time_diff;

	i = 0;
	hold = (t_hold *)a_hold;
	while (i < hold->philos_n && hold->min_eat != hold->philos_n && \
	hold->is_dead == 0)
	{
		if (cur_time_mcs() - hold->philos[i].last_eat >= hold->time_die)
		{
			hold->is_dead = 1;
			pthread_mutex_lock(&hold->msg);
			time_diff = (cur_time_mcs() - hold->start_time) / 1000;
			printf("%llu philo %i died\n", time_diff, hold->philos[i].name);
			break ;
		}
		i++;
		if (i == hold->philos_n)
			i = 0;
		ft_usleep(100);
	}
}

int	start_process(t_hold *hd)
{
	int	i;

	i = 0;
	start_time_record(hd);
	while (i < hd->philos_n)
	{
		if (pthread_create(&hd->philos[i].t, NULL, (void *)living, \
		&hd->philos[i]) != 0)
		{
			hd->philos_n = i;
			return (end_threads(hd, 2));
		}
		pthread_detach(hd->philos[i].t);
		i++;
		ft_usleep(10);
	}
	if (pthread_create(&hd->starving, NULL, (void *)catch_dead, hd) != 0)
		return (end_threads(hd, 2));
	return (0);
}
