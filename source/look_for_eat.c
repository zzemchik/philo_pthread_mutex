#include "philo.h"

void	*chek_eat(void *args)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)args;
	i = -1;
	while (++i < philo->some_param->sum_philo)
	{
		if (philo[i].sum_eat < philo->some_param->philo_eat)
		{
			i = -1;
			continue ;
		}
	}
	pthread_mutex_lock(&(philo->some_param->mutex_read));
	printf("All eated!\n");
	pthread_mutex_unlock(&(philo->some_param->death_mutex));
	pthread_mutex_unlock(&(philo->some_param->mutex_read));
	return (0);
}

void	look_for_philo(t_philo *philo)
{
	pthread_t	pthread_eat;

	pthread_create(&(pthread_eat), NULL, chek_eat, (void *)(philo));
}
