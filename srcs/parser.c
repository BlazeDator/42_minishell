/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:37:04 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/01 14:30:43 by pabernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_check_open_quotes(char *line);

void	ft_parser(char *line)
{
	char	**temp_array;

	temp_array = ft_split(line, ' ');
	if (!ft_check_open_quotes(line))
		return ;
	if (!strncmp(line, "exit", 4))
		ft_exit();
	if (!strncmp(line, "cat", 3))
		ft_executer("/bin/cat");
	if (!strncmp(line, "ls", 2))
		ft_executer("/bin/ls");
	if (!strncmp(temp_array[0], "echo", 4))
		ft_exec_echo(&temp_array[1]);
}

int	ft_check_open_quotes(char *line)
{
	char	quote;
	int		state;

	state = 0;
	while (*line)
	{
		if (!state && (*line == '\'' || *line == '\"'))
		{
			state = 1;
			quote = *line;
		}
		else if (state && *line == quote)
			state = 0;
		line++;
	}
	if (state && write(2, "Error: Open quotes\n", 19))
		return (0);
	return (1);
}
