/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafouan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 00:51:11 by esafouan          #+#    #+#             */
/*   Updated: 2023/02/16 00:53:09 by esafouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	get_diff_time(long long past_time)
{
	long long	current_time_ms;

	current_time_ms = get_time();
	return (current_time_ms - past_time);
}

int	printerror(char *str)
{
	printf("%s", str);
	return (0);
}
