/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:53:51 by anaouali          #+#    #+#             */
/*   Updated: 2024/03/15 13:33:14 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>


void	*routine(void *arg)
{
	a_list	*philo;

	philo = (a_list *)arg;
	usleep(100);
	pthread_mutex_lock(&philo->mutex[0]);
	printf("philo number : %d\n",philo->e);
	fflush(stdout);
	philo->e++;
	pthread_mutex_unlock(&philo->mutex[0]);
	return (NULL);
}

int	threads_init(int argc, a_list *philo)
{
	int			i;
	int			c;
	pthread_t	tab[2];

	c = 0;
	i = philo->individual_philo[1]->total_p_num;
	philo->e = 0;
	pthread_mutex_init(&philo->mutex[0], NULL);
	while (i > 0)
	{
		printf("created\n");
		fflush(stdout);
		if (pthread_create(&tab[c], NULL, &routine, (void *)philo) != 0)
			return (0);
		c++;
		i--;
	}
	i = 0;
	while (c > 0)
	{
		if (pthread_join(tab[i], NULL) != 0)
			return (1);
		printf("joined\n");
		fflush(stdout);
		i++;
		c--;
	}
	c = 0;
	while (i > 0)
	{
		printf("destroyed\n");
		pthread_mutex_destroy(&philo->mutex[c]);
		c++;
		i--;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	a_list	philo;

	if (!(check_input(argc, argv)))
		return (1);
	else
	{
		// printf("q\n");
		create_philos_init_threads(argc, argv, &philo);
		if (threads_init(argc, &philo) == 0)
			return (1);
	}
	return (0);
}
// ft_memset(&philo, 0, sizeof(a_list));
