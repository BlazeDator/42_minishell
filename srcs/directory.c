/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:29:26 by txisto-d          #+#    #+#             */
/*   Updated: 2024/02/17 15:50:46 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_get_dir(void)
{
	char	*dir;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	dir = ft_strjoin \
	("\001\033[1;32m\002minishell@42\001\033[0m\002:\001\033[1;34m\002", tmp);
	free(tmp);
	tmp = ft_strjoin(dir, "\001\033[0m\002$ ");
	free(dir);
	return (tmp);
}
