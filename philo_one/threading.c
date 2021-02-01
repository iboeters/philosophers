/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threading.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 14:38:37 by iboeters      #+#    #+#                 */
/*   Updated: 2021/02/01 12:49:20 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		join_threads(t_philos *philos, t_table *tab)
{
	int			i;

	i = 0;
	while (i < tab->input[0])
	{
		if (pthread_join(tab->threads[i], NULL) != 0)
		{
			printf("Error joining threads\n");
			return (-1);
		}
		i++;
	}
	if (pthread_join(philos->thread_dead, NULL) != 0)
	{
		printf("Error joining threads\n");
		return (-1);
	}
	return (0);
}

int		threading(t_philos *philos, t_table *tab)
{
	int			i;

	i = 0;
	while (i < tab->input[0])
	{
		if (pthread_create(&(tab->threads[i]), NULL,
		&eat_sleep_think_repeat, (void *)&(philos->p[i])) != 0)
		{
			printf("Error creating threads\n");
			return (-1);
		}
		i++;
	}
	if (pthread_create(&(philos->thread_dead), NULL, &check_dead,
	(void*)(philos)) != 0)
	{
		printf("Error creating threads\n");
		return (-1);
	}
	if (join_threads(philos, tab) == -1)
		return (-1);
	return (0);
}
