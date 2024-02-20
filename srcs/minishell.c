/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:24:42 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/20 13:39:53 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_minishell(void)
{
	char	*line;
	char	*prompt;
	t_envs	*envs;

	envs = NULL;
	while (1)
	{
		prompt = ft_get_dir();
		line = readline(prompt);
		free(prompt);
		if (!envs)
			envs = return_envs(ft_create_envs());
		if (!line)
			ft_handle_eof();
		if (!line[0])
			continue ;
		add_history(line);
		ft_parser(line);
		free(line);
	}
}
