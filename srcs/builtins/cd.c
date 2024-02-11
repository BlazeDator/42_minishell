/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmeirele <dmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:57:13 by dmeirele          #+#    #+#             */
/*   Updated: 2024/02/11 11:47:08 by dmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_update_curr_dir(t_envs *envs, char *curr_dir);
static void	ft_get_home_dir(t_envs *envs);

void	ft_exec_cd(char *args, t_envs *envs)
{
	char	curr_dir[PATH_MAX];

	if (args == NULL || !ft_strcmp(args, "~"))
	{
		ft_get_home_dir(envs);
		if (getcwd(curr_dir, sizeof(curr_dir)))
			ft_update_curr_dir(envs, curr_dir);
	}
	else if (!chdir(args))
	{
		if (getcwd(curr_dir, sizeof(curr_dir)))
			ft_update_curr_dir(envs, curr_dir);
	}
	else
		printf("cd: %s: No such file or directory\n", args);
}

static void	ft_update_curr_dir(t_envs *envs, char *curr_dir)
{
	while (envs)
	{
		if (!ft_strcmp(envs->key, "PWD"))
		{
			if (envs->value)
				free(envs->value);
			envs->value = ft_strdup(curr_dir);
		}
		envs = envs->next;
	}
}

static void	ft_get_home_dir(t_envs *envs)
{
	char	*home_dir;

	home_dir = NULL;
	while (envs)
	{
		if (!ft_strcmp(envs->key, "HOME"))
			home_dir = ft_strdup(envs->value);
		envs = envs->next;
	}
	if (!chdir(home_dir))
		return ;
}
