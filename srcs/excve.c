/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmeirele <dmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:14:57 by dmeirele          #+#    #+#             */
/*   Updated: 2024/02/20 15:14:57 by dmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_exec_command(char *command, t_parsed *tokens);
static char	**ft_get_path(t_envs *envs);
static char	**ft_count_args(t_parsed *tokens);

static char	**ft_get_path(t_envs *envs)
{
	char	*value;
	char	**path_value;

	path_value = NULL;
	value = NULL;
	while (envs)
	{
		if (!ft_strncmp(envs->key, "PATH", 4))
			value = ft_substr(envs->value, 0, ft_strlen(envs->value));
		envs = envs->next;
	}
	if (value)
		path_value = ft_split(value, ':');
	free(value);
	return (path_value);
}

void	*ft_check_command(t_envs *envs, t_parsed *tokens)
{
	char	**path;
	char	*command;
	char	*temp;
	int		i;

	i = -1;
	path = ft_get_path(envs);
	if (!*path)
		return (NULL);
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		command = ft_strjoin(temp, tokens->text);
		free(temp);
		if (access(command, X_OK) == 0)
		{
			free_splits(path);
			ft_exec_command(command, tokens);
			free(command);
			return (NULL);
		}
		free(command);
	}
	free_splits(path);
	return (NULL);
}

static void	ft_exec_command(char *command, t_parsed *tokens)
{
	t_envs	*envs;
	pid_t	new_process;
	char	**array_env;
	char	**new_array;

	new_array = ft_count_args(tokens);
	envs = return_envs(0);
	array_env = ft_array_envs(envs);
	new_process = fork();
	if (!new_process)
	{
		if (execve(command, new_array, array_env) == -1)
		{
			free_splits(new_array);
			free_splits(array_env);
			printf("\nCommand = [%s]\n\n", command);
			free(command);
			ft_exit(tokens);
		}
	}
	else
		waitpid(-1, NULL, 0);
	free_splits(new_array);
	free_splits(array_env);
}

static char	**ft_count_args(t_parsed *tokens)
{
	int			i;
	char		**new;
	t_parsed	*head;

	i = 0;
	head = tokens;
	while (tokens && tokens->type != PIPE)
	{
		i++;
		tokens = tokens->next;
	}
	new = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (head && head->type != PIPE)
	{
		new[i] = ft_strdup(head->text);
		i++;
		head = head->next;
	}
	new[i] = NULL;
	return (new);
}
