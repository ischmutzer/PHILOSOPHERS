/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:06:03 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/17 20:16:07 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

static int check_space(const char c)
{
    if (9 <= c && c <= 13)
        return (1);
    else if (c == 32)
        return (1);
    else
        return (0);
}

int philo_atoi(const char *str)
{
    int i;
    int sign;
    int res;

    i = 0;
    sign = 1;
    res = 0;
    if (!str)
        return (0);
    while (check_space(str[i]))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    if (str[i] > '9' || str[i] < '0')
        return (0);
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = (res * 10) + (str[i] - '0');
        i++;
    }
    return (res * sign);
}

int	check_whether_valid_input(int argc, char **args)
{
	int	num;
	int	i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		while (args[++i])
		{
			num = philo_atoi(args[i]);
            if (num >= 200 && i == 1)
                return (1);
            if (num <= 0)
                return (printf("Error: invalid argument\n"), 1);
		}
		return (0);
	}
	else
		return (printf("Error: wrong number of arguments\n"), 1);
}

int ft_get_time(void)
{
	struct timeval  tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("Error: gettimeofday failed\n"), 1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(t_philo *philo, int time)
{
    int start;

    start = ft_get_time();
    while (ft_get_time() - start < time)
    {
        if (*(philo->dead_philo) == 1)
            break;
        usleep(100);
    }
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

void    lock_n_print(t_philo *philo, int id, char *msg)
{
    pthread_mutex_lock(philo->print_lock);
    printf("%d %d %s\n", (ft_get_time() - *(philo->start)), id, msg);
    pthread_mutex_unlock(philo->print_lock);
}

int    lock_death(t_philo *philo)
{
    pthread_mutex_lock(philo->death_lock);
    if (*(philo->dead_philo) == 1)
        return (1);
    pthread_mutex_unlock(philo->death_lock);
}

void    lock_meal(t_philo *philo, int mode)
{
    pthread_mutex_lock(philo->meal_lock);
    if (mode == 1)
        philo->is_eating = 1;
    else if (mode == 0)
        philo->is_eating = 0;
    else if (mode == 2)
        ++philo->meals_eaten;
    else if (mode == 3)
        philo->last_meal = ft_get_time();
    pthread_mutex_unlock(philo->meal_lock);
}

void    cleanup_philos(t_data *data, int index)
{
    int i;

    i = 0;
    while (i <= index)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
            data->flag = 1;
    }
}
