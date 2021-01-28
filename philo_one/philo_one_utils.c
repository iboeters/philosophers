/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 11:08:19 by iboeters      #+#    #+#                 */
/*   Updated: 2021/01/28 11:04:04 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print(int philo_nr, char *text, t_table *tab)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&tab->writing);
	printf("%li %i %s\n", now.tv_usec - tab->start_program, philo_nr, text);
	pthread_mutex_unlock(&tab->writing);
}

int		ft_atoi(const char *str)
{
	unsigned long int	r;
	int					i;
	int					sign;
	unsigned long int	max_int;

	r = 0;
	i = 0;
	sign = 1;
	max_int = 922337203685477580;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1 && ((r == max_int && str[i] > '7') || (r > max_int)))
			return (-1);
		if (sign == -1 && ((r == max_int && str[i] > '8') || (r > max_int)))
			return (0);
		r = r * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (sign * r);
}
