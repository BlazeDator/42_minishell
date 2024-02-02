/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:00:28 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/01 15:29:37 by pabernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_executer(char *path)
{
	char **test;
	extern char **environ;

	test = malloc(sizeof(char *) * 2);
	test[0] = ft_strdup("Minishell");
	test[1] = ft_strdup("");
	if (fork() == 0)
	{
		ft_restore_signals();
		execve(path, test, environ);
		exit(0);
	}
	ft_ignore_signals();
	wait(0);
	if (g_signal == SIGINT || g_signal == SIGQUIT)
		printf("\n");
	rl_on_new_line();
	ft_init_signals();
	free(test[0]);
	free(test[1]);
	free(test);
}