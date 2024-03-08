/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:53:51 by anaouali          #+#    #+#             */
/*   Updated: 2024/03/08 12:15:34 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

pthread_mutex_t	mutex;

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*str1;

	str1 = str;
	while (n > 0)
	{
		*str1 = c;
		n--;
		str1++;
	}
	return (str);
}

void	init_struct(int argc, char **argv, p_list *individual_philo)
{
	individual_philo->total_p_num = ft_atoi(argv[1]);
	individual_philo->philo_t_die = ft_atoi(argv[2]);
	individual_philo->philo_t_eat = ft_atoi(argv[3]);
	individual_philo->philo_t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		individual_philo->philo_must_eat = ft_atoi(argv[5]);
}

void	create_philos(int argc, char **argv, a_list *philo)
{
	p_list	tmp;
	int		i;
	int		c;

	c = -1;
	i = ft_atoi(argv[1]);
	// ft_memset(&tmp, 0, sizeof(a_list));
	philo->individual_philo = malloc(sizeof(p_list) * i);
	if (!philo->individual_philo)
		return ;
	init_struct(argc, argv, &tmp);
	while (++c < i)
	{
		philo->individual_philo[c] = malloc(sizeof(p_list));
		if (!philo->individual_philo)
			return ;
		philo->individual_philo[c] = &tmp;
	}
}

void	*routine(void *arg)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		pthread_mutex_lock(&mutex);
		printf("philo %d is sleeping\n", i);
		printf("philo %d is eating\n", i);
		printf("philo %d is thinking\n", i);
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

int	threads_init(int argc, a_list *philo)
{
	pthread_t	*ph;
	int			i;
	int			c;

	c = 0;
	i = philo->individual_philo[1]->total_p_num;
	ph = malloc(sizeof(i));
	pthread_mutex_init(&philo->mutex, NULL);
	while (i-- > 0)
	{
		if (pthread_create(&ph[i], NULL, &routine, &ph) != 0)
			break;
		printf("created\n");
		c++;
	}
	i = 0;
	while (c-- > 0)
	{
		if (pthread_join(ph[i], NULL) != 0)
			return (1);
		printf("destroyed\n");
		i++;
	}
	pthread_mutex_destroy(&philo->mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	a_list	philo;

	if (!(check_input(argc, argv)))
		return (1);
	else
	// cree un tableau de mutex du nombre de philo
		create_philos(argc, argv, &philo);
	threads_init(argc, &philo);
	return (0);
}
// ft_memset(&philo, 0, sizeof(a_list));
