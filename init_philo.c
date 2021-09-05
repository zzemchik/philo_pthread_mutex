#include "philo.h"

t_philo	*init_philo(t_philo *philo, int l_fork, \
t_some_param *some_parm, pthread_mutex_t *mutex)
{
	int	r_fork;

	if (l_fork + 1 == some_parm->sum_philo)
		r_fork = 0;
	else
		r_fork = l_fork + 1;
	philo[l_fork].mutex = mutex;
	philo[l_fork].some_param = some_parm;
	philo[l_fork].l_fork = l_fork;
	philo[l_fork].r_fork = r_fork;
	philo[l_fork].name = l_fork;
	philo[l_fork].died = 1;
	philo[l_fork].sum_eat = 0;
	return (philo);
}
