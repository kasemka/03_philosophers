#include "philo.h"

void	*living(void* a_philo)
{
	t_philo		*philo_thread;

	philo_thread = (t_philo	*)a_philo;
	printf("\033[0;32m");
	pthread_mutex_lock(philo_thread->msg);
	pthread_mutex_lock(philo_thread->fork_left);
	philo_thread->last_eat = cur_time_ms();
	printf("%llu philo %i has taken a fork\n", cur_time_ms(), philo_thread->name);
	pthread_mutex_lock(philo_thread->fork_right);
	printf("%llu philo %i has taken a fork\n", cur_time_ms(), philo_thread->name);
	printf("%llu philo %i is eating\n", cur_time_ms(), philo_thread->name);
	pthread_mutex_unlock(philo_thread->msg);
	usleep(philo_thread->main_hold->time_eat*1000); // correct and take from time_eat microsec to ms
	pthread_mutex_unlock(philo_thread->fork_left);
	pthread_mutex_unlock(philo_thread->fork_right);

	return 0;
}

int	start_process(t_hold *hold)
{
	int	i;

	i = 0;
	printf("phil num: %i\n", hold->philos_n);
	pthread_mutex_init(&hold->msg, NULL);
	hold->start_time = cur_time_ms();
	// printf("time eat %i\n", hold->time_eat);
	while (hold->is_dead == 0)
	{
		while (i < hold->philos_n)
		{
			if (i % 2 == 0)
				pthread_create(&hold->philos[i].t, NULL, living, &hold->philos[i]);
			if (i % 2 == 1)
				pthread_create(&hold->philos[i].t, NULL, living, &hold->philos[i]);
			usleep(40);
			i = i + 2;
			if (i >= hold->philos_n && i % 2 == 1)
				i = 0;
			else if (i >= hold->philos_n && i % 2 == 0)
				i = 1;
		}
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
	for (int i = 0; i < hold.philos_n; i++)
	{
		printf("phil %i left %p \n", hold.philos[i].name, hold.philos[i].fork_left);
		printf("phil %i right %p \n", hold.philos[i].name, hold.philos[i].fork_right);
	}
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
