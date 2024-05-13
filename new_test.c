/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:21:19 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/10 16:21:12 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	first_step(void);

void	get_my_infos(int ac, char **argv, t_info *philo)
{
	philo->total_p_num = ft_atoi(argv[1]);
	philo->philo_t_die = ft_atoi(argv[2]);
	philo->philo_t_eat = ft_atoi(argv[3]);
	philo->philo_t_sleep = ft_atoi(argv[4]);
	if (ac == 6)
		philo->philo_must_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	struct t_info *philo;

	philo = malloc(sizeof(t_info));
	ft_memset(philo, sizeof(philo));
	if (check_input(argc, argv) == false)
		return (1);
	get_my_infos(argc, argv, philo);
	// if (first_step(void))
	// 	return (printf("A philo died !\n"));
	return (free(philo), 0);
}