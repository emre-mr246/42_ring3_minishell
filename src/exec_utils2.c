/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:01:26 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/24 14:08:16 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>

void	wait_for_pids(t_shell *shell)
{
	int	exit_status;

	while (wait(&exit_status) > 0)
		continue ;
	if (WIFEXITED(exit_status))
		*shell->exit_status = WEXITSTATUS(exit_status);
}
