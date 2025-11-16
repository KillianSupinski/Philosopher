/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksupinsk <ksupinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:40:39 by ksupinsk          #+#    #+#             */
/*   Updated: 2025/11/16 15:44:25 by ksupinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_ispositive(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	nb;
	int		n;

	i = 0;
	nb = 0;
	n = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -n;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * n);
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

int	join_threads(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (1);
}
