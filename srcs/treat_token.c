/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:18:21 by txisto-d          #+#    #+#             */
/*   Updated: 2024/02/19 17:00:46 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_remove_quotes(char *str);
void   ft_treating(t_parsed *tokens, char *line);

void	ft_treat_token(t_parsed *tokens, char *line)
{
	ft_expand_variables(tokens);
	ft_treating(tokens, line);
}

void   ft_treating(t_parsed *tokens, char *line)
{
	t_parsed	*aux;
	//char		*input;
	//int			token_len;

	(void) line;
	aux = tokens->next;
	//input = line;
	while (aux)
	{
		if (aux->text[0] == '\'' || aux->text[0] == '\"')
			aux->text = ft_remove_quotes(aux->text);
		aux = aux->next;
	}
}

char	*ft_remove_quotes(char *str)
{
	char	*new;
	int		len;

	len = ft_strlen(str) - 2;
	new = ft_substr(str, 1, len);
	free(str);
	return (new);
}