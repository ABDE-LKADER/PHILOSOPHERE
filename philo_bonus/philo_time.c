/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:55:46 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/19 00:57:21 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

time_t	get_time(void)
{
	struct timeval	time;

	return (gettimeofday(&time, NULL),
		(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void sle_ep(time_t time)
{
	time_t start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}
