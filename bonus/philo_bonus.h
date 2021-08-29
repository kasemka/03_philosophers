#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

//# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
#include <semaphore.h>
# include <stdlib.h>
//# include <string.h>
# include <sys/time.h>

typedef struct s_hold
{
	int 				name;
	int					philos_n;
	unsigned long long	time_die;
	unsigned long long	time_eat;
	int					time_sleep;
	int					eat_num_min;
	int					eat_num;
	unsigned long long	last_eat;
	sem_t 				*forks_sem;
	unsigned long long	start_time;
//	t_philo				*philos;
//	pthread_mutex_t		*forks;
//	pthread_mutex_t		msg;
//	pthread_t			starving;
//	int					stop_sim;
}	t_hold;

int					parse(int argc, char **argv);
int					ft_atoi(const char *str);
int					init_struct(int argc, char **argv, t_hold *hold);
//int					init_philos(t_hold *hold);
//int					init_forks(t_hold *hold);
//void				msg(t_philo *philo, char c);
//int					start_process(t_hold *hold);
unsigned long long	cur_time_mcs(void);
void				ft_usleep(unsigned long long time);
//int					end_threads(t_hold *hold);
int					malloc_fail(void);
int					invalid_input(void);
//int					mutex_destroy_fail(void);
//int					pthread_join_fail(void);
//int					pthread_create_fail(void);
//void				clear_mutex_forks(t_hold *hold, int i);

#endif
