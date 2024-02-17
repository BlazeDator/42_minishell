/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:42:17 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/17 15:34:43 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_init_signals(void)
{
	g_signal = 0;
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_ignore_signals(void)
{
	signal(SIGINT, ft_handle_sigint_ign);
	signal(SIGQUIT, ft_handle_sigquit);
}

void	ft_restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
