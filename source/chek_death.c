#include "philo.h"

void	help_chek_time(t_philo *philo, struct timeval tv)
{
	long long	time;

	pthread_mutex_unlock(&(philo->some_param->death_mutex));
	pthread_mutex_lock(&(philo->some_param->mutex_read));
	if (philo->some_param->death_print == 0)
	{
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		printf("%lld %d is died\n", \
		time - philo->time_start, philo->name);
		philo->some_param->death_print = 1;
	}
	pthread_mutex_unlock(&(philo->some_param->mutex_read));
}

void	*chek_time(void *args)
{
	t_philo			*philo;
	struct timeval	tv;
	long long		time;
	long long		time_l;

	philo = (t_philo *)args;
	while (philo->died == 1)
	{
		gettimeofday(&tv, NULL);
		time = tv.tv_sec * 1000000 + tv.tv_usec;
		time_l = philo->last_eat.tv_sec * 1000000 + philo->last_eat.tv_usec;
		if (time - time_l > philo->some_param->time_to_died)
			help_chek_time(philo, tv);
		usleep(100);
	}
	pthread_mutex_lock(&(philo->some_param->mutex));
	pthread_mutex_unlock(&(philo->mutex[philo->l_fork]));
	pthread_mutex_unlock(&(philo->mutex[philo->r_fork]));
	pthread_mutex_unlock(&(philo->some_param->mutex));
	return (0);
}
