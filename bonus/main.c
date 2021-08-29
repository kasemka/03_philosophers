#include "philo_bonus.h"

void death_control(void *a_hold)
{
	t_hold 		*hold;
	int 		i;
	unsigned long long	time_diff;

	i = 0;
	hold = (t_hold *)a_hold;
	while (1)
	{
		if (cur_time_mcs() - hold->last_eat > hold->time_die ||  \
		hold->eat_num == hold->eat_num_min)

	}

}

void living(t_hold *hold, int name)
{
	pthread_t death;

	hold->name = name;
//	printf("name %i\n", name);
	sem_wait(hold->forks_sem);
	pthread_create(&death, NULL, (void *)death_control(), hold);
	printf("philo %i took a fork 1\n", name);
	sem_wait(hold->forks_sem);
	printf("philo %i took a fork 2\n", name);
	hold->eat_num++;
	hold->last_eat = cur_time_mcs();
	printf("philo %i is eating\n", name);
	ft_usleep(hold->time_eat);
	sem_post(hold->forks_sem);
	sem_post(hold->forks_sem);
	printf("philo %i is sleeping\n", name);
	ft_usleep(hold->time_sleep);
	printf("philo %i is thinking\n", name);
}

int	main(int argc, char **argv)
{
	t_hold	hold;
	int		i;
	pid_t	pid;

	i = 0;
	if (parse(argc, argv) == 1)
		return (1);
	if (init_struct(argc, argv, &hold) == 1)
		return (1);
	hold.name = 100;
	hold.forks_sem = sem_open("forks_sem", O_CREAT, 0777, hold.philos_n);
	hold.start_time = cur_time_mcs();
	while (i < hold.philos_n)
	{
		pid = fork();
		if (!pid)
		{
			hold.last_eat = cur_time_mcs();
			living(&hold, i + 1);
			break ;
		}
		ft_usleep(20);
		i++;
	}
	if (pid != 0)
		printf("philo name in main process = %i\n", hold.name);
//	sem_close(hold.forks_sem);
//	printf("hello world!\n");
	return (0);
}
