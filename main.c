#include "philo.h"

void	init_mutex(pthread_mutex_t *mutex, t_some_param *some_param)
{
	int	j;

	j = 0;
	while (++j < some_param->sum_philo)
		pthread_mutex_init(&(mutex[j]), NULL);
	pthread_mutex_init(&(some_param->death_mutex), NULL);
	pthread_mutex_init(&(some_param->mutex), NULL);
	pthread_mutex_init(&(some_param->mutex_read), NULL);
}

void	*death(void *args)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)args;
	i = -1;
	pthread_mutex_lock(&(philo->some_param->death_mutex));
	while (++i < philo->some_param->sum_philo)
		philo[i].died = 0;
	pthread_mutex_unlock(&(philo->some_param->death_mutex));
	return (0);
}

void	help_main(t_some_param	some_param, t_philo *philo, \
pthread_mutex_t	*mutex, pthread_t *philo_pthr)
{
	pthread_t	pthread_death;
	int			argv;

	argv = -1;
	while (++argv < some_param.sum_philo)
		philo = init_philo(philo, argv, &some_param, mutex);
	if (some_param.philo_eat != 0)
		look_for_philo(philo);
	pthread_mutex_lock(&(philo->some_param->death_mutex));
	pthread_create(&(pthread_death), NULL, death, (void *)(philo));
	argv = -1;
	while (++argv < some_param.sum_philo)
		pthread_create(&(philo_pthr[argv]), NULL, eat, (void *)(&philo[argv]));
	argv = -1;
	while (++argv < some_param.sum_philo)
		pthread_join((philo_pthr[argv]), NULL);
	pthread_join(pthread_death, NULL);
}

int	main(int argv, char **argc)
{
	t_philo			*philo;
	t_some_param	some_param;
	pthread_t		*philo_pthr;
	pthread_mutex_t	*mutex;

	if (time_to_pars(argv, argc, &some_param) == -1)
	{
		printf ("Error arguments!\n");
		return (0);
	}
	philo = malloc(sizeof(t_philo) * (some_param.sum_philo));
	philo_pthr = malloc(sizeof(pthread_t) * (some_param.sum_philo));
	mutex = malloc(sizeof(pthread_mutex_t) * some_param.sum_philo);
	if (!philo || !philo_pthr || !mutex)
		all_free(philo, philo_pthr, mutex);
	init_mutex(mutex, &some_param);
	help_main(some_param, philo, mutex, philo_pthr);
	all_free(philo, philo_pthr, mutex);
}
