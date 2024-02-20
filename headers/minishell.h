/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hescoval <hescoval@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:06:26 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/20 15:55:33 by hescoval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*				Libraries					   */
/* ************************************************************************** */

# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
/* ************************************************************************** */
/*				Macros						   */
/* ************************************************************************** */
# define PROMPT "[Minishell]>"
/* ************************************************************************** */
/*				Structs						   */
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
	STRING
}					t_special;

typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}					t_envs;

typedef struct s_parsed
{
	char			*text;
	t_special		type;
	struct s_parsed	*next;
	struct s_parsed	*prev;
	int				unite_with_next;
}					t_parsed;

/* ************************************************************************** */
/*				Global Var					   */
/* ************************************************************************** */
extern int			g_signal;
/* ************************************************************************** */
/*				minishell.c					   */
/* ************************************************************************** */
void				ft_minishell(void);
/* ************************************************************************** */
/*				parser.c					   */
/* ************************************************************************** */
void				ft_parser(char *line);
int					redirect_check(char *line);
int					padding_needed(char *line, int i, int pad);
void				pad(char *src, char *dest, int i, int j);
int					pipe_checks(char *line);
char				*pad_central(char *line);
int					quotes_open(char *str, int target_index);
t_parsed			*make_list(char **args);
void				ft_farfaraway(t_parsed *tokens, int klen, char **new,
						char **tmp);
/* ************************************************************************** */
/*				executer.c					   */
/* ************************************************************************** */
void				ft_executer(char *path);
/* ************************************************************************* */
/*				envs.c						   */
/* ************************************************************************** */
t_envs				*ft_create_envs(void);
t_envs				*ft_new_env(char *str);
t_envs				*ft_add_env(t_envs *envs, t_envs *new);
t_envs				*ft_free_envs(t_envs *envs);
/* ************************************************************************** */
/*				api.c						   */
/* ************************************************************************** */
t_envs				*return_envs(t_envs *envs);
char				**return_argv(char **argv);
/* ************************************************************************** */
/*				signal.c					   */
/* ************************************************************************** */
void				ft_init_signals(void);
void				ft_ignore_signals(void);
void				ft_restore_signals(void);
/* ************************************************************************** */
/*				builtins.c					   */
/* ************************************************************************** */
void				ft_exec_builtins(t_parsed *tokens);
/* ************************************************************************** */
/*				echo.c					   */
/* ************************************************************************** */
void				ft_exec_echo(t_parsed *tokens);
/* ************************************************************************** */
/*				cd.c					   */
/* ************************************************************************** */
void				ft_exec_cd(char *args, t_envs *envs);
/* ************************************************************************** */
/*				pwd.c					   */
/* ************************************************************************** */
void				ft_exec_pwd(t_envs *envs);
/* ************************************************************************** */
/*				export.c					   */
/* ************************************************************************** */
t_envs				*ft_exec_export(t_envs *envs, char *args);
/* ************************************************************************** */
/*				unset.c					   */
/* ************************************************************************** */
t_envs				*ft_exec_unset(t_envs *envs, char *key);
/* ************************************************************************** */
/*				env.c					   */
/* ************************************************************************** */
void				ft_exec_env(t_envs *envs);
/* ************************************************************************** */
/*				exit.c					   	      */
/* ************************************************************************** */

/**
 * @brief Free the memory and exit the program.
 */
void				ft_exit(void);

/* ************************************************************************** */
/*				signal_handlers.c				   */
/* ************************************************************************** */
void				ft_handle_eof(void);
void				ft_handle_sigint(int sig);
void				ft_handle_sigint_ign(int sig);
void				ft_handle_sigquit(int sig);
/* ************************************************************************** */
/*									directory.c								*/
/* ************************************************************************** */

/**
 * @brief Get the current directory.
 * @return char * with the current directory memory allocated.
 */
char				*ft_get_dir(void);

/* ************************************************************************** */
/*									split_token.c							*/
/* ************************************************************************** */

t_parsed			*ft_split_token(char *line);

/* ************************************************************************** */
/*									expander.c							*/
/* ************************************************************************** */
t_parsed			*ft_expand_variables(t_parsed *tokens);
int					ft_before_exp(char *str);
int					ft_key_len(char *str);

/* ************************************************************************** */
/*									treat_token.c							*/
/* ************************************************************************** */
void				ft_treat_token(t_parsed *token, char *line);
int					valid_tokens(t_parsed *tokens);
#endif
