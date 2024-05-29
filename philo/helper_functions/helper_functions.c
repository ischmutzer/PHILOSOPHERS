/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:02:26 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/29 19:37:14 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <pthread.h>

size_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("Error: gettimeofday failed\n"), 1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(t_philo *philo, int time)
{
	size_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < (size_t)time)
	{
		pthread_mutex_lock(philo->death_lock);
		if (*(philo->dead_philo) == 1)
		{
			pthread_mutex_unlock(philo->death_lock);
			return (1);
		}
		pthread_mutex_unlock(philo->death_lock);
		usleep(50);
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*p;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
