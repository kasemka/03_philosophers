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
	if (philo->name % 2 == 0)
		ft_usleep(philo->hold->time_eat);
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
			hold->is_dead = 1;
			msg(&hold->philos[i], 'd');
			break ;
		}
		i++;
		if (i == hold->philos_n)
			i = 0;
		ft_usleep(100);
	}
	return (0);
}

int	start_process(t_hold *hold)
{
	int	i;

	i = 0;
	pthread_mutex_init(&hold->msg, NULL);
	start_time_record(hold);
	
	while (i < hold->philos_n)
	{
		pthread_create(&hold->philos[i].t, NULL, living, &hold->philos[i]);	
		i++;
		ft_usleep(50);
	}
	pthread_create(&hold->starving, NULL, catch_dead, hold);
	i = 1;

	return (0);
}

