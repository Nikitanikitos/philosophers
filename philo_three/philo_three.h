/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 20:24:21 by imicah            #+#    #+#             */
/*   Updated: 2020/09/30 20:24:22 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>

# define FALSE	0
# define TRUE	1

typedef struct			s_table
{
	int					number_of_philo;
	int					number_of_forks;
	int					number_of_times_each_philo_must_eat;
	long int			time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	long int			start_simulation;
	sem_t				*sem_forks;
	sem_t				*sem;
}						t_table;

typedef struct			s_philo
{
	int					id;
	int					is_die;
	long int			last_lunch_time;
	int					number_of_times_philo_must_eat;
	t_table				*table;
}						t_philo;

void					table_init(t_table *table, char **av, sem_t *sem);
void					philo_init(t_philo *philo, t_table *table, int id);

void					action(t_philo *philo);
void					*check_death(void *thread_data);
void					write_status_philo(t_philo *philo, char *action);
void					ft_usleep(long int time);
void					ft_putendl_fd(char *s, int fd);
void					ft_putstr_fd(char *s, int fd);

long int				get_current_millisecond(void);
int						ft_atoi(char *nptr);
int						ft_strlen(const char *str);
int						check_arguments(int ac, char **av);

char					*ft_itoa(long int n);
char					ft_isdigit(char c);

#endif
