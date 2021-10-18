#include "philo_bonus.h"

int	remove_pid_arr(int *arr, int num, int len)
{
	int	i;

	i = 0;
	while (i < len && arr[i] != num)
		i++;
	if (i == len)
		return (1);
	arr[i] = 0;
	return (0);
}

void	kill_all(int *forks_pid, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (forks_pid[i] != 0)
			kill(forks_pid[i], SIGKILL);
	}
}

void	check_fed_up(void *a_hold)
{
	t_hold				*hold;
	int					n;

	n = 0;
	hold = (t_hold *)a_hold;
	while (++n <= hold->philos_n)
		sem_wait(hold->well_fed);
	kill_all(hold->forks_pid, hold->philos_n);
}

// status = 9: child process was killed by parent;
// status = 0: child end with exit(0);
void	end_processes(t_hold *hold)
{
	int			pid_with_exit;
	int			status;
	pthread_t	fed;

	pthread_create(&fed, NULL, (void *)check_fed_up, hold);
	pthread_detach(fed);
	pid_with_exit = waitpid(0, &status, 0);
	if (status == 0)
		kill_all(hold->forks_pid, hold->philos_n);
}
