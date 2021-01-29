/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think_repeat.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 10:42:34 by iboeters      #+#    #+#                 */
/*   Updated: 2021/01/29 14:44:11 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		all_done(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->p[0].tab->input[0])
	{
		if (philos->p[i].times_eaten !=
		philos->p[i].tab->input[4])
			break ;
		i++;
	}
	if (i == philos->p[0].tab->input[0])
		return (1);
	return (0);
}

int		starving(t_philos *philos, int i)
{
	long long int	now;

	now = get_time_now(philos->p[0].tab);
	if (philos->p[i].eating == 0)
	{
		if ((now - philos->p[i].last_meal) >
		philos->p[i].time_to_die)
		{
			print(&philos->p[i], "died");
			philos->dead_philo = 1;
			return (1);
		}
	}
	return (0);
}

void	*check_dead(void *philosophers)
{
	t_philos		*philos;
	int				i;

	philos = (t_philos *)philosophers;
	while (1)
	{
		i = 0;
		while (i < philos->p[0].tab->input[0])
		{
			if (starving(philos, i))
				break ;
			i++;
		}
		if ((philos->p->arg_5 == 1 && all_done(philos)) ||
		philos->dead_philo == 1)
			break ;
	}
	i = 0;
	while (i < philos->p[0].tab->input[0])
	{
		philos->p[i].dead_philo = philos->dead_philo;
		i++;
	}
	return (NULL);
}

void	eat(t_philosopher *philo)
{
	philo->eating = 1;
	print(philo, "is eating");
	philo->times_eaten++;
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->tab->forks[philo->r_fork] - 1);
	pthread_mutex_unlock(&philo->tab->forks[philo->l_fork - 1]);
	philo->last_meal = get_time_now(philo->tab);
	philo->eating = 0;
}

void	*eat_sleep_think_repeat(void *p)
{
	t_philosopher		*philo;

	philo = (t_philosopher *)p;
	while (philo->dead_philo != 1 &&
	!(philo->arg_5 == 1 && philo->times_eaten == philo->tab->input[4]))
	{
		pthread_mutex_lock(&philo->tab->forks[philo->r_fork - 1]);
		if (philo->dead_philo == 1)
			break ;
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->tab->forks[philo->l_fork - 1]);
		if (philo->dead_philo == 1)
			break ;
		print(philo, "has taken a fork");
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
