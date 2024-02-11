/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hescoval <hescoval@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:37:04 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/10 18:08:49 by hescoval         ###   ########.fr       */
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

/*	t_parsed	*list;
	t_parsed	*helper;*/
	char		*help_me_god;
	char		**splitted;

	if (!ft_check_open_quotes(line))
		return ;
	if (!strncmp(line, "exit", 4))
		exit(0);
	if (!redirect_basic_check(line))
	{
		ft_printf("invalid redirect\n");
		exit(1);
	}
	if (!pipe_check(line))
	{
		exit(1);
		ft_printf("Unexpected near '|'\n");
	}
	help_me_god = pad_central(line);
	splitted = split_quotes(help_me_god, ' ');
	ft_exec_builtins(splitted);
/*	list = make_list(splitted);
	t_parsed *helper = list;
	while(helper)
	{
		ft_printf("ARGUMENT IS [%s]\n", helper->text);
		ft_printf("TYPE IS [%s]\n_________________\n", helper->type);
		helper = helper->next;
	}
	ft_printf("\n");*/
}
