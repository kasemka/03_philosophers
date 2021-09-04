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

	i = 0;
	while (i < len)
	{
		if (forks_pid[i] != 0)
			kill(forks_pid[i], SIGKILL);
		i++;
	}
	exit (0);
}

void	end_processes(t_hold *hold, int *forks_pid)
{
	int	i;
	int	pid_with_exit;
	int	status;

	i = 0;
	while (i < hold->philos_n)
	{
		pid_with_exit = waitpid(0, &status, 0);
		if (status == 0)
			kill_all(forks_pid, hold->philos_n);
		else if (status == 1)
			remove_pid_arr(forks_pid, pid_with_exit, hold->philos_n);
		i++;
	}
	free(forks_pid);
}
