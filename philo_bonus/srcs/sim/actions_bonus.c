/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:25:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 20:32:59 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	// printf("philo %d tries to get fork\n", philo->id);
	sem_wait(philo->utensils);
	philo_action(philo, FORK);
	if (philo->data->n_philo == 1)
	{
		printf("philo %d dies of loneliness... what a loser\n", philo->id);
		philo_wait(philo, philo->data->times[DIE]);
		sem_post(philo->utensils);
		exit(1) ;
	}
	sem_wait(philo->utensils);
	philo_action(philo, FORK);
	philo_action(philo, EAT);
	philo_wait(philo, philo->data->times[EAT]);
	set_time(philo, DEATH);
	sem_post(philo->utensils);
	sem_post(philo->utensils);
}

void	philo_wait(t_philo *philo, int ms)
{
	long	end;

	end = philo->cur + ms;
	while (set_time(philo, CUR) < end)
	{
		sem_wait(philo->lock);
		if (philo->cur > philo->tod || philo->data->ended)
		{
			sem_post(philo->lock);
			philo_action(philo, DIE);
			return ;
		}
		sem_post(philo->lock);
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

	sem_wait(philo->lock);
	// printf("philo %d got lock\n", philo->id);
	if (philo->data->ended == 0) // && philo->data->active > 1)
	{
		printf("%lu %d %s\n", set_time(philo, CUR), philo->id,
			actions[action]);
		if (action == DIE)
		{
			philo->data->ended = 1;
			return ;
		}
	}
	// printf("philo %d releases lock\n", philo->id);
	sem_post(philo->lock);
}
