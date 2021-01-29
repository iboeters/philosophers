/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/29 10:34:36 by iboeters      #+#    #+#                 */
/*   Updated: 2021/01/29 11:29:14 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		*invalid_return(char *str)
{
	printf("%s\n", str);
	return (NULL);
}

int		*save_input(int argc, char **argv, int *ret)
{
	int i;

	i = 0;
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

int		*valid_input(int argc, char **argv)
{
	int		*ret;
	int		size;

	if (argc < 5 || argc > 6)
		return (invalid_return("Invalid amount of arguments"));
	size = ft_atoi(argv[1]);
	if (size <= 1)
		return (invalid_return("Invalid argument"));
	ret = (int *)malloc(argc * sizeof(int));
	if (ret == NULL)
		return (invalid_return("Malloc fail"));
	return (save_input(argc, argv, ret));
}
