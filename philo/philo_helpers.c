/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:06:03 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/29 14:59:50 by ischmutz         ###   ########.fr       */
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

int philo_atoi(const char *str) //its accepting a str that contains letters as well, so "./philo 2 850a 200b00 200c 5" is valid input rn
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
            if (num > 200 && i == 1)
                return (1);
            if (num == 0 && i == 1) //check for num of philo == 0
                return (1);
            if (num <= 0)
                return (printf("Error: invalid argument\n"), 1);
		}
		return (0);
	}
	else
		return (printf("Error: wrong number of arguments\n"), 1);
}

size_t ft_get_time(void)
{
	struct timeval  tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("Error: gettimeofday failed\n"), 1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int ft_usleep(t_philo *philo, int time)
{
    size_t start;

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

void    lock_print(t_data *data, int id, char *msg)
{
    pthread_mutex_lock(&data->print_lock);
    //printf("1gettime: %lu start: %lu\n", ft_get_time(), data->start);
    printf("%lu %d %s\n", (ft_get_time() - data->start), id, msg);
    pthread_mutex_unlock(&data->print_lock);
}

void    lock_n_print(t_philo *philo, int id, char *msg)
{
    if (lock_death(philo) == 1)
        return ;
    pthread_mutex_lock(philo->print_lock);
    //printf("2gettime: %lu start: %lu\n", ft_get_time(), *(philo->start));
    printf("%lu %d %s\n", (ft_get_time() - *(philo->start)), id, msg);
    pthread_mutex_unlock(philo->print_lock);
}

void    change_flag(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->flag = 1;
	pthread_mutex_unlock(&data->death_lock);
}

int    lock_death(t_philo *philo)
{
    pthread_mutex_lock(philo->death_lock);
    if (*(philo->dead_philo) == 1)
    {
        pthread_mutex_unlock(philo->death_lock);
        return (1);
    }
    else
        pthread_mutex_unlock(philo->death_lock);
    return (0);
}

void    philo_is_eating(t_philo *philo)
{
    if (lock_death(philo) == 1)
        return ;
    pthread_mutex_lock(philo->meal_lock);
    ++philo->meals_eaten;
    pthread_mutex_unlock(philo->meal_lock);
}

void    philo_finished_eating(t_philo *philo)
{
    if (lock_death(philo) == 1)
        return ;
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = ft_get_time();
    pthread_mutex_unlock(philo->meal_lock);
}

void    destroy_mutexes(t_data *data)
{
    int i;

    i = -1;
    pthread_mutex_destroy(&data->death_lock);
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->meal_lock);
    while (++i < data->philo_count)
        pthread_mutex_destroy(&data->forks[i]);
}

void    cleanup_philos(t_data *data, int index)
{
    int i;

    i = 0;
    if (index == -1)
    {
        if (pthread_join(data->monitor, NULL) != 0)
            change_flag(data);
        return;
    }
    else
    {
        while (i < index)
        {
            if (pthread_join(data->philos[i].thread, NULL) != 0)
                change_flag(data);
            i++;
        }
    }
    destroy_mutexes(data);
    free(data->philos);
}
