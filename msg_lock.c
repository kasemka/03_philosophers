#include "philo.h"

void	msg(t_philo *philo, char c)
{
	pthread_mutex_lock(philo->msg);
	if (philo->hold->is_dead == 0)
	{
		ft_putnbr_fd(time_diff(philo), 1);
		write(1, " philo ", 7);
		ft_putnbr_fd(philo->name, 1);
		if (c == 'l')
			write(1, " has taken a left fork\n", 23);
		else if (c == 'r')
			write(1, " has taken a right fork\n", 24);
		else if (c == 'e')
			write(1, " is eating\n", 11);
		else if (c == 't')
			write(1, " is thinking\n", 13);
		else if (c == 's')
			write(1, " is sleeping\n", 13);
		else if (c == 'd')
		{
			write(1, " died\n", 6);
			return ;
		}
		pthread_mutex_unlock(philo->msg);
	}
}
