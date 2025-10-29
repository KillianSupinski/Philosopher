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

void safe_print(t_philo *philo, const char *message)
{
    t_data *d = philo->data;
    unsigned long long ts;

    ts = (unsigned long long)(get_time_ms() - d->start_ms);

    pthread_mutex_lock(&d->print_mutex);
    if (!d->stop)
        printf("%llu %d %s\n", ts, philo->id, message);
    pthread_mutex_unlock(&d->print_mutex);
}

// void    msleep_precise(int ms)
// {
//     uint64_t    end;

//     end = get_time_ms() + (uint64_t)ms;
//     while (get_time_ms() < end)
//         usleep(100);
// }

int action_philo(t_philo *philo)
{
    t_data *data = philo->data;

    // Take forks
    pthread_mutex_lock(philo->left_fork);
    safe_print(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    safe_print(philo, "has taken a fork");

    // Eat
    pthread_mutex_lock(&data->meal_check_mutex);
    philo->last_meal_ms = get_time_ms();
    pthread_mutex_unlock(&data->meal_check_mutex);

    safe_print(philo, "is eating");
    usleep(data->time_to_eat * 1000);         // <-- un seul sleep ici
    philo->num_meals_eaten++;

    // Put down forks
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);

    // Sleep
    safe_print(philo, "is sleeping");
    usleep(data->time_to_sleep * 1000);

    // Think
    safe_print(philo, "is thinking");
    return 1;
}
void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if(philo->data->num_philos == 1)
    {
        safe_print(philo, "has taken a fork");
        usleep(philo->data->time_to_die * 1000);
        safe_print(philo, "died");
        philo->data->stop = 1;
        return (NULL);
    }
    if (philo->id % 2 == 0)
        usleep(500);
    while(1)
    {
        pthread_mutex_lock(&philo->data->state_mutex);
        if(philo->data->stop)
        {
            pthread_mutex_unlock(&philo->data->state_mutex);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->data->state_mutex);
        if(!action_philo(philo))
            return (NULL);
        safe_print(philo, "is thinking");
    }
    return (NULL);
}

void    init_philo_struct(t_data *data, t_philo *philos, pthread_t *threads)
{
    int i;
    pthread_mutex_t *tmp;

    i = 0;
    while (i < data->num_philos)
    {
        philos[i].id = i + 1;
        philos[i].num_meals_eaten = 0;
        philos[i].last_meal_ms = 0;
        philos[i].data = data;
        philos[i].thread = threads[i];
        philos[i].left_fork  = &data->forks[i];
        philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        if (philos[i].id % 2 == 0) {
            tmp = philos[i].left_fork;
            philos[i].left_fork = philos[i].right_fork;
            philos[i].right_fork = tmp;
        }
        i++;
    }
}

int init_thread(t_data *data, t_philo *philos, pthread_t *threads)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_create(&threads[i], NULL, &philo_routine, &philos[i]) != 0)
            return (0);
        i++;
    }
    return (1);
}

int init_philo(t_data *data)
{
    t_philo     *philos;
    pthread_t   *thread;

    if (!alloc_philo_thread(data, &philos, &thread))
        return (0);
    if (!init_fork(data))
        return (0);
    init_philo_struct(data, philos, thread);
    if (init_thread(data, philos, thread) == 0)
        return (0);
    join_threads(data, thread);
    free(philos);
    free(thread);
    return (1);
}