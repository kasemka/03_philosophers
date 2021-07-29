#include "philo.h"

void	msg(t_philo *philo, char c)
{
	pthread_mutex_lock(philo->msg);
	printf("\033[0;32m");
	if (c == 'l')
		printf("%llu philo %i has taken a left fork\n", time_diff(philo), \
		philo->name);
	else if (c == 'r')
		printf("%llu philo %i has taken a right fork\n", time_diff(philo), \
		philo->name);
	else if (c == 'e')
		printf("%llu philo %i is eating\n", time_diff(philo), philo->name);
	else if (c == 't')
		printf("%llu philo %i is thinking\n", time_diff(philo), philo->name);
	else if (c == 's')
		printf("%llu philo %i is sleeping\n", time_diff(philo), philo->name);
	else if (c == 'd')
	{
		printf("%llu philo %i died\n", time_diff(philo), philo->name);
		return ;
	}
	pthread_mutex_unlock(philo->msg);
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

void	start_time(t_hold *hold)
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

void	*catch_starving(void *a_hold)
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
		{
			i = 0;
			ft_usleep(50);
		}
		ft_usleep(50);
	}
	return (0);
}

int	start_process(t_hold *hold)
{
	int	i;

	i = 0;
	pthread_mutex_init(&hold->msg, NULL);
	start_time(hold);
	pthread_create(&hold->starving, NULL, catch_starving, hold);
	while (i < hold->philos_n)
	{
		pthread_create(&hold->philos[i].t, NULL, living, &hold->philos[i]);
		i++;
		ft_usleep(100);
	}
	i = 1;

	return (0);
}

void	end_threads(t_hold *hold)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	pthread_join(hold->starving, NULL);
	while (i < hold->philos_n)
	{
		pthread_detach(hold->philos[i].t);
		i++;
	}
	pthread_mutex_destroy(&hold->msg);
	while (j < hold->forks_n)
	{
		pthread_mutex_destroy(&hold->forks[j]);
		j++;
	}
	// free(hold->philos); 
	// free(forks);
}

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
	printf("hello world!\n");
	return (0);
}
