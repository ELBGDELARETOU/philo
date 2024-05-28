/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:21:19 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/28 19:23:16 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	t_info	*info;

	info = philo->info_lst;
	if ((philo->philo_id) % 2 == 1)
	{
		pthread_mutex_lock(&(info->forks[philo->l_fork]));
		pthread_mutex_lock(&(info->forks[philo->r_fork]));
		my_printf(info, philo->philo_id, "took a fork");
		my_printf(info, philo->philo_id, "took a fork");
	}
	else
	{
		pthread_mutex_lock(&(info->forks[philo->r_fork]));
		pthread_mutex_lock(&(info->forks[philo->l_fork]));
		my_printf(info, philo->philo_id, "took a fork");
		my_printf(info, philo->philo_id, "took a fork");
	}
	// pthread_mutex_lock(&(info->forks[philo->r_fork]));
	// pthread_mutex_lock(&(info->forks[philo->l_fork]));
	// my_printf(info, philo->philo_id, "took a fork");
	// my_printf(info, philo->philo_id, "took a fork");
	pthread_mutex_lock(&(info->checker));
	my_printf(info, philo->philo_id, "is eating");
	(philo->eaten_meals)++;
	philo->finished_eating = ft_time();
	pthread_mutex_unlock(&(info->checker));
	ft_sleep(info->philo_t_eat, info);
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
}

int	is_dead2(t_info *info, t_philo *philo)
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

void	is_dead(t_info *info, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < info->total_p_num)
		{
			pthread_mutex_lock(&(info->checker));
			if ((ft_time() - philo[i].finished_eating) > info->philo_t_die
				&& philo->is_eating == 0)
			{
				my_printf(info, philo->philo_id, "is dead");
				info->is_dead = 1;
				pthread_mutex_unlock(&(info->checker));
				return ;
			}
			pthread_mutex_unlock(&(info->checker));
			usleep(10);
		}
		if (is_dead2(info, philo) == 123)
			break ;
	}
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)param;
	info = philo->info_lst;
	if (philo->philo_id % 2 == 0)
		usleep(10);
	while (1)
	{
		pthread_mutex_lock(&(info->checker));
		if (info->is_dead == 1 || info->eaten_all == 1
			|| info->total_p_num == 1)
		{
			if (info->total_p_num == 1)
				printf("%lld 1 took a fork\n", (ft_time() - info->time));
			pthread_mutex_unlock(&(info->checker));
			break ;
		}
		pthread_mutex_unlock(&(info->checker));
		eating(philo);
		my_printf(info, philo->philo_id, "is sleeping");
		ft_sleep(info->philo_t_sleep, info);
		my_printf(info, philo->philo_id, "is thinking");
	}
	return (NULL);
}

int	first_step(t_info *info)
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
	end_ft(info, philo);
	return (0);
}
