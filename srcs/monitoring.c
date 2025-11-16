/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksupinsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:52:30 by ksupinsk          #+#    #+#             */
/*   Updated: 2025/11/16 15:48:17 by ksupinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_philo_dead(t_data *data, long long last, int i)
{
	if (get_time_ms() - last >= (long long)data->time_to_die)
	{
		print_dead(&data->philos[i]);
		pthread_mutex_lock(&data->state_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->state_mutex);
		return (0);
	}
	return (1);
}

int	philo_all_done(t_data *data, int done_count)
{
	if (data->meal_goal == -1)
		return (0);
	if (done_count == data->num_philos)
	{
		print_all_done(data);
		pthread_mutex_lock(&data->state_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	return (0);
}

int	state_philo(t_data *data)
{
	int			i;
	int			eaten;
	long long	last;
	int			done_count;

	i = 0;
	done_count = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_check_mutex);
		last = data->philos[i].last_meal_ms;
		eaten = data->philos[i].num_meals_eaten;
		pthread_mutex_unlock(&data->meal_check_mutex);
		if (is_philo_dead(data, last, i) == 0)
			return (0);
		if (data->meal_goal != -1 && eaten >= data->meal_goal)
			done_count++;
		i++;
	}
	if (philo_all_done(data, done_count))
		return (0);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		s;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&data->state_mutex);
		s = data->stop;
		pthread_mutex_unlock(&data->state_mutex);
		if (s)
			return (NULL);
		if (!state_philo(data))
			return (NULL);
		usleep(500);
	}
}
