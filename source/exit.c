#include "philo.h"

void	all_free(t_philo *philo, pthread_t *philo_pthr, pthread_mutex_t *mutex)
{
	int	i;

	i = -1;
	while (++i < philo->some_param->sum_philo)
		pthread_mutex_destroy(&mutex[i]);
	pthread_mutex_destroy(&philo->some_param->death_mutex);
	pthread_mutex_destroy(&philo->some_param->mutex);
	pthread_mutex_destroy(&philo->some_param->mutex_read);
	if (philo)
		free(philo);
	if (philo_pthr)
		free(philo_pthr);
	if (mutex)
		free(mutex);
}
