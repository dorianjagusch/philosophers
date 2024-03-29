/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:25:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/16 16:25:16 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	philo_action(philo, FORK);
	if (philo->data->n_philo == 1)
	{
		philo_wait(philo, philo->data->times[DIE]);
		pthread_mutex_unlock(philo->fork1);
		return ;
	}
	pthread_mutex_lock(philo->fork2);
	philo_action(philo, FORK);
	philo_action(philo, EAT);
	philo_wait(philo, philo->data->times[EAT]);
	set_time(philo, DEATH);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

void	philo_wait(t_philo *philo, int ms)
{
	long	end;

	end = philo->cur + ms;
	while (set_time(philo, CUR) < end)
	{
		pthread_mutex_lock(&(philo->data->lock[DATA]));
		if (philo->cur > philo->tod || philo->data->ended)
		{
			pthread_mutex_unlock(&(philo->data->lock[DATA]));
			philo_action(philo, DIE);
			return ;
		}
		pthread_mutex_unlock(&(philo->data->lock[DATA]));
		usleep(200);
	}
	return ;
}

void	philo_action(t_philo *philo, int action)
{
	const char	*actions[] = {
		"died",
		"is eating",
		"is sleeping",
		"is thinking",
		"has taken a fork"
	};

	pthread_mutex_lock(&(philo->data->lock[DATA]));
	if (philo->data->ended == 0 && philo->data->active > 1)
	{
		printf("%lu %d %s\n", set_time(philo, CUR), philo->id,
			actions[action]);
		if (action == DIE)
			philo->data->ended = 1;
	}
	pthread_mutex_unlock(&(philo->data->lock[DATA]));
}
