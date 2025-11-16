/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksupinsk <ksupinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:39:35 by ksupinsk          #+#    #+#             */
/*   Updated: 2025/11/16 15:33:25 by ksupinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	alloc_philo_thread(t_data *data, t_philo **philos, pthread_t **threads)
{
	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
		return (0);
	*threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!*threads)
	{
		free(*philos);
		return (0);
	}
	return (1);
}

int	init_fork(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->meal_check_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->state_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->seat_mutex, NULL) != 0)
		return (0);
	return (1);
}

void	init_philo_struct(t_data *data, t_philo *philos, pthread_t *threads)
{
	int				i;
	pthread_mutex_t	*tmp;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].num_meals_eaten = 0;
		philos[i].last_meal_ms = data->start_ms;
		philos[i].data = data;
		philos[i].thread = threads[i];
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		if (philos[i].id % 2 == 0)
		{
			tmp = philos[i].left_fork;
			philos[i].left_fork = philos[i].right_fork;
			philos[i].right_fork = tmp;
		}
		i++;
	}
	data->philos = philos;
}

int	init_thread(t_data *data, t_philo *philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_philo(t_data *data)
{
	t_philo		*philos;
	pthread_t	*thread;
	pthread_t	monitor_thread;

	if (!alloc_philo_thread(data, &philos, &thread))
		return (0);
	if (!init_fork(data))
		return (0);
	init_philo_struct(data, philos, thread);
	if (init_thread(data, philos, thread) == 0)
		return (0);
	if (data->num_philos == 1)
	{
		pthread_join(thread[0], NULL);
		clean_ressources(data);
		return (free(philos), free(thread), 1);
	}
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, data) != 0)
		return (0);
	pthread_join(monitor_thread, NULL);
	join_threads(data, thread);
	clean_ressources(data);
	return (free(philos), free(thread), 1);
}
