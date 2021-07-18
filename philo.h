#ifndef PHILO_H
#define PHILO_H
 
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h> 
# include <string.h>

typedef struct s_philo
{
	int				name;
	int				last_eat;
	pthread_t		t;
	// int		left_hand mutex;
	// int		right_hand mutex;
}	t_philo;

typedef struct	s_hold
{
	int			philos_n;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			eat_num;
	t_philo		*philos;
}	t_hold;

int	ft_atoi(const char *str);

int	malloc_fail(void);

#endif
