#include "philo_bonus.h"

void	monitor(void *a_hold)
{
	t_hold				*hold;
	unsigned long long	time_diff;

	hold = (t_hold *)a_hold;
	while (1)
	{
		if (cur_time_mcs() - hold->last_eat > hold->time_die)
		{
			hold->stop_sim = 1;
			sem_wait(hold->death);
			time_diff = (cur_time_mcs() - hold->start_time) / 1000;
			printf("%llu philo %d died\n", time_diff, hold->name);
			sem_wait(hold->print);
			exit (0);
		}
		if (hold->eat_num == hold->eat_num_min)
		{
			sem_post(hold->forks_sem);
			sem_post(hold->forks_sem);
			exit (1);
		}
		ft_usleep(50, hold->stop_sim);
	}
}

void	living(t_hold *hold, int name)
{
	pthread_t	death;

	hold->name = name;
	pthread_create(&death, NULL, (void *)monitor, hold);
	pthread_detach(death);
	while (hold->stop_sim == 0)
	{
		sem_wait(hold->forks_sem);
		msg(hold, 'f');
		ft_usleep(10, hold->stop_sim);
		sem_wait(hold->forks_sem);
		msg(hold, 'a');
		hold->eat_num++;
		msg(hold, 'e');
		hold->last_eat = cur_time_mcs();
		ft_usleep(hold->time_eat, hold->stop_sim);
		sem_post(hold->forks_sem);
		sem_post(hold->forks_sem);
		msg(hold, 's');
		ft_usleep(hold->time_sleep, hold->stop_sim);
		msg(hold, 't');
	}
}

void	start_processes(t_hold *hold, int *forks_pid, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < hold->philos_n)
	{
		*pid = fork();
		if (*pid == 0)
		{
			hold->last_eat = cur_time_mcs();
			free(forks_pid);
			living(hold, i + 1);
			break ;
		}
		else
			forks_pid[i] = *pid;
		ft_usleep(10, hold->stop_sim);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_hold	hold;
	pid_t	pid;
	int		*forks_pid;

	if (parse(argc, argv) | init_struct(argc, argv, &hold))
		return (1);
	forks_pid = malloc(sizeof(int) * hold.philos_n);
	if (forks_pid == NULL)
		return (malloc_fail());
	sem_unlink("forks_sem");
	sem_unlink("death");
	sem_unlink("print");
	hold.forks_sem = sem_open("forks_sem", O_CREAT, 0777, hold.philos_n);
	hold.death = sem_open("death", O_CREAT, 0777, 1);
	hold.print = sem_open("print", O_CREAT, 0777, 1);
	hold.start_time = cur_time_mcs();
	start_processes(&hold, forks_pid, &pid);
	if (pid != 0)
		end_processes(&hold, forks_pid);
	return (0);
}
