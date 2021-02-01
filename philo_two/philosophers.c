/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 10:09:29 by iboeters      #+#    #+#                 */
/*   Updated: 2021/02/01 15:43:28 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philosopher *philo, t_table *tab, int nr)
{
	philo->nr = nr;
	philo->times_eaten = 0;
	philo->time_to_die = tab->input[1];
	philo->time_to_eat = tab->input[2];
	philo->time_to_sleep = tab->input[3];
	philo->l_fork = philo->nr;
	if (philo->nr == 1)
		philo->r_fork = tab->input[0];
	else
		philo->r_fork = philo->nr - 1;
	philo->arg_5 = tab->arg_5;
	philo->last_meal = tab->start_program;
	philo->eating = 0;
	philo->dead_philo = 0;
	philo->tab = tab;
}

int		init_philosophers(t_philos *philos, t_table *tab)
{
	int	i;

	i = 0;
	philos->p = (t_philosopher *)malloc(tab->input[0] *
	sizeof(t_philosopher));
	if (!philos->p)
	{
		printf("Malloc fail\n");
		return (-1);
	}
	philos->dead_philo = 0;
	while (i < tab->input[0])
	{
		init_philo(&philos->p[i], tab, i + 1);
		i++;
	}
	return (0);
}

int		init_table(int argc, char **argv, t_table *tab)
{
	tab->input = valid_input(argc, argv);
	if (tab->input == NULL)
		return (-1);
	tab->arg_5 = 0;
	if (argc == 6)
		tab->arg_5 = 1;
	tab->threads = (pthread_t *)malloc(tab->input[0] *
	sizeof(pthread_t));
	tab->sem_forks = sem_open(SEM_NAME, O_CREAT, 0660, tab->input[0]);
	tab->writing = sem_open("writing", O_CREAT, 0660, 1);
	if (tab->sem_forks == SEM_FAILED)
	{
		printf("Error creating semaphore\n");
		return (-1);
	}
	if (!tab->threads)
	{
		printf("Malloc fail\n");
		return (-1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_table			tab;
	t_philos		philos;
	struct timeval	now;

	if (init_table(argc, argv, &tab) == -1)
		return (-1);
	sem_unlink(SEM_NAME);
	gettimeofday(&now, NULL);
	tab.start_program = now.tv_sec * 1000 + now.tv_usec / 1000;
	if (init_philosophers(&philos, &tab) == -1)
		return (-1);
	if (threading(&philos, &tab) == -1)
		return (-1);
	if (tab.input)
		free(tab.input);
	if (tab.threads)
		free(tab.threads);
	sem_unlink(SEM_NAME);
	sem_unlink("writing");
	if (sem_close(tab.sem_forks) == -1 || sem_close(tab.writing) == -1)
	{
		printf("Not a valid semaphore\n");
		return (-1);
	}
	if (philos.p)
		free(philos.p);
	return (0);
}
