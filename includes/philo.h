#ifndef PHILO_H
#define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>



typedef struct  s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    bool            last_param;
    int             meal_goal;
    volatile int    stop;
    uint64_t        start_ms;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t meal_check_mutex;
    pthread_mutex_t state_mutex;
}                   t_data;

typedef struct s_philo
{
    int             id;
    int             num_meals_eaten;
    pthread_mutex_t  *left_fork;
    pthread_mutex_t  *right_fork;
    uint64_t        last_meal_ms;
    pthread_t       thread;
    t_data         *data;
}               t_philo;

long long	get_time_ms(void);
long    ft_atoi(const char *str);
int     ft_ispositive(char *str);
int init_philo(t_data *data);
int join_threads(t_data *data, pthread_t *threads);
#endif