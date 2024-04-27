/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 03:40:29 by esafouan          #+#    #+#             */
/*   Updated: 2023/02/16 03:47:25 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct atoii
{
	int		i;
	long	j;
	int		sign;
}	t_atoii;

typedef struct elements
{
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		times_must_eat;
	int				num_philo;
	long long		initialisation_of_time;
	pthread_mutex_t	for_printing;
	pthread_mutex_t	for_check;
	pthread_mutex_t	eat;
	pthread_mutex_t	fork[200];
}	t_element;

typedef struct s_philo
{
	pthread_t	thread;
	int			philo_index;
	long long	last_eat;
	int			left_fork;
	int			right_fork;
	int			finish_eat;
	int			num_eating;
	t_element	*elem;
}	t_philo;

long long	get_time(void);
int			get_diff_time(long long past_time);
int			printerror(char *str);
int			ft_atoi(char *str);
int			check_args(t_element *t, int ac);
int			get_args(t_element *t, char **av, int ac);
void		printing(t_element *elem, int i, char *str);
void		philo_dies_print(int i, t_element *elem);
int			check_num_eating(t_philo *philo, t_element *elem);
int			check_death(t_philo *philo, t_element *elem);
void		sleeping(t_philo *philo, t_element *elem);
void		eating(t_philo *philo, t_element *elem);
void		thinking(t_philo *philo, t_element *elem);
void		*routine(void *tmp);
int			creat_forks(t_philo *philo, t_element *elem, int num_philo);
int			creat_threads(t_philo *philo, t_element *elem);
int			init_philos(t_philo *philo, t_element *elem, int num_philo);

#endif
