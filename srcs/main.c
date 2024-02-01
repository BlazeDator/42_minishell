/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:48:43 by pabernar          #+#    #+#             */
/*   Updated: 2024/02/01 14:25:53 by pabernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_signal;

int	main(int argc, char **argv)
{
	if (argc != 1 && argv)
		return (printf("No arguments\n"));
	ft_init_signals();
	ft_minishell();
	return (0);
}
