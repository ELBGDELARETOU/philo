/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:21:19 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/21 18:44:27 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	ft_sleep(long long time, t_info *info)
// {
// 	long long	i;

// 	i = ft_time();
// 	while (info->is_dead != 1)
// 	{
// 		pthread_mutex_lock(&(info->checker));
// 		if ((ft_time() - i) >= time)
// 		{
// 			pthread_mutex_unlock(&(info->checker));
// 			break ;
// 		}
// 		pthread_mutex_unlock(&(info->checker));
// 		usleep(50);
// 	}
// }

// void	eating(t_philo *philo)
// {
// 	t_info	*info;

// 	info = philo->info_lst;
// 	pthread_mutex_lock(&(info->forks[philo->l_fork]));
// 	printf("%lld %d took a fork\n", ft_time() - info->time, philo->philo_id
// 		+ 1);
// 	pthread_mutex_lock(&(info->forks[philo->r_fork]));
// 	printf("%lld %d took a fork\n", ft_time() - info->time, philo->philo_id
// 		+ 1);
// 	pthread_mutex_lock(&(info->checker));
// 	printf("%lld %d is eating\n", ft_time() - info->time, philo->philo_id + 1);
// 	philo->finished_eating = ft_time();
// 	(philo->eaten_meals)++;
// 	pthread_mutex_unlock(&(info->checker));
// 	ft_sleep(info->philo_t_eat, info);
// 	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
// 	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
// }

// void	is_dead(t_info *info, t_philo *philo)
// {
// 	int	i;

// 	while (info->eaten_all != 1)
// 	{
// 		i = -1;
// 		while (++i < info->total_p_num && info->is_dead != 1)
// 		{
// 			pthread_mutex_lock(&(info->checker));
// 			if ((ft_time() - philo[i].finished_eating) > info->philo_t_die)
// 			{
// 				printf("%d is dead", philo->philo_id);
// 				pthread_mutex_unlock(&(info->checker));
// 				info->is_dead = 1;
// 			}
// 			pthread_mutex_unlock(&(info->checker));
// 			usleep(100);
// 		}
// 		if (info->is_dead)
// 			break ;
// 		i = 0;
// 		while (info->must_eat != -1 && i < info->total_p_num
// 			&& philo[i].eaten_meals >= info->must_eat)
// 			i++;
// 		pthread_mutex_lock(&(info->checker));
// 		if (i == info->total_p_num)
// 			info->eaten_all = 1;
// 		pthread_mutex_unlock(&(info->checker));
// 	}
// }

// void	*routine(void *param)
// {
// 	t_philo	*philo;
// 	t_info	*info;

// 	philo = (t_philo *)param;
// 	info = philo->info_lst;
// 	if (philo->philo_id % 2)
// 		usleep(15000);
// 	while (1)
// 	{
// 		pthread_mutex_lock(&(info->checker));
// 		if (info->is_dead || info->eaten_all)
// 		{
// 			pthread_mutex_unlock(&(info->checker));
// 			break ;
// 		}
// 		pthread_mutex_unlock(&(info->checker));
// 		eating(philo);
// 		my_printf(info, philo->philo_id, "sleeping");
// 		ft_sleep(info->philo_t_sleep, info);
// 		my_printf(info, philo->philo_id, "thinking");
// 	}
// 	return (NULL);
// }

// int	first_step(t_info *info)
// {
// 	int		i;
// 	t_philo	*philo;

// 	i = -1;
// 	philo = info->philos;
// 	info->time = ft_time();
// 	while (++i < info->total_p_num)
// 	{
// 		if (pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i])))
// 			return (1);
// 		philo[i].finished_eating = ft_time();
// 	}
// 	is_dead(info, info->philos);
// 	i = -1;
// 	while (++i < info->total_p_num)
// 		pthread_join(philo[i].thread_id, NULL);
// 	i = -1;
// 	while (++i)
// 		pthread_mutex_destroy(&(info->forks[i]));
// 	pthread_mutex_destroy(&(info->writing));
// 	pthread_mutex_destroy(&(info->checker));
// 	return (0);
// }

void	ft_sleep(long long time, t_info *rules)
{
	long long	i;

	i = ft_time();
	while (1)
	{
		pthread_mutex_lock(&(rules->checker));
		if (rules->is_dead)
		{
			pthread_mutex_unlock(&(rules->checker));
			break ;
		}
		pthread_mutex_unlock(&(rules->checker));
		if ((ft_time() - i) >= time)
			break ;
		usleep(50);
	}
}

void	eating(t_philo *philo)
{
	t_info	*info;

	info = philo->info_lst;
	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	my_printf(info, philo->philo_id, "took a fork");
	pthread_mutex_lock(&(info->forks[philo->r_fork]));
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

void	is_dead(t_info *info, t_philo *philo)
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
				printf("%lld %d is dead\n", ft_time() - info->time,
					philo[i].philo_id + 1);
				info->is_dead = 1;
				pthread_mutex_unlock(&(info->checker));
				return ;
			}
			pthread_mutex_unlock(&(info->checker));
			usleep(100);
		}
		pthread_mutex_lock(&(info->checker));
		if (info->is_dead)
		{
			pthread_mutex_unlock(&(info->checker));
			break ;
		}
		if (info->must_eat != -1)
		{
			i = 0;
			while (i < info->total_p_num
				&& philo[i].eaten_meals >= info->must_eat)
				i++;
			if (i == info->total_p_num)
			{
				info->eaten_all = 1;
				pthread_mutex_unlock(&(info->checker));
				break ;
			}
		}
		pthread_mutex_unlock(&(info->checker));
	}
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)param;
	info = philo->info_lst;
	if (philo->philo_id % 2)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&(info->checker));
		if (info->is_dead || info->eaten_all)
		{
			pthread_mutex_unlock(&(info->checker));
			break ;
		}
		pthread_mutex_unlock(&(info->checker));
		eating(philo);
		my_printf(info, philo->philo_id, "sleeping");
		ft_sleep(info->philo_t_sleep, info);
		my_printf(info, philo->philo_id, "thinking");
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
