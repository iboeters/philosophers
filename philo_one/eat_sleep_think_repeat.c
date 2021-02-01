/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think_repeat.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 10:42:34 by iboeters      #+#    #+#                 */
/*   Updated: 2021/02/01 16:41:25 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philosopher *philo)
{
	philo->eating = 1;
	print(philo, "is eating");
	philo->times_eaten++;
	philo->last_meal = get_time_now(philo->tab);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->tab->forks[philo->r_fork] - 1);
	pthread_mutex_unlock(&philo->tab->forks[philo->l_fork - 1]);
	philo->eating = 0;
}

int		take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->tab->forks[philo->r_fork - 1]);
	if (philo->dead_philo == 1)
		return (1);
	print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->tab->forks[philo->l_fork - 1]);
	if (philo->dead_philo == 1)
		return (1);
	print(philo, "has taken a fork");
	return (0);
}

void	*eat_sleep_think_repeat(void *p)
{
	t_philosopher		*philo;

	philo = (t_philosopher *)p;
	if (philo->nr % 2 == 0)
		usleep(175);
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
