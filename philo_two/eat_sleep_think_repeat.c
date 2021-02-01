/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think_repeat.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 10:42:34 by iboeters      #+#    #+#                 */
/*   Updated: 2021/02/01 15:16:21 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philosopher *philo)
{
	philo->eating = 1;
	print(philo, "is eating");
	philo->times_eaten++;
	usleep(philo->time_to_eat * 1000);
	sem_post(philo->tab->sem_forks);
	sem_post(philo->tab->sem_forks);
	philo->eating = 0;
}

int		take_forks(t_philosopher *philo)
{
	sem_wait(philo->tab->sem_forks);
	if (philo->dead_philo == 1)
		return (1);
	print(philo, "has taken a fork");
	sem_wait(philo->tab->sem_forks);
	if (philo->dead_philo == 1)
		return (1);
	print(philo, "has taken a fork");
	return (0);
}

void	*eat_sleep_think_repeat(void *p)
{
	t_philosopher		*philo;

	philo = (t_philosopher *)p;
	while (philo->dead_philo != 1 &&
	!(philo->arg_5 == 1 && philo->times_eaten == philo->tab->input[4]))
	{
		if (take_forks(philo))
			break ;
		eat(philo);
		if (philo->dead_philo == 1 ||
		(philo->tab->arg_5 == 1 && philo->times_eaten == philo->tab->input[4]))
			break ;
		print(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		if (philo->dead_philo == 1)
			break ;
		print(philo, "is thinking");
	}
	return (NULL);
}
