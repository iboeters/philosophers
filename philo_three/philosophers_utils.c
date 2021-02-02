/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 11:08:19 by iboeters      #+#    #+#                 */
/*   Updated: 2021/02/01 15:38:55 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long int	get_time_now(t_table *tab)
{
	struct timeval	now;
	int				ret;

	ret = gettimeofday(&now, NULL);
	if (ret == -1)
	{
		sem_wait(tab->writing);
		printf("Gettimeofday() failed\n");
		sem_post(tab->writing);
		return (0);
	}
	return ((now.tv_sec * 1000) + now.tv_usec / 1000);
}

void			print(t_philosopher *philo, char *text)
{
	long long int	now;

	now = get_time_now(philo->tab);
	sem_wait(philo->tab->writing);
	if (philo->eating == 1)
		printf("%lli %i %s [%i]\n", now - philo->tab->start_program, philo->nr,
		text, philo->times_eaten);
	else
		printf("%lli %i %s\n", now - philo->tab->start_program, philo->nr,
		text);
	sem_post(philo->tab->writing);
}

void			check_sign(const char *str, int *i, int *sign)
{
	if (str[*i] == '-')
		*sign = -1;
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
	return ;
}

int				ft_atoi(const char *str)
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
	check_sign(str, &i, &sign);
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
