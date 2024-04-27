/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 00:53:49 by esafouan          #+#    #+#             */
/*   Updated: 2023/02/16 00:59:03 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	t_atoii	q;

	q.sign = 1;
	q.i = 0;
	q.j = 0;
	while (str[q.i] == 32 || (str[q.i] >= 9 && str[q.i] <= 13))
		q.i++;
	if (str[q.i] == '-' || str[q.i] == '+')
	{
		if (str[q.i] == '-')
			q.sign *= -1;
		q.i++;
	}	
	if (str[q.i] == '\0')
		return (-1);
	while (str && str[q.i])
	{
		if (!(str[q.i] <= '9' && str[q.i] >= '0'))
			return (-1);
		q.j = q.j * 10 + str[q.i] - 48;
		q.i++;
	}
	if (q.j * q.sign > 2147483647 || q.j * q.sign < 0)
		return (-1);
	return (q.j * q.sign);
}

int	check_args(t_element *t, int ac)
{
	if (ac == 5)
	{
		if (t->num_philo == -1 || t->num_philo > 200 || t->time_to_die == -1
			|| t->time_to_eat == -1 || t->time_to_sleep == -1)
			return (-1);
	}
	if (ac == 6)
	{
		if (t->num_philo == -1 || t->num_philo > 200 || t->time_to_die == -1
			|| t->time_to_eat == -1 || t->time_to_sleep == -1
			|| t->times_must_eat == -1)
			return (-1);
	}
	return (0);
}

int	get_args(t_element *t, char **av, int ac)
{
	if (ac == 5)
	{
		t->num_philo = ft_atoi(av[1]);
		t->time_to_die = ft_atoi(av[2]);
		t->time_to_eat = ft_atoi(av[3]);
		t->time_to_sleep = ft_atoi(av[4]);
		t->times_must_eat = -1;
	}
	else if (ac == 6)
	{
		t->num_philo = ft_atoi(av[1]);
		t->time_to_die = ft_atoi(av[2]);
		t->time_to_eat = ft_atoi(av[3]);
		t->time_to_sleep = ft_atoi(av[4]);
		t->times_must_eat = ft_atoi(av[5]);
	}
	if (check_args(t, ac) == -1)
		return (-1);
	return (0);
}
