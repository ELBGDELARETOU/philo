/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:52:25 by anaouali          #+#    #+#             */
/*   Updated: 2024/03/18 15:26:07 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define NUM_PHILO = 0
# define T_TO_DIE = 1
# define T_TO_EAT = 2
# define T_TO_SLEEP = 3
# define MIN_EAT = 4

typedef struct t_list
{
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;

	int				is_dead;
	int				total_p_num;
	int				philo_id;
	int				philo_t_die;
	int				philo_t_eat;
	int				philo_t_sleep;
	int				philo_must_eat;
}					p_list;

typedef struct b_list
{
	pthread_mutex_t	*mutex;
	pthread_t		*tab;
	p_list			**individual_philo;
	int				e;
	int				i;
}					a_list;

long				ft_atoi(char *str);
int					ft_strlen(char *str);
int					ft_isdigit(char c);

// input check
int					check_input(int argc, char **argv);
int					check_valid_argument(int argc, char **argv);
int					ft_isalpha(char *s);
int					ft_is_a_valid_num(char *argv, int i);
int					bigger_than_int(char *str);

// threads funcitons
int					threads_init(int argc, a_list *philo);
void				create_philos_init_threads(int argc, char **argv,
						a_list *philo);
void				init_struct(int argc, char **argv,
						p_list *individual_philo);

#endif