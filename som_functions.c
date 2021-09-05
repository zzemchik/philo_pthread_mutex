#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	n;
	int	t;

	t = 0;
	n = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' || \
			*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		n = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - 48);
	if (*str != 0)
		return (-1);
	return (res * n);
}

void	_usleep(long time)
{
	struct timeval	begin;
	struct timeval	current;
	long			start;
	long			now;

	gettimeofday(&begin, NULL);
	gettimeofday(&current, NULL);
	start = (begin.tv_sec * 1000000) + begin.tv_usec;
	now = (current.tv_sec * 1000000) + current.tv_usec;
	while ((now - start) < time)
	{
		usleep(50);
		gettimeofday(&current, NULL);
		now = (current.tv_sec * 1000000) + current.tv_usec;
	}
}

long int	give_time(struct timeval time_now)
{
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}
