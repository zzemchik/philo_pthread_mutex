#include "philo.h"

int	time_to_pars(int argv, char **argc, t_some_param *pilo)
{
	int	i;

	i = 0;
	if (argv > 6 || argv < 5)
		return (-1);
	pilo->sum_philo = ft_atoi(argc[1]);
	pilo->time_to_died = ft_atoi(argc[2]) * 1000;
	pilo->time_to_eat = ft_atoi(argc[3]) * 1000;
	pilo->time_to_sleep = ft_atoi(argc[4]) * 1000;
	if (argv == 6)
		pilo->philo_eat = ft_atoi(argc[5]);
	else
		pilo->philo_eat = 0;
	pilo->death_print = 0;
	if (pilo->time_to_died < 0)
		return (-1);
	if (pilo->time_to_eat < 0)
		return (-1);
	if (pilo->time_to_sleep < 0)
		return (-1);
	if (pilo->sum_philo <= 0)
		return (-1);
	if (pilo->philo_eat < 0)
		return (-1);
	return (0);
}
