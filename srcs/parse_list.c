/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hescoval <hescoval@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:46:37 by hescoval          #+#    #+#             */
/*   Updated: 2024/02/10 17:24:59 by hescoval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*find_type(char *arg)
{
	if(ft_strcmp(arg, ">") == 0)
		return	ft_strdup("RD_OVERWRITE");
	if(ft_strcmp(arg, ">>") == 0)
		return	ft_strdup("RD_APPEND");
	if(ft_strcmp(arg, "<") == 0)
		return	ft_strdup("RD_INPUT");
	if(ft_strcmp(arg, "<<") == 0)
		return	ft_strdup("RD_HEREDOC");
	if(ft_strcmp(arg, "|") == 0)
		return	ft_strdup("PIPE");
	return 0;
}

t_parsed	*make_list(char **args)
{
	int	i;

	i = 0;
	t_parsed *head;
	t_parsed *helper;

	head = ft_calloc(1, sizeof(t_parsed));
	head->text = args[0];
	head->type = ft_strdup("COMMAND");
	helper = head;
	while(args[++i])
	{
		helper->next = ft_calloc(1, sizeof(t_parsed));
		helper->next->prev = helper;
		helper = helper->next;
		helper->text = ft_strdup(args[i]);
		helper->type = find_type(helper->text);
		if(helper->type == NULL)
		{
			if(ft_strcmp(helper->prev->type, "PIPE") != 0)
				helper->type = ft_strdup("STRING");
			else
				helper->type = ft_strdup("COMMAND");
		}
	}
	return(head);
}
