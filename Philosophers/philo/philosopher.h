#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>

typedef enum e_state{
	ERROR = -1,
	FAIL = 0,
	SUCCESS = 1,
}			t_state;

typedef enum e_cond{
	DEAD,
	FULL,
	TAKE_FORK,
	PUT_FORK,
	EATING,
	SLEEPING,
	THINKING,
}			t_cond;

typedef struct s_fork{
	int				id;
	pthread_mutex_t	fork;
}				t_fork;

typedef struct s_info{
	bool			flag;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_to_eat;
	int				total_eat_count;
	long long		start_time;
	t_fork			*fork;
	pthread_mutex_t	active;
	pthread_mutex_t	print;
}				t_info;

typedef struct s_philo{
	int			id;
	int			eat_count;
	int			l_fork;
	int			r_fork;
	long long	last_time;
	t_info		*info;
}			t_philo;

typedef struct s_set{
	t_philo	*philo;
	t_fork	*fork;
	t_info	*info;
}			t_set;

//////////////free_check/////////////////
int			free_set(t_set *set, int r);
void		free_ptr(void **ptr);
int			eat_check(t_philo *philo);
int			t_usleep(long long begin, long long time);

//////////////init/////////////////
t_set		*init(int argc, char **argv);
t_fork		*init_fork(t_info *info);
t_philo		*init_philo(t_info *info);
t_info		*init_info(int argc, char **argv);

//////////////time_to/////////////////
long long	get_time(void);
int			time_to_think(t_philo *philo);
int			time_to_sleep(t_philo *philo);
int			time_to_eat(t_philo *p);
void		print_text(t_philo *philo, t_cond cond, long long time, int id);

///////////////philosopher//////////
void		create_philo_main(t_set *set);
void		*thread_function(void *p);

///////////////util////////////////
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
#endif