/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hescoval <hescoval@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:24:42 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/08 04:41:59 by hescoval         ###   ########.fr       */
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
