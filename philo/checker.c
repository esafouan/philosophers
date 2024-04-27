/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 01:15:58 by esafouan          #+#    #+#             */
/*   Updated: 2023/02/16 16:27:36 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_dies_print(int i, t_element *elem)
{
	long long	time_print;

	pthread_mutex_lock(&elem->for_printing);
	time_print = get_diff_time(elem->initialisation_of_time);
	printf("%lld %d %s\n", time_print, i, "died");
}

void	destroy_all_mutexes(t_element *elem)
{
	int	i;

	i = 0;
	while (i < elem->num_philo)
	{
		pthread_mutex_destroy(&elem->fork[i]);
		i++;
	}
	pthread_mutex_destroy(elem->fork);
	pthread_mutex_destroy(&elem->for_check);
	pthread_mutex_destroy(&elem->for_printing);
}

int	check_num_eating(t_philo *philo, t_element *elem)
{
	int	count;

	count = 0;
	pthread_mutex_lock(&elem->for_check);
	if (elem->times_must_eat != -1)
	{
		while (count < elem->num_philo
			&& (philo[count].num_eating >= elem->times_must_eat))
			count++;
		if (count == elem->num_philo)
		{
			destroy_all_mutexes(elem);
			return (0);
		}
	}
	pthread_mutex_unlock(&elem->for_check);
	return (1);
}

int	check_death(t_philo *philo, t_element *elem)
{
	int	last_meal_diff_time;
	int	count;

	count = 0;
	pthread_mutex_lock(&elem->for_check);
	while (count < elem->num_philo)
	{
		last_meal_diff_time = get_diff_time(philo[count].last_eat);
		if (last_meal_diff_time > elem->time_to_die)
		{
			philo_dies_print(philo[count].philo_index, elem);
			destroy_all_mutexes(elem);
			return (1);
		}
		count++;
	}
	pthread_mutex_unlock(&elem->for_check);
	return (0);
}
