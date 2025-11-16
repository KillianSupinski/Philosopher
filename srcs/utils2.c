/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksupinsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:54:49 by ksupinsk          #+#    #+#             */
/*   Updated: 2025/11/16 15:41:01 by ksupinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_ressources(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_check_mutex);
	pthread_mutex_destroy(&data->state_mutex);
	pthread_mutex_destroy(&data->seat_mutex);
	free(data->forks);
}

void	print_dead(t_philo *p)
{
	t_data				*d;
	unsigned long long	ts;

	d = p->data;
	ts = (unsigned long long)(get_time_ms() - d->start_ms);
	pthread_mutex_lock(&d->print_mutex);
	printf("%llu %d died\n", ts, p->id);
	pthread_mutex_lock(&d->state_mutex);
	d->stop = 1;
	pthread_mutex_unlock(&d->state_mutex);
	pthread_mutex_unlock(&d->print_mutex);
}

void	print_all_done(t_data *d)
{
	unsigned long long	ts;

	ts = (unsigned long long)(get_time_ms() - d->start_ms);
	pthread_mutex_lock(&d->print_mutex);
	printf("%llu all philosophers have eaten enough\n", ts);
	pthread_mutex_unlock(&d->print_mutex);
}

void	safe_print(t_philo *philo, const char *message)
{
	t_data				*d;
	int					stop;
	unsigned long long	ts;

	d = philo->data;
	pthread_mutex_lock(&d->print_mutex);
	ts = (unsigned long long)(get_time_ms() - d->start_ms);
	pthread_mutex_lock(&d->state_mutex);
	stop = d->stop;
	pthread_mutex_unlock(&d->state_mutex);
	if (!stop)
		printf("%llu %d %s\n", ts, philo->id, message);
	pthread_mutex_unlock(&d->print_mutex);
}
