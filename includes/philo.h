/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksupinsk <ksupinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:55:02 by ksupinsk          #+#    #+#             */
/*   Updated: 2025/11/16 15:59:49 by ksupinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			last_param;
	int				meal_goal;
	int				seat;
	int				stop;
	long long		start_ms;
	pthread_mutex_t	*forks;
	pthread_mutex_t	seat_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_check_mutex;
	pthread_mutex_t	state_mutex;
	struct s_philo	*philos;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				num_meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal_ms;
	pthread_t		thread;
	t_data			*data;
}				t_philo;

long long	get_time_ms(void);
long		ft_atoi(const char *str);
int			ft_ispositive(char *str);
int			init_philo(t_data *data);
int			join_threads(t_data *data, pthread_t *threads);
void		safe_print(t_philo *philo, const char *message);
void		*monitor_routine(void *arg);
void		*philo_routine(void *arg);
void		clean_ressources(t_data *data);
void		print_dead(t_philo *p);
void		print_all_done(t_data *d);

#endif
