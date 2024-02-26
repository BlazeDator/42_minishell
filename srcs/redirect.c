/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:08:49 by txisto-d          #+#    #+#             */
/*   Updated: 2024/02/26 19:57:02 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	ft_overwrite(t_parsed **aux, t_parsed **tokens, int num_com);
static int	ft_append(t_parsed **aux, t_parsed **tokens, int num_com);
static int	ft_input(t_parsed **aux, t_parsed **tokens, int num_com);
static int	ft_heredoc(t_parsed **aux, t_parsed **tokens, int num_com);

int	ft_redirect(t_parsed **tokens, int num_com)
{
	t_parsed	*aux;
	int			fd;

	aux = tokens[num_com];
	fd = 1;
	while (aux)
	{
		if (aux->type == RD_OVERWRITE)
			fd = ft_overwrite(&aux, tokens, num_com);
		else if (aux->type == RD_APPEND)
			fd = ft_append(&aux, tokens, num_com);
		else if (aux->type == RD_INPUT)
			fd = ft_input(&aux, tokens, num_com);
		else if (aux->type == RD_HEREDOC)
			fd = ft_heredoc(&aux, tokens, num_com);
		if (aux)
			aux = aux->next;
		if (fd == -1)
			return (fd);
	}
	return (fd);
}

static int	ft_overwrite(t_parsed **aux, t_parsed **tokens, int num_com)
{
	int			fd;
	t_parsed	*tmp;
	t_parsed	*free_me;

	tmp = (*aux)->prev;
	free_me = *aux;
	*aux = (*aux)->next->next;
	fd = open(free_me->next->text, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
	{
		dup2(fd, 1);
		close(fd);
	}
	free_me->next->next = NULL;
	if (tmp)
	{
		tmp->next = *aux;
		if ((*aux))
			(*aux)->prev = tmp;
	}
	else
		tokens[num_com] = *aux;
	ft_free_tokens(free_me);
	return (fd);
}

static int	ft_append(t_parsed **aux, t_parsed **tokens, int num_com)
{
	int			fd;
	t_parsed	*tmp;
	t_parsed	*free_me;

	tmp = (*aux)->prev;
	free_me = *aux;
	*aux = (*aux)->next->next;
	fd = open(free_me->next->text, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd != -1)
	{
		dup2(fd, 1);
		close(fd);
	}
	free_me->next->next = NULL;
	if (tmp)
	{
		tmp->next = *aux;
		if ((*aux))
			(*aux)->prev = tmp;
	}
	else
		tokens[num_com] = *aux;
	ft_free_tokens(free_me);
	return (fd);
}

static int	ft_input(t_parsed **aux, t_parsed **tokens, int num_com)
{
	int			fd;
	t_parsed	*tmp;
	t_parsed	*free_me;

	tmp = (*aux)->prev;
	free_me = *aux;
	*aux = (*aux)->next->next;
	fd = open(free_me->next->text, O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, 1);
		close(fd);
	}
	free_me->next->next = NULL;
	if (tmp)
	{
		tmp->next = *aux;
		if ((*aux))
			(*aux)->prev = tmp;
	}
	else
		tokens[num_com] = *aux;
	ft_free_tokens(free_me);
	return (fd);
}

static int	ft_heredoc(t_parsed **aux, t_parsed **tokens, int num_com)
{
	int			pipe_fd[2];
	int			status;
	t_parsed	*tmp;
	t_parsed	*free_me;

	tmp = (*aux)->prev;
	free_me = *aux;
	*aux = (*aux)->next->next;
	status = pipe(pipe_fd);
	if (status == -1)
		ft_printf("Error creating pipe\n");
	ft_manage_heredoc(pipe_fd, free_me->next->text);
	free_me->next->next = NULL;
	if (tmp)
	{
		tmp->next = *aux;
		if ((*aux))
			(*aux)->prev = tmp;
	}
	else
		tokens[num_com] = *aux;
	ft_free_tokens(free_me);
	return (1);
}
