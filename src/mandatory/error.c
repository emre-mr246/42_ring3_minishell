/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:52:47 by emgul             #+#    #+#             */
/*   Updated: 2024/08/28 13:51:53 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	print_error(t_shell *shell, char *str, char *cmd, int mode, int exits)
{
	*(shell->last_exit_status) = 1;
	if (mode == ERR_ENVNAME)
	{
		ft_putstr_fd("RaRe: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	else if (mode == ERR_NODIR)
	{
		ft_putstr_fd("RaRe: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
	else if (mode == ERR_CD_PWD)
	{
		ft_putstr_fd("RaRe: cd: string not in pwd: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (mode == ERR_NOCMD)
	{
		ft_putstr_fd("RaRe: command not found: ", 2);
		ft_putendl_fd (str, 2);
	}
	else if (mode == ERR_EXCBUFF)
		ft_putstr_fd("Exceeded buffer size\n", 2);
	else if (mode == ERR_MEMALLOC)
		ft_putstr_fd("Cannot allocate memory\n", 2);
	else if (mode == ERR_NONNUM)
	{
		*(shell->last_exit_status) = 2;
		ft_putstr_fd("Input nonnumeric\n", 2);
	}
	else if (mode == ERR_NOREAD)
	{
		ft_putstr_fd("RaRe: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": cannot read file: ", 2);
		ft_putendl_fd(str, 2);
	}
	if (exits)
		exit(*(shell->last_exit_status));
	else
		return ;
}
