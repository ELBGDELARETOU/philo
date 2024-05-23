/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:15:09 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/23 16:21:54 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	struct t_info	info;

	if (check_input(ac, av) == false)
		return (1);
	if (init(ac, av, &info) == false)
		return (2);
	if (first_step(&info) == false)
		return (3);
	return (0);
}
