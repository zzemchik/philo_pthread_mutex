#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct			s_some_param
{
	long long			time_to_died;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					sum_philo;
	int					philo_eat;
	int					death_print;
	long int			time_start;
	pthread_mutex_t   	death_mutex;
	pthread_mutex_t		mutex_read;
	pthread_mutex_t		mutex;
}						t_some_param; 

typedef struct			s_pair
{
	int					left;
	int					right;
}               		t_pair;

typedef struct			s_philo
{
	long int			time_start;
	int					time_philo_died;
	int					name;
	int					l_fork;
	int					r_fork;
	int					died;
	int					sum_eat;
	struct timeval		last_eat;
	pthread_mutex_t		*mutex;
	t_some_param		*some_param;
}						t_philo;

typedef struct			s_forks
{
	int					l_fork;
	int					r_fork;
}						t_forks;

int			time_to_pars(int argv, char **argc, t_some_param *pilo);
int			ft_atoi(const char *str);
int			print_error();
void		*eat(void *args);
void		*chek_time(void *args);
void		_usleep(long time);
t_philo		*init_phil(t_philo *philo, int l_fork, t_some_param *some_parm, pthread_mutex_t *mutex);
long int	give_time(struct timeval time_now);
void		all_free(t_philo *philo, pthread_t *philo_pthr, pthread_mutex_t *mutex);
void		*chek_time(void *args);
void		look_for_philo(t_philo *philo);
#endif