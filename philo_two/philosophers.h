/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 10:26:31 by iboeters      #+#    #+#                 */
/*   Updated: 2021/02/01 17:10:30 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct			s_table{
	int					*input;
	int					arg_5;
	pthread_t			*threads;
	sem_t				*sem_forks;
	sem_t				*writing;
	long long int		start_program;
}						t_table;

typedef struct			s_philosopher{
	int					nr;
	int					times_eaten;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					l_fork;
	int					r_fork;
	int					arg_5;
	long long int		last_meal;
	int					eating;
	int					dead_philo;
	t_table				*tab;
}						t_philosopher;

typedef struct			s_philos{
	t_philosopher		*p;
	pthread_t			thread_dead;
	int					dead_philo;
}						t_philos;

int						ft_atoi(const char *str);
void					*eat_sleep_think_repeat(void *philosopher);
long long int			get_time_now(t_table *tab);
void					*check_dead(void *philosophers);
void					print(t_philosopher *philo, char *text);
int						*valid_input(int argc, char **argv);
int						threading(t_philos *philos, t_table *tab);

#endif
