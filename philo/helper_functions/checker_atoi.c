/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:06:03 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/29 19:27:12 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <pthread.h>

static int	check_space(const char c)
{
	if (9 <= c && c <= 13)
		return (1);
	else if (c == 32)
		return (1);
	else
		return (0);
}

int	philo_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

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

int	check_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
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
			if (check_str(args[i]))
				return (printf("Invalid input: non-numeric argument\n"), 1);
			num = philo_atoi(args[i]);
			if (num > 200 && i == 1)
				return (printf("Invalid input: too many philos\n"), 1);
			if (num == 0 && i == 1)
				return (printf("Invalid input: num of philos\n"), 1);
			if (num <= 0)
				return (printf("Invalid argument\n"), 1);
		}
		return (0);
	}
	else
		return (printf("Error: wrong number of arguments\n"), 1);
}
