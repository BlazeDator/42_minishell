/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:28 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/01 15:29:37 by pabernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_envs	*ft_create_envs(void)
{
	extern char	**environ;
	t_envs		*envs;

	envs = 0;
	while (*environ)
	{
		envs = ft_add_env(envs, ft_new_env(*environ));
		environ++;
	}
	return (envs);
}

t_envs	*ft_new_env(char *str)
{
	t_envs	*envs;
	int		len;

	envs = malloc(sizeof(t_envs));
	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	envs->key = malloc(len);
	ft_strlcpy(envs->key, str, len);
	str += (len);
	len = ft_strlen(str);
	len++;
	envs->value = malloc(len);
	ft_strlcpy(envs->value, str, len);
	envs->next = 0;
	return (envs);
}

t_envs	*ft_add_env(t_envs *envs, t_envs *new)
{
	t_envs	*start;

	start = 0;
	if (envs && new)
	{
		start = envs;
		while (envs->next)
			envs = envs->next;
		envs->next = new;
		return (start);
	}
	else if (new)
		return (new);
	return (0);
}

t_envs	*ft_del_env(t_envs *envs, char *key)
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
	if (envs->key)
		free(envs->key);
	if (envs->value)
		free(envs->value);
	free(envs);
	return (start);
}

t_envs	*ft_free_envs(t_envs *envs)
{
	t_envs	*temp;

	while (envs)
	{
		if (envs->key)
			free(envs->key);
		if (envs->value)
			free(envs->value);
		temp = envs;
		envs = envs->next;
		free(temp);
	}
	return (0);
}
