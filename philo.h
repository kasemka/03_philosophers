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
	unsigned long long	last_eat;
	int					eat_num;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	pthread_mutex_t		*msg;
	pthread_mutex_t		*died;
	pthread_t			t;
	t_hold				*hold;
}	t_philo;

typedef struct	s_hold
{
	int					philos_n;
	int					forks_n;
	unsigned long long	time_die;
	unsigned long long	time_eat;
	int					time_sleep;
	int					eat_num;
	int					philos_num_eat_min;
	unsigned long long	start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		msg;
	pthread_mutex_t		died;
	pthread_t			starving;
	int					is_dead;
}	t_hold;



int					ft_atoi(const char *str);
int					init_struct(int argc, char **argv, t_hold *hold);
int					init_philos(t_hold *hold);
int					init_forks(t_hold *hold);
unsigned long long	time_diff(t_philo *philo); 
unsigned long long	cur_time_mcs(void);
int					malloc_fail(void);
void				ft_usleep(unsigned long long time);

#endif
