/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos_init_threads.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:49:35 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/10 12:23:28 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	init_struct(int argc, char **argv, p_list *individual_philo)
{
	individual_philo->total_p_num = ft_atoi(argv[1]);
	individual_philo->philo_t_die = ft_atoi(argv[2]);
	individual_philo->philo_t_eat = ft_atoi(argv[3]);
	individual_philo->philo_t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		individual_philo->philo_must_eat = ft_atoi(argv[5]);
}

void	create_philos_init_threads(int argc, char **argv, t_list *philo)
{
	t_list tmp;
	int i;
	int c;

	c = -1;
	i = ft_atoi(argv[1]);
	philo->mutex = (pthread_mutex_t *)malloc(ft_atoi(argv[1])
			* sizeof(pthread_t));
	philo->individual_philo = malloc(sizeof(t_list) * i);
	if (!philo->individual_philo)
		return ;
	init_struct(argc, argv, &tmp);
	while (++c < i)
	{
		philo->individual_philo[c] = malloc(sizeof(t_list));
		if (!philo->individual_philo)
			return ;
		philo->individual_philo[c] = &tmp;
	}
}
