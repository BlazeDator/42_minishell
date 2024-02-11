/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hescoval <hescoval@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:06:26 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/10 17:23:02 by hescoval         ###   ########.fr       */
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
# include <linux/limits.h>

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

typedef enum s_special
{
	DEFAULT,
	RD_OVERWRITE,
	RD_APPEND,
	RD_INPUT,
	RD_HEREDOC,
	PIPE,
	COMMAND,
	STRING
}	t_special;

typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}					t_envs;

typedef struct s_parsed
{
	char			*text;
	char			*type;
	struct s_parsed	*next;
	struct s_parsed	*prev;
}	t_parsed;

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
int		redirect_check(char *line);
int		padding_needed(char *line, int i, int pad);
void	pad(char *src, char *dest, int i, int j);
int		pipe_checks(char *line);
char	*pad_central(char *line);
int		quotes_open(char *str, int target_index);
t_parsed	*make_list(char **args);
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
t_envs	*ft_del_env(t_envs *envs, char *key);
t_envs	*ft_free_envs(t_envs *envs);
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
/*				builtins.c				      */
/* ************************************************************************** */
void	ft_exec_builtins(char **args);
/* ************************************************************************** */
/*				echo.c				      */
/* ************************************************************************** */
void	ft_exec_echo(char **array_args);
/* ************************************************************************** */
/*				cd.c				      */
/* ************************************************************************** */
void	ft_exec_cd(char *args, t_envs *envs);
/* ************************************************************************** */
/*				pwd.c				      */
/* ************************************************************************** */
void	ft_exec_pwd(t_envs *envs);
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
