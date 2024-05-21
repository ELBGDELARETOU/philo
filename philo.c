/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademnaouali <ademnaouali@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:21:19 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/21 12:28:43 by ademnaouali      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_sleep(long long time, t_info *rules)
{
	long long i;

	i = ft_time();
	while (rules->is_dead != 1)
	{
		if ((ft_time() - i) >= time)
			break ;
		usleep(50);
	}
}

void	eating(t_philo *philo)
{
	t_info *info;

	info = philo->info_lst;
	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	printf("Time : %lld philo : %d took a fork\n", ft_time() -info->time , philo->philo_id + 1);
	pthread_mutex_lock(&(info->forks[philo->r_fork]));
	printf("Time : %lld philo : %d took a fork\n", ft_time() - info->time ,philo->philo_id + 1);
	pthread_mutex_lock(&(info->checker));
	printf("Time : %lld philo : %d is eating\n", ft_time() - info->time,  philo->philo_id + 1);
	philo->finished_eating = ft_time();
	pthread_mutex_unlock(&(info->checker));
	ft_sleep(info->philo_t_eat, info);
	(philo->eaten_meals)++;
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
}

void	is_dead(t_info *info, t_philo *philo)
{
	int i;

	while (info->eaten_all != 1)
	{
		i = -1;
		while (++i < info->total_p_num && info->is_dead != 1)
		{
			pthread_mutex_lock(&(info->checker));
			if((ft_time() - philo[i].finished_eating) > info->philo_t_die)
			{
				printf("%d is dead", philo->philo_id);
				info->is_dead = 1;
			}
			pthread_mutex_unlock(&(info->checker));
			usleep(100);
		}
		if (info->is_dead)
			break;
		i = 0;
		while (info->must_eat != -1 && i < info->total_p_num && philo[i].eaten_meals >= info->must_eat)
			i++;
		if (i == info->total_p_num)
			info->eaten_all = 1;
	}
}

void	*routine(void *param)
{
	t_philo *philo;
	t_info *info;
	
	philo = (t_philo *)param;
	info = philo->info_lst;
	if(philo->philo_id % 2)
		usleep(15000);
	while (info->is_dead != 1)
	{
		eating(philo);
		if(info->eaten_all)
			break;
		my_printf(info, philo->philo_id, "sleeping");
		ft_sleep(info->philo_t_sleep, info);
		my_printf(info, philo->philo_id, "thinking");
	}
	return (NULL);
}

int first_step(t_info *info)
{
	int i;
	t_philo *philo;
	
	i = -1;
	philo = info->philos;
	info->time = ft_time();
	while(++i < info->total_p_num)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i])))
			return (1);
		philo[i].finished_eating = ft_time();
	}
	is_dead(info, info->philos);
	i = -1;
	while (++i < info->total_p_num)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->writing));
	return (0);
}
