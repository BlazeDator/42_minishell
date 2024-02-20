/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmeirele <dmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:20:20 by dmeirele          #+#    #+#             */
/*   Updated: 2024/02/12 12:20:20 by dmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_envs	*ft_exec_unset(t_envs *envs, char *key)
{
	t_envs	*start;
	t_envs	*last;

	start = envs;
	last = envs;
	if (!ft_strcmp(key, envs->key))
		start = envs->next;
	else
	{
		while (envs && ft_strcmp(key, envs->key))
		{
			last = envs;
			envs = envs->next;
		}
		if (envs)
			last->next = envs->next;
	}
	if (!envs)
		return (start);
	free(envs->key);
	free(envs->value);
	free(envs);
	return_envs(start);
	return (start);
}
