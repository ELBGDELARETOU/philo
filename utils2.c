/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:13:26 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/23 16:22:05 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(long long time, t_info *info)
{
	long long	i;

	i = ft_time();
	while (1)
	{
		pthread_mutex_lock(&(info->checker));
		if (info->is_dead)
		{
			pthread_mutex_unlock(&(info->checker));
			break ;
		}
		pthread_mutex_unlock(&(info->checker));
		if ((ft_time() - i) >= time)
			break ;
		usleep(50);
	}
}
