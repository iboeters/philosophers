/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_dead.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 12:55:48 by iboeters      #+#    #+#                 */
/*   Updated: 2021/09/23 18:21:52 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_done(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->p[0].tab->input[0])
	{
		if (philos->p[i].times_eaten
			!= philos->p[i].tab->input[4])
			break ;
		i++;
	}
	if (i == philos->p[0].tab->input[0])
		return (1);
	return (0);
}

int	starving(t_philos *philos, int i)
{
	long long int	now;

	now = get_time_now(philos->p[0].tab);
	if ((now - philos->p[i].last_meal)
		> philos->p[i].time_to_die)
	{
		print(&philos->p[i], "died");
		philos->dead_philo = 1;
		return (1);
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
		if ((philos->p->arg_5 == 1 && all_done(philos))
			|| philos->dead_philo == 1)
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
