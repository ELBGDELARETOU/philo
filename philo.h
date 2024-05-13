/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaouali <anaouali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:52:25 by anaouali          #+#    #+#             */
/*   Updated: 2024/05/10 16:49:43 by anaouali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define NUM_PHILO = 0
# define T_TO_DIE = 1
# define T_TO_EAT = 2
# define T_TO_SLEEP = 3
# define MIN_EAT = 4

struct t_info;

typedef struct t_philo
{
	int				philo_id;
	int				finished_eating;
	int				l_fork;
	int				r_fork;
	struct t_info	*data_list;
	pthread_t		thread_id;
}					t_philo;

typedef struct t_info
{
	int				finsished;
	int				is_dead;
	int				total_p_num;
	int				philo_t_die;
	int				philo_t_eat;
	int				philo_t_sleep;
	int				philo_must_eat;
	long long		time;

	pthread_mutex_t	forks[200];
	t_philo			philos[200];
}					t_info;

long				ft_atoi(char *str);
int					ft_strlen(char *str);
int					ft_isdigit(char c);
void				*ft_memset(void *str, size_t n);

// input check
int					check_input(int argc, char **argv);
int					check_valid_argument(int argc, char **argv);
int					ft_isalpha(char *s);
int					ft_is_a_valid_num(char *argv, int i);
int					bigger_than_int(char *str);

// threads funcitons
// int					threads_init(int argc, a_list *philo);
// void				create_philos_init_threads(int argc, char **argv,
// 						t_list *philo);
// void				init_struct(int argc, char **argv,
// 						t_list *individual_philo);

#endif