#include "philo.h"

void	*eating(void* a_philo)
{
	t_philo		*philo_thread;

	philo_thread = (t_philo	*)a_philo;
	pthread_mutex_lock(philo_thread->msg);
	pthread_mutex_lock(philo_thread->fork_left);
	// philo_thread->last_eat = cur_time_ms();
	printf("\033[0;32m");
	printf("%i philo %i has taken a fork\n", cur_time_ms(), philo_thread->name);
	pthread_mutex_lock(philo_thread->fork_right);
	printf("%i philo %i has taken a fork\n", cur_time_ms(), philo_thread->name);
	printf("%i philo %i is eating\n", cur_time_ms(), philo_thread->name);
	pthread_mutex_unlock(philo_thread->msg);
	usleep(200*1000); // correct and take from time_eat microsec to ms
	pthread_mutex_unlock(philo_thread->fork_left);
	pthread_mutex_unlock(philo_thread->fork_right);


	return 0;
}

int	start(t_hold *hold)
{
	int	i;

	i = 0;
	printf("phil num: %i\n", hold->philos_n);
	pthread_mutex_init(&hold->msg, NULL);
	printf("why? 32\n");
	while (i < hold->philos_n)
	{	
		pthread_create(&hold->philos[i].t, NULL, eating, &hold->philos[i]);
		// if (pthread_create(&hold->philos[i].t, NULL, eating, (void *)hold->philos) != 0)
		// 	return (1);
		// else
		// 	printf("strange?\n");
		usleep(10);
		i++;
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
	// int i = 0;
	// while (i < hold.philos_n)
	// {
	// 	printf("philos %i left: %i right: %i\n", hold.philos[i].name, hold.philos[i].left_hand, hold.philos[i].right_hand);
	// 	i++;
	// }
	if (start(&hold) == 1)
		return (1);
	printf("hello world!\n");
	return (0);
	// forks = philosophers num
	// dies if  = start_eating - current time > time_to_die in milliseconds
	// time_to_eat = the time it takes for a philosopher to eat
	// time_to_sleep = time spent for sleep
	// number_of_times_each_philosopher_must_eat: argument is optional, 
		//if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’
		//the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
	// You can’t have more than 10 ms between the death and when it will print its death

}
