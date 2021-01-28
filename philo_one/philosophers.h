/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 10:26:31 by iboeters      #+#    #+#                 */
/*   Updated: 2021/01/28 11:35:30 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h> //sleep
# include <stdlib.h>
# include <sys/time.h>

typedef struct		s_philosopher{
	int				nr;
	int				times_eaten;
	int				time_to_die;
	int				time_eat;
	int				time_sleep;
	int				l_fork;
	int				r_fork;
}					t_philosopher;

typedef struct		s_table{
	int				nr;
	int				n_philosophers;
	int				*input;
	int				arg_5;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	long int		start_program;
}					t_table;

int		ft_atoi(const char *str);
void	*eat_sleep_think_repeat(void *table);

#endif
