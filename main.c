/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:53:51 by anaouali          #+#    #+#             */
/*   Updated: 2024/03/18 15:30:52 by anaouali         ###   ########.fr       */
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
	printf("philo number : %d\n", philo->e);
	philo->e++;
	pthread_mutex_unlock(&philo->mutex[0]);
	return (NULL);
}

int	threads_init(int argc, a_list *philo)
{
	int	index;
	int	c;

	c = 0;
	philo->i = philo->individual_philo[1]->total_p_num;
	index = philo->i;
	philo->tab = malloc(philo->i  * sizeof(pthread_t));
	if (!philo->tab)
		return (0);
	philo->e = 1;
	pthread_mutex_init(&philo->mutex[0], NULL);
	while (index > 0)
	{
		printf("created\n");
		if (pthread_create(&philo->tab[c], NULL, &routine, (void *)philo) != 0)
			return (0);
		c++;
		index--;
	}
	return (1);
}
int	thread_join(int argc, a_list *philo)
{
	int	i;
	int	c;

	i = 0;
	c =  philo->i;
	while (c > 0)
	{
		if (pthread_join(philo->tab[i], NULL) != 0)
			return (0);
		printf("joined\n");
		i++;
		c--;
	}
	return (1);
}

int	thread_destroy(int argc, a_list *philo)
{
	int	i;
	int	c;

	c = 0;
	i = philo->i;
	while (i > 0)
	{
		printf("destroyed\n");
		pthread_mutex_destroy(&philo->mutex[c]);
		c++;
		i--;
	}
	free(philo->tab);
	return (1);
}

int	main(int argc, char **argv)
{
	a_list	philo;

	if (!(check_input(argc, argv)))
		return (1);
	else
	{
		create_philos_init_threads(argc, argv, &philo);
		if (threads_init(argc, &philo) == 0)
			return (1);
		if (thread_join(argc, &philo) == 0)
			return (1);
		if (thread_destroy(argc, &philo) == 0)
			return (1);
	}
	return (0);
}
// ft_memset(&philo, 0, sizeof(a_list));
