/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksupinsk <ksupinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:39:35 by ksupinsk          #+#    #+#             */
/*   Updated: 2025/10/22 13:39:37 by ksupinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int alloc_philo_thread(t_data *data, t_philo **philos, pthread_t **threads)
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

int init_fork(t_data *data)
{
    int i;

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
    return (1);
}

void    safe_print(t_philo *philo, char *message)
{
    t_data      *d;

    d = philo->data;
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->stop)
        printf("%llu %d %s\n", d->start_ms, philo->id, message);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void    msleep_precise(int ms)
{
    uint64_t    end;

    end = get_time_ms() + (uint64_t)ms;
    while (get_time_ms() < end)
        usleep(100);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    
    return (NULL);
}

int init_philo_struct(t_data *data, t_philo *philos, pthread_t *threads)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        philos[i].id = i + 1;
        philos[i].num_meals_eaten = 0;
        philos[i].last_meal_ms = 0;
        philos[i].data = data;
        if (pthread_create(&threads[i], NULL, &philo_routine, &philos[i]) != 0)
            return (0);
        philos[i].thread = threads[i];
        i++;
    }
    return (1);
}

int init_philo(t_data *data)
{
    t_philo     *philos;
    pthread_t   thread;

    if (!alloc_philo_thread(data, &philos, &thread))
        return (0);
    if (!init_fork(data))
        return (0);
    if (init_philo_struct(data, philos, thread) == 0)
        return (0);
    
}