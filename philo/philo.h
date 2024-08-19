/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:30:51 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/19 19:13:01 by abadouab         ###   ########.fr       */
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

# define ERROR_MSG "\033[1;31mError:\033[0m <use a valid values>"
# define USAGE_MSG "\033[1;33mUsage:\033[0m <philo_num> <die_time> <eat_time> \
<sleep_time>"

# define INIT_FAIL "\033[1;31mError:\033[0m <failed to initialize the mutex>"
# define CREATE_FAIL "\033[1;31mError:\033[0m <failed to create a new thread>"
# define ALLOC_FAIL "\033[1;31mError:\033[0m <failed to allocate memory>"

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
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
}					t_infos;

typedef struct s_philo
{
	int				tid;
	t_infos			*infos;
	time_t			last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	philo_fork;
	struct s_philo	*next;
}					t_philo;

time_t		get_time(void);
void		str_error(char *s);
void		*life_cycle(void *value);
void		cleanup(t_philo *philo, t_infos *infos);
int			parcer(int ac, char **av, t_infos *infos);
int			init_philos(t_philo **philo, t_infos *infos);
void		join_threads(t_philo *philo, t_infos *infos);
int			create_philos(t_philo *philo, t_infos *infos);
void		life_cycle_log(t_philo *philo, char *log, int mode);
long		safe_access(pthread_mutex_t *mutex, long *value,
				long new, int mode);

#endif
