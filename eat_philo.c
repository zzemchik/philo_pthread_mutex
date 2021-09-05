#include "philo.h"

void	print_fork(t_philo *philo, long int time, int flag)
{
	if (philo->died != 0)
	{
		if (flag == 0)
			printf("%ld %d has taken a right fork\n", time, philo->name);
		else
			printf("%ld %d has taken a left fork\n", time, philo->name);
	}
}

void	eat_queue(t_philo *philo, long int time_start, int l_fork, int r_fork)
{
	struct timeval	time_now;
	int				i;
	int				j;

	if (l_fork > r_fork)
	{
		i = 0;
		j = 1;
	}
	else
	{
		i = 1;
		j = 0;
	}
	pthread_mutex_lock(&(philo->mutex[r_fork]));
	gettimeofday(&(time_now), NULL);
	pthread_mutex_lock(&(philo->some_param->mutex_read));
	print_fork(philo, give_time(time_now) - time_start, i);
	pthread_mutex_unlock(&(philo->some_param->mutex_read));
	pthread_mutex_lock(&(philo->mutex[l_fork]));
	gettimeofday(&(time_now), NULL);
	pthread_mutex_lock(&(philo->some_param->mutex_read));
	print_fork(philo, give_time(time_now) - time_start, j);
	pthread_mutex_unlock(&(philo->some_param->mutex_read));
}

void	eat_help(t_philo *philo, struct timeval	time_now, long int	time_start)
{
	gettimeofday(&(philo->last_eat), NULL);
	gettimeofday(&(time_now), NULL);
	pthread_mutex_lock(&(philo->some_param->mutex_read));
	if (philo->died != 0)
		printf("%ld %d is eating\n", time_now.tv_sec * 1000 + \
		 time_now.tv_usec / 1000 - time_start, philo->name);
	pthread_mutex_unlock(&(philo->some_param->mutex_read));
	_usleep(philo->some_param->time_to_eat);
	(philo->sum_eat)++;
	pthread_mutex_unlock(&(philo->mutex[philo->l_fork]));
	pthread_mutex_unlock(&(philo->mutex[philo->r_fork]));
	gettimeofday(&(time_now), NULL);
	pthread_mutex_lock(&(philo->some_param->mutex_read));
	if (philo->died != 0)
		printf("%ld %d is sleeping\n", time_now.tv_sec * 1000 + \
		time_now.tv_usec / 1000 - time_start, philo->name);
	pthread_mutex_unlock(&(philo->some_param->mutex_read));
	_usleep(philo->some_param->time_to_sleep);
	gettimeofday(&(time_now), NULL);
	pthread_mutex_lock(&(philo->some_param->mutex_read));
	if (philo->died != 0)
		printf("%ld %d is thinking\n", time_now.tv_sec * 1000 + \
		time_now.tv_usec / 1000 - time_start, philo->name);
	pthread_mutex_unlock(&(philo->some_param->mutex_read));
}

void	help_eat2(t_philo *philo, long int time_start)
{
	if (philo->l_fork % 2 == 0)
	{
		if (philo->sum_eat == 0)
			usleep(100);
		eat_queue(philo, time_start, philo->l_fork, philo->r_fork);
	}
	else
		eat_queue(philo, time_start, philo->r_fork, philo->l_fork);
}

void	*eat(void *args)
{
	t_philo				*philo;
	pthread_t			philo_chek;
	long int			time_start;
	struct timeval		time_now;
	t_pair				forks;

	philo = (t_philo *)args;
	forks.left = philo->l_fork;
	forks.right = philo->r_fork;
	gettimeofday(&(philo->last_eat), NULL);
	time_start = philo->last_eat.tv_sec * 1000 + philo->last_eat.tv_usec / 1000;
	philo->time_start = time_start;
	time_now = philo->last_eat;
	pthread_create(&(philo_chek), NULL, chek_time, (void *)(philo));
	while (philo->died == 1)
	{
		help_eat2(philo, time_start);
		eat_help(philo, time_now, time_start);
	}
	pthread_join(philo_chek, NULL);
	return (0);
}
