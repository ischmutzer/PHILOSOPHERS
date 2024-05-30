/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:53:18 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/30 15:36:25 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print_monitor(t_data *data, int id, char *msg)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%lu %d %s\n", (ft_get_time() - data->start), id + 1, msg);
	pthread_mutex_unlock(&data->print_lock);
}

void	change_flag(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->flag = 1;
	pthread_mutex_unlock(&data->death_lock);
}
