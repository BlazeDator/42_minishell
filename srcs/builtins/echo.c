/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmeirele <dmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:33:04 by dmeirele          #+#    #+#             */
/*   Updated: 2024/02/08 16:33:04 by dmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	set_values(int *quote_flag, char *quote, char *arg);
static void	ft_echo_new_line(char **array_args);

void	ft_exec_echo(char **array_args)
{
	int		i;
	int		j;
	int		flag;
	char	quote;

	i = -1;
	flag = 0;
	if (!ft_strcmp(array_args[0], "-n"))
		i++;
	while (array_args[++i])
	{
		j = -1;
		while (array_args[i][++j])
		{
			if (!flag && (array_args[i][j] == '\'' || array_args[i][j] == '\"'))
				set_values(&flag, &quote, &array_args[i][j]);
			else if (flag && array_args[i][j] == quote)
				flag = 0;
			else
				ft_printf("%c", array_args[i][j]);
		}
		if (array_args[i + 1])
			ft_printf(" ");
	}
	ft_echo_new_line(array_args);
}

static void	ft_echo_new_line(char **array_args)
{
	if (ft_strcmp(array_args[0], "-n"))
		printf("\n");
}

static void	set_values(int *quote_flag, char *quote, char *arg)
{
	*quote_flag = 1;
	*quote = *arg;
}
