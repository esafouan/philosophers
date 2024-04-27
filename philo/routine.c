/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 01:00:25 by esafouan          #+#    #+#             */
/*   Updated: 2023/02/16 01:14:56 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printing(t_element *elem, int i, char *str)
{
	long long	time_print;

	pthread_mutex_lock(&elem->for_printing);
	time_print = get_diff_time(elem->initialisation_of_time);
	printf("%lld %d %s\n", time_print, i, str);
	pthread_mutex_unlock(&elem->for_printing);
}

void	sleeping(t_philo *philo, t_element *elem)
{
	long long	time_sleep;

	time_sleep = get_time();
	printing(elem, philo->philo_index, "is sleeping");
	while (get_time() - time_sleep < elem->time_to_sleep)
		usleep(1000);
}

void	eating(t_philo *philo, t_element *elem)
{
	pthread_mutex_lock(&elem->fork[philo->right_fork]);
	printing(elem, philo->philo_index, "has taken a fork");
	pthread_mutex_lock(&elem->fork[philo->left_fork]);
	printing(elem, philo->philo_index, "has taken a fork");
	pthread_mutex_lock(&elem->for_check);
	philo->num_eating += 1;
	philo->last_eat = get_time();
	pthread_mutex_unlock(&elem->for_check);
	printing(elem, philo->philo_index, "is eating");
	while (get_time() - philo->last_eat < elem->time_to_eat)
		usleep(1000);
	pthread_mutex_unlock(&elem->fork[philo->right_fork]);
	pthread_mutex_unlock(&elem->fork[philo->left_fork]);
}

void	thinking(t_philo *philo, t_element *elem)
{
	printing(elem, philo->philo_index, "is thinking");
}

void	*routine(void *tmp)
{	
	t_philo		*philos;
	t_element	*elem;

	philos = (t_philo *)tmp;
	elem = philos->elem;
	if (philos->philo_index % 2 == 0)
		usleep(500);
	while (1)
	{
		eating(philos, elem);
		sleeping(philos, elem);
		thinking(philos, elem);
	}
	return (NULL);
}
