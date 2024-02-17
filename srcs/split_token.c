/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:28:12 by txisto-d          #+#    #+#             */
/*   Updated: 2024/02/17 23:09:30 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_quotes_len(char *str, size_t *i, size_t *len, char quote)
{
	if (str[*i] == quote)
	{
		(*i)++;
		(*len)++;
		while (str[*i] && str[*i] != quote)
		{
			(*len)++;
			(*i)++;
		}
		if (str[*i] == quote)
		{
			(*len)++;
			(*i)++;
		}
	}
}

static size_t	ft_token_len(char *str, int *start)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = *start;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t'
		&& str[i] != '\'' && str[i] != '\"')
	{
		len++;
		i++;
	}
	if (len == 0)
		ft_quotes_len(str, &i, &len, '\"');
	if (len == 0)
		ft_quotes_len(str, &i, &len, '\'');
	if (len != 0)
		*start = i;
	return (len);
}

static void	ft_token_list(char *line, t_list *lst, int *i)
{
	size_t	len;
	int		start;

	start = 0;
	len = 0;
	while (line[start])
	{
		len = ft_token_len(line, &start);
		start -=len;
		lst->content = ft_substr(line, start, len);
		start += len;
		lst->next = ft_calloc(1, sizeof(t_list));
		if (!lst->next)
			exit(1);
		lst = lst->next;
		(*i)++;
	}
	lst->next = NULL;
}

static char	**ft_token_array(t_list *lst, int i)
{
	char	**tokens;
	int		j;

	tokens = ft_calloc(i + 1, sizeof(char *));
	if (!tokens)
		exit(1);
	j = 0;
	while (lst)
	{
		tokens[j] = lst->content;
		lst = lst->next;
		j++;
	}
	return (tokens);
}

char	**ft_split_token(char *line)
{
	t_list	*lst;
	t_list	*return_lst;
	char 	**tokens;
	int		i;

	lst = NULL;
	i = 0;
	lst = ft_calloc(1, sizeof(t_list));
	if (!lst)
		exit(1);
	return_lst = lst;
	ft_token_list(line, lst, &i);
	tokens = ft_token_array(return_lst, i);
	return (tokens);
}
