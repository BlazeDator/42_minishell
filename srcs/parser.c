/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:37:04 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/20 13:41:07 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	pipe_check(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|' && !quotes_open(line, i))
		{
			if (i == 0)
				return (0);
			if (line[i + 1] == '\0')
				return (0);
			if (i != 0 && (line[i - 1] == '|' || line[i + 1] == '|'))
				return (0);
		}
	}
	return (1);
}

int	redirect_basic_check(char *line)
{
	int	i;
	int	count;

	i = -1;
	while (line[++i])
	{
		count = 0;
		if (find_char(line[i], "><") && !quotes_open(line, i))
		{
			while (line[i] && find_char(line[i], "><"))
			{
				if (find_char(line[i + 1], "><") && line[i + 1] != line[i])
					return (0);
				count++;
				i++;
			}
		}
		if (count > 2)
			return (0);
	}
	return (1);
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

void	ft_parser(char *line)
{
	t_parsed	*tokens;
	char		*help_hugo_god;

	if (!ft_check_open_quotes(line))
		return ;
	if (!redirect_basic_check(line))
	{
		ft_printf("invalid redirect\n");
		exit(1);
	}
	if (!pipe_check(line))
	{
		ft_printf("Unexpected near '|'\n");
		exit(1);
	}
	help_hugo_god = pad_central(line);
	tokens = ft_split_token(help_hugo_god);
	ft_treat_token(tokens, help_hugo_god);
	free(help_hugo_god);
	ft_exec_builtins(tokens);
	ft_free_tokens(tokens);
}

void	ft_free_tokens(t_parsed *tokens)
{
	t_parsed	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->text);
		free(tokens);
		tokens = tmp;
	}
}
