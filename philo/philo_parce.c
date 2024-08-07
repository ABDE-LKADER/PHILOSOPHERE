/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:10:42 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/06 21:15:21 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

time_t	get_time(void)
{
	struct timeval	time;

	return (gettimeofday(&time, NULL),
		(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static int	create_philos(t_philo **philo, t_infos *infos, int tid)
{
	t_philo		*new;
	t_philo		*last;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (ERROR);
	(TRUE) && (new->tid = tid, new->infos = infos,
		pthread_mutex_init(&new->my_fork, NULL),
		pthread_mutex_init(&new->safe_check, NULL),
		new->next = NULL);
	if (!*philo)
		return (*philo = new, TRUE);
	last = *philo;
	while (last->next)
		last = last->next;
	return (last->next = new, TRUE);
}

t_philo	*init_philos(t_philo **philo, t_infos *infos)
{
	int			tid;
	t_philo		*loop;

	(TRUE) && (tid = FALSE, pthread_mutex_init(&infos->print_lock, NULL),
		pthread_mutex_init(&infos->check_philo, NULL));
	while (++tid <= infos->philo_num)
		create_philos(philo, infos, tid);
	loop = *philo;
	while (loop->next)
		loop = loop->next;
	loop->next = *philo;
	(TRUE) && (loop = *philo, infos->start_time = get_time());
	while (loop)
	{
		loop->last_meal = get_time();
		pthread_create(&loop->my_thread, NULL, life_cycle, loop);
		if (loop->tid == infos->philo_num)
			break ;
		loop = loop->next;
	}
	return (loop);
}

int	parcer(int ac, char **av, t_infos *infos)
{
	int		num;
	int		index;

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
