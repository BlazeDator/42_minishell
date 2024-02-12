/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmeirele <dmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 22:57:18 by dmeirele          #+#    #+#             */
/*   Updated: 2024/02/10 22:57:18 by dmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_exec_builtins(char **args)
{
	t_envs	*envs;

	envs = return_envs(0);
	if (!ft_strcmp(args[0], "echo") || !ft_strcmp(args[0], "\\echo"))
		ft_exec_echo(&args[1]);
	if (!ft_strcmp(args[0], "cd") || !ft_strcmp(args[0], "\\cd"))
		ft_exec_cd(args[1], envs);
	if (!ft_strcmp(args[0], "pwd") || !ft_strcmp(args[0], "\\pwd"))
		ft_exec_pwd(envs);
	if (!ft_strcmp(args[0], "export") || !ft_strcmp(args[0], "\\export"))
		envs = ft_exec_export(envs, args[1]);
	if (!ft_strcmp(args[0], "unset") || !ft_strcmp(args[0], "\\unset"))
		envs = ft_exec_unset(envs, args[1]);
	if (!ft_strcmp(args[0], "env") || !ft_strcmp(args[0], "\\env"))
		ft_exec_env(envs);
	if (!ft_strcmp(args[0], "exit") || !ft_strcmp(args[0], "\\exit"))
		ft_exit();
}
