/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:12:17 by txisto-d          #+#    #+#             */
/*   Updated: 2024/02/19 15:50:09 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	ft_check_quotes_and_exp(char *str);
static int	ft_before_exp(char *str);
static void	ft_expanding(t_parsed *tokens, char *new, char *tmp, t_envs *envs);
static int	ft_key_len(char *str);

t_parsed	*ft_expand_variables(t_parsed *tokens)
{
    char		*new;
	char		*tmp;
	t_envs		*envs;
	t_parsed	*aux;

	aux = tokens;
    while (aux && aux->text)
    {
        while (ft_check_quotes_and_exp(aux->text))
        {
			envs = return_envs(0);
			new = NULL;
			tmp = NULL;
			ft_expanding(aux, new, tmp, envs);
        }
		aux = aux->next;
    }
    return (tokens);
}

static void	ft_expanding(t_parsed *tokens, char *new, char *tmp, t_envs *envs)
{
	int		klen;
	int		before_len;

	before_len = ft_before_exp(tokens->text);
	klen = ft_key_len(tokens->text);
	tmp = ft_substr(tokens->text, 0, before_len);
	while (envs && ft_strnstr(tokens->text, envs->key, before_len + klen + 1) == NULL)
		envs = envs->next;
	if (envs)
	{
		new = ft_strjoin(tmp, envs->value);
		klen = ft_before_exp(tokens->text) + ft_strlen(envs->key) + 1;
		free(tmp);
		tmp = ft_substr(tokens->text, klen, ft_strlen(tokens->text) - klen);
		free(tokens->text);
		tokens->text = ft_strjoin(new, tmp);
		free(new);
		free(tmp);
	}
	else
	{
		klen = ft_key_len(tokens->text);
		klen = ft_before_exp(tokens->text) + ft_key_len(tokens->text) + 1;
		new = ft_strjoin(tmp, (tokens->text + klen));
		free(tmp);
		free(tokens->text);
		tokens->text = new;
	}
}

static int	ft_key_len(char *str)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
	{
		i++;
	}
	while (str[i] && str[i] != ' ' && str[i] != '\t'
		&& str[i] != '\'' && str[i] != '\"' && str[i] != '$')
		{
			i++;
			j++;
		}
	return (j);
}

static int	ft_before_exp(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}

static int        ft_check_quotes_and_exp(char *str)
{
    int    i;

    i = 0;
    if (str[0] == '\'')
        return (0);
    while(str[i])
    {
        if (str[i] == '$' && !str[i + 1])
            return (0);
        else if (str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}
