/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:30:51 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/12 21:54:18 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define READ 0
# define WRITE 1
# define INCR 2

# define LOCK 0
# define UNLOCK 1

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

# define ERROR_MSG "\033[1;31mError:\033[0m <use a valid values>\n"
# define FAILED_MSG "\033[1;31mError:\033[0m <use a valid values>\n"
# define USAGE_MSG "\033[1;33mUsage:\033[0m <philo_num> <die_time> <eat_time> \
<sleep_time>\n"

# define JOIN_FAIL "\033[1;31mError:\033[0m <failed to join the thread>\n"
# define INIT_FAIL "\033[1;31mError:\033[0m <failed to initialize the mutex>\n"
# define LOCK_FAIL "\033[1;31mError:\033[0m <failed to lock the mutex>\n"
# define UNLOCK_FAIL "\033[1;31mError:\033[0m <failed to lock the mutex>\n"
# define CREATE_FAIL "\033[1;31mError:\033[0m <failed to create a new thread>\n"
# define ALLOC_FAIL "\033[1;31mError:\033[0m <failed to allocate memory>\n"

typedef struct s_infos
{
	int				philo_num;
	int				meals_num;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	long			philo_dead;
	long			philos_full;
	time_t			start_time;
}					t_infos;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	t_infos			*infos;
	time_t			last_meal;
	struct s_philo	*next;
}					t_philo;

time_t		get_time(void);
void		str_error(char *s);
void		*life_cycle(void *value);
int			life_cycle_log(t_philo *philo, char *log, int mode);
int			parcer(int ac, char **av, t_infos *infos);
int			init_philos(t_philo **philo, t_infos *infos);
long		safe_access(pthread_mutex_t *mutex, long *value,
				long new, int mode);
int			protected_lock(pthread_mutex_t *mutex1, pthread_mutex_t *mutex2,
				int mode);
void		cleanup(t_philo *philo, t_infos *infos);
int			create_philos(t_philo *philo, t_infos *infos);

#endif
