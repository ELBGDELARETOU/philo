/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademnaouali <ademnaouali@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:21:19 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/15 16:12:43 by ademnaouali      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_checker(t_info *info, t_philo *philo)
{
	int i;

	while (info->philo_must_eat)
}


void	eating(t_philo *philo)
{
	t_info *info;

	info = philo->info_lst;
	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	printf("philo : %d took a fork\n", philo->philo_id);
	pthread_mutex_lock(&(info->forks[philo->r_fork]));
	printf("philo : %d took a fork\n", philo->philo_id);
	philo->finished_eating = ft_time();
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
}

void	*routine(void *param)
{
	t_philo *philo;
	t_info *info;

	philo = (t_philo *)param;
	info = philo->info_lst;
	if(philo->philo_id % 2 != 0)
		usleep(15000);
	while (info->is_dead != 1)
	{
		eating(philo);
		if(info->finsished == 1)
			break;
		usleep(50);
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
	// death_checker(info, info->philos);
	i = -1;
	while (++i < info->total_p_num)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i)
		pthread_mutex_destroy(&(info->forks[i]));
	return (0);
}

int	main(int ac, char **av)
{
	struct t_info *info;

	info = malloc(sizeof(t_info));
	ft_memset(info, sizeof(info));
	if (check_input(ac, av) == false)
		return (1);
	if (init(ac, av, info) == false)
		return(2);
	if (first_step(info) == false)
		return(3);
	return(0);
}