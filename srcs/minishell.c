/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:24:42 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/01 10:23:41 by pabernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_minishell(void)
{
	char		*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line) 
			ft_handle_eof();
		if (!line[0])
			continue ;
		add_history(line);
		ft_parser(line);
		free(line);
	}
}
