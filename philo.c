/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:21:19 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/23 16:17:49 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	s_info	*info;

	info = philo->info_lst;
	if (philo->philo_id % 2)
	{
		pthread_mutex_lock(&(info->forks[philo->l_fork]));
		my_printf(info, philo->philo_id, "took a fork");
		pthread_mutex_lock(&(info->forks[philo->r_fork]));
	}
	else
	{
		pthread_mutex_lock(&(info->forks[philo->r_fork]));
		my_printf(info, philo->philo_id, "took a fork");
		pthread_mutex_lock(&(info->forks[philo->l_fork]));
	}
	my_printf(info, philo->philo_id, "took a fork");
	pthread_mutex_lock(&(info->checker));
	my_printf(info, philo->philo_id, "eating");
	philo->finished_eating = ft_time();
	(philo->eaten_meals)++;
	pthread_mutex_unlock(&(info->checker));
	ft_sleep(info->philo_t_eat, info);
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
}

int	is_dead2(s_info *info, t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&(info->checker));
	if (info->must_eat != -1)
	{
		i = 0;
		while (i < info->total_p_num && philo[i].eaten_meals >= info->must_eat)
			i++;
		if (i == info->total_p_num)
		{
			info->eaten_all = 1;
			pthread_mutex_unlock(&(info->checker));
			return (123);
		}
	}
	pthread_mutex_unlock(&(info->checker));
	return (0);
}

void	is_dead(s_info *info, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < info->total_p_num)
		{
			pthread_mutex_lock(&(info->checker));
			if ((ft_time() - philo[i].finished_eating) > info->philo_t_die)
			{
				my_printf(info, philo->philo_id, "is dead");
				info->is_dead = 1;
				pthread_mutex_unlock(&(info->checker));
				return ;
			}
			pthread_mutex_unlock(&(info->checker));
			usleep(100);
		}
		if (is_dead2(info, philo) == 123)
			break ;
	}
}

void	*routine(void *param)
{
	t_philo	*philo;
	s_info	*info;

	philo = (t_philo *)param;
	info = philo->info_lst;
	if (philo->philo_id % 2)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&(info->checker));
		if (info->is_dead == 1 || info->eaten_all == 1
			|| info->total_p_num == 1)
		{
			if (info->total_p_num == 1)
				printf("%lld 1 is took a fork\n", (ft_time() - info->time));
			pthread_mutex_unlock(&(info->checker));
			break ;
		}
		pthread_mutex_unlock(&(info->checker));
		eating(philo);
		my_printf(info, philo->philo_id, "thinking");
		ft_sleep(info->philo_t_sleep, info);
		my_printf(info, philo->philo_id, "sleeping");
	}
	return (NULL);
}

int	first_step(s_info *info)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = info->philos;
	info->time = ft_time();
	while (++i < info->total_p_num)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i])))
			return (1);
		pthread_mutex_lock(&(info->checker));
		philo[i].finished_eating = ft_time();
		pthread_mutex_unlock(&(info->checker));
	}
	is_dead(info, info->philos);
	i = -1;
	while (++i < info->total_p_num)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < info->total_p_num)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->writing));
	pthread_mutex_destroy(&(info->checker));
	return (0);
}
