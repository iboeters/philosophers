/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_dead.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 12:55:48 by iboeters      #+#    #+#                 */
/*   Updated: 2021/02/02 21:30:53 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_dead(void *philosopher)
{
	t_philosopher	*philo;
	long long int	now;

	philo = (t_philosopher *)philosopher;
	while (1)
	{
		now = get_time_now(philo->tab);
		usleep(1000);
		if ((now - philo->last_meal) > philo->time_to_die)
		{
			print(philo, "died");
			exit(1);
		}
		if (philo->arg_5 == 1 && philo->times_eaten == philo->tab->input[4])
			break ;
	}
	return (NULL);
}
