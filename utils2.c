/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:13:26 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/28 19:23:28 by anaouali         ###   ########.fr       */
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
		if (info->total_p_num % 2 == 0)
			usleep(info->philo_t_eat);
		else
			usleep(10);
	}
}
void	end_ft(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->total_p_num)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < info->total_p_num)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->writing));
	pthread_mutex_destroy(&(info->checker));
}