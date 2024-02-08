/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:06:26 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/01 14:26:17 by pabernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*				Libraries				      */
/* ************************************************************************** */
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# include "../libft/libft.h"
/* ************************************************************************** */
/*				Macros					      */
/* ************************************************************************** */
# define PROMPT "[Minishell]>"
/* ************************************************************************** */
/*				Structs					      */
/* ************************************************************************** */
/* *next -> if pipe. */
typedef struct s_minish
{
	char			*command;
	char			**args;
	struct s_envs	*envs;
	char			**redir_in;
	char			**redir_out;
	struct s_minish	*next;
}					t_minish;

typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}					t_envs;
/* ************************************************************************** */
/*				Global Var				      */
/* ************************************************************************** */
extern int	g_signal;
/* ************************************************************************** */
/*				minishell.c				      */
/* ************************************************************************** */
void	ft_minishell(void);
/* ************************************************************************** */
/*				parser.c				      */
/* ************************************************************************** */
void	ft_parser(char *line);
/* ************************************************************************** */
/*				executer.c				      */
/* ************************************************************************** */
void	ft_executer(char *path);
/* ************************************************************************** */
/*				envs.c					      */
/* ************************************************************************** */
t_envs	*ft_create_envs(void);
t_envs	*ft_new_env(char *str);
t_envs	*ft_add_env(t_envs *envs, t_envs *new);
/* ************************************************************************** */
/*				api.c					      */
/* ************************************************************************** */
t_envs	*return_envs(t_envs *envs);
char	**return_argv(char **argv);
/* ************************************************************************** */
/*				signal.c				      */
/* ************************************************************************** */
void	ft_init_signals(void);
void	ft_ignore_signals(void);
void	ft_restore_signals(void);
/* ************************************************************************** */
/*				echo.c				      */
/* ************************************************************************** */
void	ft_exec_echo(char **array_args);
/* ************************************************************************** */
/*				signal_handlers.c			      */
/* ************************************************************************** */
void	ft_handle_eof(void);
void	ft_handle_sigint(int sig);
void	ft_handle_sigint_ign(int sig);
void	ft_handle_sigquit(int sig);
/* ************************************************************************** */
/*				exit.c				      	      */
/* ************************************************************************** */
void	ft_exit(void);
#endif
