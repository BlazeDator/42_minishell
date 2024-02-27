/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:28 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/26 22:19:15 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_executer(char *command, char **new_array,
		char **array_env, t_parsed *tokens)
{
	ft_restore_signals();
	if (execve(command, new_array, array_env) == -1)
	{
		free_splits(new_array);
		free_splits(array_env);
		free(command);
		ft_exit(tokens);
	}
}
