/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:10:42 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/04 19:41:34 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

size_t	get_time(void)
{
	struct timeval	time;

	return (gettimeofday(&time, NULL),
		(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static int	create_philos(t_philo **philo, t_infos *infos, int uid)
{
	t_philo		*new;
	t_philo		*last;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (ERROR);
	(TRUE) && (new->uid = uid, new->infos = infos,
		pthread_mutex_init(&new->my_fork, NULL), new->next = NULL);
	if (!*philo)
		return (*philo = new, TRUE);
	last = *philo;
	while (last->next)
		last = last->next;
	return (last->next = new, TRUE);
}

t_philo	*init_philos(t_philo **philo, t_infos *infos)
{
	int			uid;
	t_philo		*loop;

	uid = FALSE;
	while (++uid <= infos->philo_num)
		create_philos(philo, infos, uid);
	loop = *philo;
	while (loop->next)
		loop = loop->next;
	loop->next = *philo;
	(TRUE) && (loop = *philo, infos->start_time = get_time());
	while (loop)
	{
		pthread_create(&loop->my_thread, NULL, life_cycle, loop);
		if (loop->uid == infos->philo_num)
			break ;
		loop = loop->next;
	}
	return (loop);
}

int	parcer(int ac, char **av, t_infos *infos)
{
	int		num;
	int		index;

	infos->meals_num = ERROR;
	while (--ac)
	{
		(TRUE) && (index = ERROR, num = _atoi(av[ac]));
		while (av[ac][++index])
		{
			if (!index && av[ac][index] == '+')
				av[ac]++;
			if (!(av[ac][index] >= ZERO && av[ac][index] <= NINE))
				return (ERROR);
		}
		if (num > MPH && ac == N1)
			return (ERROR);
		if (num < MTM && (ac == N2 || ac == N3 || ac == N4))
			return (ERROR);
		(ac == N1) && (infos->philo_num = num);
		(ac == N2) && (infos->die_time = num);
		(ac == N3) && (infos->eat_time = num);
		(ac == N4) && (infos->sleep_time = num);
		(ac == N5) && (infos->meals_num = num);
	}
	return (TRUE);
}
