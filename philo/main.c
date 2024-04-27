/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 01:22:32 by esafouan          #+#    #+#             */
/*   Updated: 2023/02/16 03:40:00 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	creat_forks(t_philo *philo, t_element *elem, int num_philo)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&elem->for_printing, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&elem->for_check, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&elem->eat, NULL) != 0)
		return (-1);
	while (i < num_philo)
	{
		if (pthread_mutex_init(&elem->fork[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (init_philos(philo, elem, num_philo) == -1)
		return (0);
	if (creat_threads(philo, elem) == -1)
		return (0);
	return (0);
}

int	creat_threads(t_philo *philo, t_element *elem)
{
	int	i;

	i = 0;
	elem->initialisation_of_time = get_time();
	while (i < elem->num_philo && elem->time_to_die >= 0)
	{
		if (pthread_create(&(philo[i].thread), NULL, routine, &(philo[i])))
		{
			printerror("The threads could not be created");
			return (-1);
		}
		usleep (50);
		i++;
	}
	return (0);
}

int	init_philos(t_philo *philo, t_element *elem, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		philo[i].philo_index = i + 1;
		philo[i].last_eat = get_time();
		philo[i].elem = elem;
		philo[i].num_eating = 0;
		philo[i].finish_eat = 0;
		philo[i].right_fork = philo[i].philo_index - 1;
		philo[i].left_fork = philo[i].philo_index;
		if (philo[i].left_fork == num_philo)
			philo[i].left_fork = 0;
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int			num_philo;
	t_element	elem;
	t_philo		philo[200];

	if (ac == 5 || ac == 6)
	{
		if (get_args(&elem, av, ac) == -1)
		{
			write(2, "Error in args\n", 14);
			return (0);
		}
		num_philo = elem.num_philo;
		if (creat_forks(philo, &elem, num_philo) == -1)
			return (0);
		while (1)
		{
			if (check_death(philo, &elem))
				break ;
			if (check_num_eating(philo, &elem) == 0)
				break ;
		}
	}
	else
		printerror("check number of args\n");
	return (0);
}
