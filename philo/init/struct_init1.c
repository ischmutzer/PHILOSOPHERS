/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:01:50 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/29 19:41:37 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// int init_n_malloc_struct(t_data *data, t_philo **philos, char **argv)
// {
//     bzero(&data, sizeof(*data));
// 	data->philo_count = philo_atoi(argv[1]);
// 	*philos = (t_philo *)malloc(data->philo_count * sizeof(t_philo));
// 	if (!philos)
// 		return (printf("malloc failed\n"), 1);
// 	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
// 	if (!data->forks)
// 		return(free(philos), printf("malloc failed\n"), 1);
// 	bzero(philos, sizeof(**philos));
// 	data_init(data, *philos, argv);
// 	forks_init(data, data->philo_count);
// 	philos_init(data, *philos, argv);
//     return (0);
// }
