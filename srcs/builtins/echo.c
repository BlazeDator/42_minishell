/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmeirele <dmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:33:04 by dmeirele          #+#    #+#             */
/*   Updated: 2024/02/08 22:23:03 by dmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_check_echo_arguments(char *array_args);
static void	ft_check_quotes_echo(char *array_args);
static void	ft_print_echo_space(char *array_args);
static void	ft_print_new_line(int flag_nl);

void	ft_exec_echo(char **array_args)
{
	int	i;
	int	flag_nl;
	int	option;

	i = 0;
	option = 1;
	flag_nl = 1;
	while (array_args[i])
	{
		if (ft_check_echo_arguments(array_args[i]) && option)
		{
			flag_nl = 0;
			i++;
		}
		else
			option = 0;
		if (!option)
		{
			ft_check_quotes_echo(array_args[i]);
			ft_print_echo_space(array_args[i + 1]);
			i++;
		}
	}
	ft_print_new_line(flag_nl);
}

static int	ft_check_echo_arguments(char *array_args)
{
	int	i;

	i = 0;
	if (array_args[i] == '\"')
		i++;
	if (array_args[i] != '-')
		return (0);
	i++;
	if (array_args[i] != 'n')
		return (0);
	while (array_args[i] == 'n')
		i++;
	if (array_args[i] != '\0' && array_args[i] != '\"')
		return (0);
	return (1);
}

static void	ft_check_quotes_echo(char *array_args)
{
	int		state;
	char	quote;

	state = 0;
	while (*array_args)
	{
		if (!state && (*array_args == '\'' || *array_args == '\"'))
		{
			state = 1;
			quote = *array_args;
		}
		else if (state && *array_args == quote)
			state = 0;
		else
			printf("%c", *array_args);
		array_args++;
	}
}

static void	ft_print_echo_space(char *array_args)
{
	if (array_args)
		printf(" ");
	return ;
}

static void	ft_print_new_line(int flag_nl)
{
	if (flag_nl)
		printf("\n");
	return ;
}
