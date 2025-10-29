/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksupinsk <ksupinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:40:30 by ksupinsk          #+#    #+#             */
/*   Updated: 2025/10/22 13:40:32 by ksupinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int parsing_args(int argc, char **argv, t_data *data)
{
    int i;

    i = 1;

    if (argc != 5 && argc != 6)
    {
        printf("Error: Invalid number of arguments\n");
        return (1);
    }
    while (i < argc)
    {
        if (ft_ispositive(argv[i]) == 0)
        {
            printf("Error: All arguments must be positive integers\n");
            return (0);
        }
        i++;
    }
    if (argc == 6)
        data->last_param = 1;
    else
        data->last_param = 0;
    return (1);
}

void init_data(t_data *data, char **argv)
{
    data->num_philos = (int)ft_atoi(argv[1]);
    data->time_to_die = (int)ft_atoi(argv[2]);
    data->time_to_eat = (int)ft_atoi(argv[3]);
    data->time_to_sleep = (int)ft_atoi(argv[4]);
    if (data->last_param)
        data->meal_goal = (int)ft_atoi(argv[5]);
    else
        data->meal_goal = -1;
    data->stop = 0;
    if (data->num_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
        || data->time_to_sleep < 0 || (data->last_param && data->stop < 0))
    {
        printf("Error: Invalid argument values\n");
        return ;
    }
}

int main(int argc, char **argv)
{
    t_data data;

    memset(&data, 0, sizeof(t_data));
    if (argc != 5 && argc != 6)
    {
        printf("Error: Invalid number of arguments\n");
        return (1);
    }
    if (!parsing_args(argc, argv, &data))
        return (1);
    init_data(&data, argv);
    data.start_ms = get_time_ms();
    if(!init_philo(&data))
    {
        write(2, "Error: Initialization failed\n", 30);
        return (1);
    }
    return (0);
}
