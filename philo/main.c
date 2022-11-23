/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:23 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/23 14:46:59 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	int	i;
	int	res;
	int	sign;
	// int	new_res;

	i = 0;
	sign = 1;
	res = 0;
	// new_res = 0;
	while (s[i] == '\f' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == ' ')
		i++;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		// new_res = res * 10 - (s[i] - '0');
		// if (new_res > res)
		// {
		// 	write(1, "Error\n", 6);
		// 	exit(1);
		// }
		// res = new_res;
		i++;
	}
	// res = do_atoi(s, i, res, new_res);
	// error_atoi(sign, res);
	return (res * sign);
}

int	ft_atol(char const *s)
{
	int	i;
	long	res;
	long	sign;
	// int	new_res;

	i = 0;
	sign = 1;
	res = 0;
	// new_res = 0;
	while (s[i] == '\f' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == ' ')
		i++;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		// new_res = res * 10 - (s[i] - '0');
		// if (new_res > res)
		// {
		// 	write(1, "Error\n", 6);
		// 	exit(1);
		// }
		// res = new_res;
		i++;
	}
	// res = do_atoi(s, i, res, new_res);
	// error_atoi(sign, res);
	return (res * sign);
}

int	do_atoi(char const *s, int i, int res, int new_res)
{	
	while (s[i] >= '0' && s[i] <= '9')
	{
		new_res = res * 10 + (s[i] - '0');
		if (new_res > res)
		{
			write(1, "Error\n", 6);
			exit(1);
		}
		res = new_res;
		i++;
	}
	return (res);
}

useconds_t	philo_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	error_atoi(int sign, int res)
{
	if (sign == 1 && res == -2147483648)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
}

pthread_t	*tab_thread(pthread_t *tab, int	nombre)
{
	tab = (pthread_t *)malloc(sizeof(pthread_t) * nombre);
	return (tab);
}

pthread_mutex_t	*tab_mutex(pthread_mutex_t *tab, int nb)
{
	tab = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb);
	if (!tab)
		return (NULL);
	return (tab);
}

// void	print_all(t_all *all)
// {
// 	printf("NUMBER OF FORK == %d\n", num_fork);
// 	printf("ACTUEL PHILOSOPHERS == %d\n", actual_philo);
// 	printf("FIRST ROUND == %d\n", first_round);
// 	int				number_eats;
// }

// pthread_mutex_t	*tab_mutex(int nb)
// {
// 	pthread_mutex_t	*tab;
// 	int				i;

// 	i = 0;
// 	tab = malloc(sizeof(pthread_mutex_t) * nb + 1);
// 	if (!tab)
// 		return (NULL);
// 	while (i < nb)
// 	{
// 		tab[i] = &pthread_mutex_init(&tab[i], NULL);
// 		i++;
// 	}
// }

useconds_t	philo_get_time(void);

int	parsing(int ac, char **av, t_all *all)
{
	int	i;

	i = 0;
	gettimeofday(&all->timeval, NULL);
	// printf("seconds : %ld micro seconds : %d\n", all->timeval.tv_sec, all->timeval.tv_usec);
	all->num_philo = ft_atoi(av[1]);
	if (all->num_philo < 0)
	{
		printf("Error: Number's Philos is negative.\n");
		return (0);
	}
	all->philo.tab_philo = tab_thread(all->philo.tab_philo, all->num_philo);
	all->philo.fork = tab_mutex(all->philo.fork, ft_atoi(av[1]));
	all->philo.time_for_dead = ft_atol(av[2]);
	printf("all->philo.time_for_dead == %ld\n", all->philo.time_for_dead);
	all->philo.fork = tab_mutex(all->philo.fork, all->num_philo);
	all->philo.time_for_eat = ft_atol(av[3]);
	all->philo.time_for_sleep = ft_atol(av[4]);
	if (ac == 6)
		all->philo.last_meal = ft_atoi(av[5]);
	// else if (ac != 6)
	// 	all->philo.last_meal = -1;
	all->num_fork = ft_atoi(av[1]);
	all->time_start = philo_get_time();
	all->actual_philo = 0;
	all->first_round = 1;
	// pthread_mutex_init(&all->philo.left_fork, NULL);
	// pthread_mutex_init(&all->philo.r_fork, NULL);
	pthread_mutex_init(&all->philo.eat_msg, NULL);
	pthread_mutex_init(&all->philo.sleep_msg, NULL);
	return (1);
}

// long	get_time(void)
// {
// 	struct timeval	tv;
// 	long			end;

// 	gettimeofday(&tv, NULL);
// 	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
// 	return (end);
// }

int	ft_usleep(useconds_t usec)
{
	useconds_t		start;
	useconds_t		after;

	start = philo_get_time();
	after = start;
	while (after - start < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = philo_get_time();
	}
	return (0);
}

void	*function(void *data)
{
	printf("Philo se reveille\n");
	// printf("Thread est mort\n");
	return ((void *)data);
}

void	*eating(void *data)
{
	printf("Philo mange\n");
	return ((void *)data);
} 


void	*routine(void *all)
{
	useconds_t	end;

	end = 0;
	if (((t_all *)(all))->first_round == 1)
		((t_all *)(all))->time_act = ((t_all *)(all))->time_start;
	else
		((t_all *)(all))->time_act = philo_get_time();
	// printf("((t_all *)(all))->actual_philo == %d\n", ((t_all *)(all))->actual_philo);
	pthread_mutex_lock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork]);
	printf("((t_all *)(all))->actual_fork == %d\n", ((t_all *)(all))->actual_fork);
	printf("pthread_mutex_lock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork]) == %d\n", pthread_mutex_lock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork]));
	printf("pthread_mutex_lock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork + 1]) == %d\n", pthread_mutex_lock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork + 1]));
	if (pthread_mutex_lock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork]) != 0)
		printf("%u %d has taken a fork\n", end, ((t_all *)(all))->actual_philo);
		// pthread_mutex_unlock(&((t_all *)(all))->philo.eat_msg);
	pthread_mutex_unlock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork]);
	if (pthread_mutex_lock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork + 1]) != 0)
		printf("%u %d has taken a fork\n", end, ((t_all *)(all))->actual_philo);
	else
	{
		ft_usleep(50);		
	}
	pthread_mutex_unlock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork + 1]);
	ft_usleep(((t_all *)(all))->philo.time_for_eat);
	// pthread_mutex_unlock(&((t_all *)(all))->philo.eat_msg);
	pthread_mutex_lock(&((t_all *)(all))->philo.eat_msg);
	printf("%u %d is eating\n", end, ((t_all *)(all))->actual_philo);
	pthread_mutex_unlock(&((t_all *)(all))->philo.eat_msg);
	// pthread_create(&((t_all *)(all))->philo.tab_philo[((t_all *)(all))->actual_fork], NULL, &routine, all);
	// if (pthread_mutex_lock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork + 1]) == 0)
	// {
	// 	pthread_mutex_lock(&((t_all *)(all))->philo.eat_msg);
	// 	printf("%u %d has taken a fork\n", end, ((t_all *)(all))->actual_philo);
	// }
	// else
	// {
	// 	ft_usleep(50);
	// 	// pthread_create(&((t_all *)(all))->philo.tab_philo[((t_all *)(all))->actual_fork], NULL, &routine, all);

	// }
	end = ((t_all *)(all))->time_act - ((t_all *)(all))->time_start;
	// printf("%u %d is eating\n", end, ((t_all *)(all))->actual_philo);
	ft_usleep(((t_all *)(all))->philo.time_for_eat);
	pthread_mutex_unlock(&((t_all *)(all))->philo.eat_msg);
	((t_all *)(all))->time_act = philo_get_time();
	((t_all *)(all))->philo.last_time = ((t_all *)(all))->time_act - ((t_all *)(all))->time_start;
	pthread_mutex_lock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork]);
	pthread_mutex_lock(&((t_all *)(all))->philo.fork[((t_all *)(all))->actual_fork + 1]);
		// pthread_mutex_unlock(&((t_all *)(all))->philo.r_fork);
	pthread_mutex_lock(&((t_all *)(all))->philo.sleep_msg);
	printf("%u %d is sleeping\n", end, ((t_all *)(all))->actual_philo);
	ft_usleep(((t_all *)(all))->philo.time_for_sleep);
	pthread_mutex_unlock(&((t_all *)(all))->philo.sleep_msg);
	printf("%u %d is thinking\n", end, ((t_all *)(all))->actual_philo);
	// if (((t_all *)(all))->philo.last_meal != -1)
	// 	((t_all *)(all))->philo.last_meal--;
	return ((void *)all);
}

void	doing_all(t_all *all)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (all->philo.tab_philo != NULL)
	{
		all->time_start = philo_get_time();
		printf("all->philo.last_meal == %d\n", all->philo.last_meal);
		if (all->philo.last_meal != 0)
		{
			while (all->philo.tab_philo[i] && y < all->philo.last_meal)
			{
				all->actual_philo = i;
				all->actual_fork = i;
				pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
				pthread_join(all->philo.tab_philo[i], NULL);
				i++;
				all->first_round = 0;
				if (i == all->num_philo)
				{
					i = 0;
					y++;
				}
			}
		}
		else
		{
			while (all->philo.tab_philo[i])
			{
				all->actual_philo = i;
				all->actual_fork = i;
				// printf("all->actual_philo - %d\n", all->actual_philo);
				pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
				// pthread_create(&all->philo.tab_philo[i], NULL, &routine2, all);
				// pthread_join(all->philo.tab_philo[i], NULL);
				// if (i % 2 == 0)
				// {
				// 	printf("0.1\n");
				// 	pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
				// }
				// else
				// {
				// 	printf("0.2\n");
				// 	pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
				// }
				i++;
				all->first_round = 0;
				if (i == all->num_philo)
				{
					i = 0;
				}
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_all	*all;

	all = malloc(sizeof(t_all *));
	all->num_philo = 0;
	if (!all)
		return (0);
	if (ac != 5 && ac != 6)
	{
		printf("Error: Missing parameters\n");
		return (0);
	}
	if (parsing(ac, av, all) == 0)
		return (0);
	doing_all(all);

	return (0);
}