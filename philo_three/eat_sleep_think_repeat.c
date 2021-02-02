/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think_repeat.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/28 10:42:34 by iboeters      #+#    #+#                 */
/*   Updated: 2021/02/02 21:39:10 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philosopher *philo)
{
	sem_wait(philo->tab->sem_forks);
	print(philo, "has taken a fork");
	sem_wait(philo->tab->sem_forks);
	print(philo, "has taken a fork");
	philo->eating = 1;
	print(philo, "is eating");
	philo->times_eaten++;
	philo->last_meal = get_time_now(philo->tab);
	usleep(philo->time_to_eat * 1000);
	sem_post(philo->tab->sem_forks);
	sem_post(philo->tab->sem_forks);
	philo->eating = 0;
}

void	join_threads(t_philosopher *philo)
{
	if (pthread_join(philo->thread_dead, NULL) != 0)
	{
		printf("Error joining threads\n");
		exit(1);
	}
}

void	*eat_sleep_think_repeat(void *p)
{
	t_philosopher		*philo;

	philo = (t_philosopher *)p;
	if (pthread_create(&(philo->thread_dead), NULL, &check_dead,
	(void*)(philo)) != 0)
	{
		printf("Error creating threads\n");
		return (NULL);
	}
	while (!(philo->arg_5 == 1 &&
	philo->times_eaten == philo->tab->input[4]))
	{
		eat(philo);
		if (philo->tab->arg_5 == 1 &&
		philo->times_eaten == philo->tab->input[4])
			break ;
		print(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		print(philo, "is thinking");
	}
	join_threads(philo);
	exit(0);
	return (NULL);
}
