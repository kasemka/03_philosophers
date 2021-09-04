#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <stdlib.h>
# include <signal.h>
//# include <string.h>
# include <sys/time.h>

typedef struct s_hold
{
	int					name;
	int					philos_n;
	unsigned long long	time_die;
	unsigned long long	time_eat;
	int					time_sleep;
	int					eat_num_min;
	int					eat_num;
	unsigned long long	last_eat;
	unsigned long long	start_time;
	int					stop_sim;
	sem_t				*forks_sem;
	sem_t				*death;
	sem_t				*print;
}	t_hold;

int					parse(int argc, char **argv);
int					ft_atoi(const char *str);
int					init_struct(int argc, char **argv, t_hold *hold);
void				msg(t_hold *philo, char c);
unsigned long long	cur_time_mcs(void);
void				ft_usleep(unsigned long long time, int stop_sim);
void				end_processes(t_hold *hold, int *forks_pid);
int					malloc_fail(void);
int					invalid_input(void);

#endif
