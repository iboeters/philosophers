/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forking.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 14:38:37 by iboeters      #+#    #+#                 */
/*   Updated: 2021/02/02 21:42:06 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	kill_processes(t_table *tab)
{
	int		i;

	i = 0;
	while (i < tab->input[0])
	{
		kill(tab->pids[i], SIGTERM);
		i++;
	}
}

int		wait_proccesses(t_table *tab)
{
	int		i;
	int		wstat;

	i = 0;
	while (i < tab->input[0])
	{
		if (waitpid(-1, &wstat, 0) == -1)
		{
			printf("Error waiting for pids\n");
			return (-1);
		}
		if (WEXITSTATUS(wstat) == 1)
			break ;
		i++;
	}
	if (WEXITSTATUS(wstat) == 1)
		kill_processes(tab);
	return (0);
}

int		forking(t_philos *philos, t_table *tab)
{
	int			i;

	i = 0;
	while (i < tab->input[0])
	{
		philos->p[0].tab->pids[i] = fork();
		if (philos->p[0].tab->pids[i] == -1)
			printf("Forking went wrong\n");
		if (philos->p[0].tab->pids[i] == 0)
			eat_sleep_think_repeat((void *)&philos->p[i]);
		i++;
	}
	if (wait_proccesses(tab) == -1)
		return (-1);
	return (0);
}
