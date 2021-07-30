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
		philo->hold->philos_num_eat_min++;
	ft_usleep(philo->hold->time_eat);
}

void	*living(void *a_philo)
{
	t_philo		*philo;

	philo = (t_philo *)a_philo;
	while (1)
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
		ft_usleep(50);
	}
	return (0);
}

void	*catch_dead(void *a_hold)
{
	t_hold		*hold;
	int			i;

	i = 0;
	hold = (t_hold *)a_hold;
	while (i < hold->philos_n && hold->philos_num_eat_min != hold->philos_n)
	{
		if (cur_time_mcs() - hold->philos[i].last_eat > hold->time_die)
		{
			msg(&hold->philos[i], 'd');
			hold->is_dead = 1;
			break ;
		}
		i++;
		if (i == hold->philos_n)
			i = 0;
		ft_usleep(110);
	}
	return (0);
}

int	start_process(t_hold *hd)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&hd->msg, NULL) != 0)
	{
		end_threads(hd, 1);
		return (1);
	}
	start_time_record(hd);
	while (++i < hd->philos_n)
	{
		if (pthread_create(&hd->philos[i].t, NULL, living, &hd->philos[i]) != 0)
		{
			hd->philos_n = i;
			end_threads(hd, 2);
			return (1);
		}
		ft_usleep(100);
	}
	if (pthread_create(&hd->starving, NULL, catch_dead, hd) != 0)
	{
		end_threads(hd, 2);
		return (1);
	}
	return (0);
}
