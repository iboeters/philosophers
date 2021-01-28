/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 10:09:29 by iboeters      #+#    #+#                 */
/*   Updated: 2021/01/28 11:36:39 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		*invalid_return(char *str)
{
	printf("%s\n", str);
	return (NULL);
}

int		*valid_input(int argc, char **argv)
{
	int		i;
	int		*ret;
	int		size;

	i = 0;
	if (argc < 5 || argc > 6)
		return (invalid_return("Invalid amount of arguments"));
	size = ft_atoi(argv[1]);
	if (size <= 1) // you need at least 2 forks to eat
		return (invalid_return("Invalid argument"));
	ret = (int *)malloc(argc * sizeof(int));
	if (ret == NULL)
		return (invalid_return("Malloc fail"));
	printf("Input: \n");
	while (i + 1 < argc)
	{
		ret[i] = ft_atoi(argv[i + 1]);
		if (ret[i] <= 0)
		{
			if (ret)
				free(ret);
			return (invalid_return("Invalid argument"));
		}
		printf("[%i] %i \n", i, ret[i]);
		i++;
	}
	if (i + 1 == argc)
		return (ret);
	return (NULL);
}

int		init_table(int argc, char **argv, t_table *tab)
{
	int i;

	i = 0;
	tab->nr = 0;
	tab->input = valid_input(argc, argv);
	if (tab->input == NULL)
		return (-1);
	tab->n_philosophers = tab->input[0];
	tab->arg_5 = 0;
	if (argc == 6)
		tab->arg_5 = 1;
	tab->threads = (pthread_t *)malloc(tab->input[0] *
	sizeof(pthread_t));
	tab->forks = (pthread_mutex_t *)malloc(tab->input[0] *
	sizeof(pthread_mutex_t));
	if (!tab->threads || !tab->forks)
	{
		printf("Malloc fail\n");
		return (-1);
	}
	while (i < tab->input[0])
	{
		pthread_mutex_init(&tab->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&tab->writing, NULL);
	return (0);
}

int		main(int argc, char **argv)
{
	int				i;
	t_table			tab;
	struct timeval	now;

	i = 0;
	if (init_table(argc, argv, &tab) == -1)
		return (-1);
	gettimeofday(&now, NULL);
	tab.start_program = now.tv_usec;
	printf("time start: %li\n", tab.start_program);
	while (i < tab.input[0])
	{
		pthread_create(&(tab.threads[i]), NULL,
		&eat_sleep_think_repeat, (void *)&tab);
		usleep(175);
		i++;
	}
	i = 0;
	while (i < tab.input[0])
	{
		printf("[%i] waiting...\n", i + 1);
		pthread_join(tab.threads[i], NULL); //block current threads until specified threads are finished: i.e. join all threads together
		i++;
	}
	printf("printed once\n");
	if (tab.input)
		free(tab.input);
	if (tab.threads)
		free(tab.threads);
	if (tab.forks)
		free(tab.forks);
	gettimeofday(&now, NULL);
	printf("time now: %li\n", now.tv_usec);
	printf("duration program: %li\n", now.tv_usec - tab.start_program);
	return (0);
}

/*
** set last arg to (void *)&result (and declare an int *result),
** to store result. In our program: pass a struct?
*/
