/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think_repeat.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 10:42:34 by iboeters      #+#    #+#                 */
/*   Updated: 2021/01/28 11:38:04 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philosopher *philo, t_table *tab)
{
	philo->nr = tab->nr + 1;
	tab->nr++;
	philo->times_eaten = 0;
	philo->time_eat = tab->input[2];
	philo->time_sleep = tab->input[3];
	philo->l_fork = philo->nr;
	if (philo->nr == 1)
		philo->r_fork = tab->input[0];
	else
		philo->r_fork = philo->nr - 1;
}

void	*eat_sleep_think_repeat(void *table)
{
	t_table			*tab;
	t_philosopher	philo;

	tab = (t_table *)table;
	init_philo(&philo, tab);
	while (1)
	{
		if (tab->arg_5 == 1 && philo.times_eaten == tab->input[4])
			break ;
		pthread_mutex_lock(&tab->forks[philo.r_fork - 1]);
		// print(philo.nr, "has taken a fork", tab);
		pthread_mutex_lock(&tab->forks[philo.l_fork - 1]);
		// print(philo.nr, "has taken a fork", tab);
		philo.time_to_die = 0;
		// print(philo.nr, "is eating", tab);
		pthread_mutex_lock(&tab->writing);
		printf("philo %i is eating with fork %i and %i| time: %i\n", philo.nr, philo.l_fork, philo.r_fork, philo.times_eaten);
		pthread_mutex_unlock(&tab->writing);
		philo.times_eaten++;
		usleep(philo.time_eat * 1000);
		pthread_mutex_unlock(&tab->forks[philo.r_fork] - 1);
		pthread_mutex_unlock(&tab->forks[philo.l_fork - 1]);
		// print(philo.nr, "is sleeping", tab);
		pthread_mutex_lock(&tab->writing);
		printf("philo %i is sleeping\n", philo.nr);
		pthread_mutex_unlock(&tab->writing);
		usleep(philo.time_sleep * 1000);
		if (tab->arg_5 == 1 && philo.times_eaten < tab->input[4])
		{
			// print(philo.nr, "is thinking", tab);
			pthread_mutex_lock(&tab->writing);
			printf("philo %i is thinking\n", philo.nr);	
			pthread_mutex_unlock(&tab->writing);
		}
	}
	return (NULL);
}
