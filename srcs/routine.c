/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksupinsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:52:18 by ksupinsk          #+#    #+#             */
/*   Updated: 2025/11/16 15:54:00 by ksupinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	seat_mutex(t_data *data)
{
	int	i;
	int	s;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->state_mutex);
		s = data->stop;
		pthread_mutex_unlock(&data->state_mutex);
		if (s)
			return (0);
		pthread_mutex_lock(&data->seat_mutex);
		if (data->seat > 0)
		{
			data->seat--;
			pthread_mutex_unlock(&data->seat_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->seat_mutex);
		usleep(200);
	}
}

void	release_seat_mutex(t_data *data)
{
	pthread_mutex_lock(&data->seat_mutex);
	data->seat++;
	pthread_mutex_unlock(&data->seat_mutex);
}

int	action_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (!seat_mutex(data))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(&data->meal_check_mutex);
	philo->last_meal_ms = get_time_ms();
	pthread_mutex_unlock(&data->meal_check_mutex);
	safe_print(philo, "is eating");
	usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&data->meal_check_mutex);
	philo->num_meals_eaten++;
	pthread_mutex_unlock(&data->meal_check_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	release_seat_mutex(data);
	safe_print(philo, "is sleeping");
	usleep(data->time_to_sleep * 1000);
	if (data->num_philos % 2 == 1)
		usleep((data->time_to_eat / 2) * 1000);
	return (safe_print(philo, "is thinking"), 1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		safe_print(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		safe_print(philo, "died");
		pthread_mutex_lock(&philo->data->state_mutex);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->state_mutex);
		if (philo->data->stop)
			return (pthread_mutex_unlock(&philo->data->state_mutex), NULL);
		pthread_mutex_unlock(&philo->data->state_mutex);
		if (!action_philo(philo))
			return (NULL);
	}
	return (NULL);
}
