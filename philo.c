#include "philo.h"

void	msg(t_philo *philo, char c)
{
	pthread_mutex_lock(philo->msg);
	if (philo->hold->is_dead == 0)
	{
		printf("\033[0;32m");
		if (c == 'l')
			printf("%llu philo %i has taken a left fork\n", time_diff(philo), philo->name);
		else if (c == 'r')
			printf("%llu philo %i has taken a right fork\n", time_diff(philo), philo->name);
		else if (c == 'e')
			printf("%llu philo %i is eating\n", time_diff(philo), philo->name);
		else if (c == 't')
			printf("%llu philo %i is thinking\n", time_diff(philo), philo->name);
		else if (c == 's')	
			printf("%llu philo %i is sleeping\n", time_diff(philo), philo->name);
		pthread_mutex_unlock(philo->msg);
	}
}

// void	eating(t_philo philo)
// {

// }

void	*living(void* a_philo)
{
	t_philo		*philo;

	philo = (t_philo	*)a_philo;
	if (philo->name % 2 == 0)
		usleep(50);
	while (philo->hold->is_dead == 0)
	{
		if (cur_time_mcs() - philo->last_eat > philo->hold->time_die * 1000)
		{
			philo->hold->is_dead = 1;
			printf("%llu philo %i died\n", time_diff(philo), philo->name);
			return 0;
		}
		pthread_mutex_lock(philo->fork_left);
		msg(philo, 'l');
		pthread_mutex_lock(philo->fork_right);
		msg(philo, 'r');
		msg(philo, 'e');
		philo->last_eat = cur_time_mcs();
		usleep(philo->hold->time_eat * 1000);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		msg(philo, 's');
		usleep(philo->hold->time_sleep * 1000);
		msg(philo, 't');
	}
	return 0;
}


void	start_time(t_hold *hold)
{
	int	i;

	i = 0;
	hold->start_time = cur_time_mcs();
	while (i < hold->philos_n)
	{
		hold->philos[i].last_eat = cur_time_mcs(); // microsec
		i++;
		usleep(50);
	}
}

int	start_process(t_hold *hold)
{
	int	i;

	i = 0;
	printf("phil num: %i\n", hold->philos_n);
	pthread_mutex_init(&hold->msg, NULL);
	pthread_mutex_init(&hold->died, NULL);
	start_time(hold);
	while (i < hold->philos_n)
	{
		pthread_create(&hold->philos[i].t, NULL, living, &hold->philos[i]);
		i++;
		usleep(50);
	}
	pthread_exit(NULL);
	return (0);
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
	// for (int i = 0; i < hold.philos_n; i++)
	// 	printf("fork %i - %p \n", i, &hold.forks[i]);
	// printf("\n");
	// for (int i = 0; i < hold.philos_n; i++)
	// {
	// 	printf("phil %i left %p \n", hold.philos[i].name, hold.philos[i].fork_left);
	// 	printf("phil %i right %p \n", hold.philos[i].name, hold.philos[i].fork_right);
	// }
	if (start_process(&hold) == 1)
		return (1);
	printf("hello world!\n");
	return (0);
	// dies if  = start_eating - current time > time_to_die in milliseconds
	// time_to_eat = the time it takes for a philosopher to eat
	// time_to_sleep = time spent for sleep
	// number_of_times_each_philosopher_must_eat: argument is optional, 
	// You can’t have more than 10 ms between the death and when it will print its death

}



// int print_msg(char c)
// {
// 	if(philo->hold->is_dead == 0)
// 	{
// 		pthread_mutex_lock(philo->msg);
// 	if(c == 's')
// 		printf("sleep");
// 	if(c == 'l')

// 	pthread_mutex_unlock(philo->msg);
// 	}
	
// }