/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 10:09:29 by iboeters      #+#    #+#                 */
/*   Updated: 2021/01/25 11:11:00 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //sleep
#include "philo_one.h"
#include <stdlib.h>

void	*print1(void *v)
{
	int i;

	i = 4;
	while (i < 8)
	{
		printf("1| %i\n", i);
		sleep(2);
		i++;
	}
	(void)v;
	return (NULL);
}

void	*print2(void *v)
{
	int i;

	i = 0;
	(void)v;
	while (i < 4)
	{
		printf("2| %i\n", i);
		sleep(1);
		i++;
	}
	return (NULL);
}

int		*valid_input(int argc, char **argv)
{
	int		i;
	int		*ret;
	int		size;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Invalid amount of arguments\n");
		return (NULL);
	}
	size = ft_atoi(argv[1]);
	if (size <= 0)
	{
		printf("Invalid arguments\n");
		return (NULL);
	}
	ret = (int *)malloc(size * sizeof(int));
	while (i + 1 < argc)
	{
		ret[i] = ft_atoi(argv[i + 1]);
		if (ret[i] <= 0)
		{
			printf("Invalid arguments\n");
			return (NULL);
		}
		i++;
	}
	if (i + 1 == argc)
		return (ret);
	return (NULL);
}

int		main(int argc, char **argv)
{
	pthread_t	*philosophers;
	int			i;
	int			*input;

	i = 0;
	input = valid_input(argc, argv);
	if (input == NULL)
		return (-1);
	philosophers = (pthread_t *)malloc(input[0] * sizeof(pthread_t));
	while (i < input[0])
	{
		pthread_create(&(philosophers[i]), NULL, print1, NULL);
		i++;
	}
	print2(NULL);
	i = 0;
	while (i < input[0])
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
	if (input)
		free(input);
	if (philosophers)
		free(philosophers);
	return (0);
}

/*
** set last arg to (void *)&result (and declare an int *result),
** to store result. In our program: pass a struct?
*/
