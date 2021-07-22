#ifndef PHILO_H
#define PHILO_H
 
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h> 
# include <string.h>
# include <sys/time.h>

typedef struct	s_hold t_hold;

typedef struct s_philo
{
	int					name;
	int					last_eat;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	pthread_mutex_t		*msg;
	pthread_t			t;
	t_hold				*main_hold;
}	t_philo;

typedef struct	s_hold
{
	int					philos_n;
	int					forks_n;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					eat_num;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		msg;
}	t_hold;



int	ft_atoi(const char *str);
int	init_struct(int argc, char **argv, t_hold *hold);
int	init_philos(t_hold *hold);
int	init_forks(t_hold *hold);
int	cur_time_ms(void);
int	malloc_fail(void);

#endif
