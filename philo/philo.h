/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:30:51 by abadouab          #+#    #+#             */
/*   Updated: 2024/08/01 19:42:08 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define USAGE_MSG "\033[1;33mUsage:\033[0m <philo_number> <die_time> \
<eat_time> <sleep_time>\n"

#define ERROR_MSG "\033[1;31mError:\033[0m <>\n"
#define ERROR_MSG "\033[1;31mError:\033[0m <use a valid values>\n"
#define ERROR_MSG "\033[1;31mError:\033[0m <use a valid values>\n"

typedef struct s_philo
{
    int             id;
    struct s_philo  *left;
    struct s_philo  *right;
}                   t_philo;

typedef struct s_infos
{
    int             time_to_eat;
    int             time_to_die;
    int             time_to_sleep;
    int             number_of_times;
    int             number_of_philos;
}                   t_infos;

#endif
