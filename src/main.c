/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 16:14:16 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include "readline/history.h"
#include "readline/readline.h"

static char	*create_prompt(t_shell *shell)
{
	char	*prompt;
	char	*tmp_prompt;
	char	*value;

	value = NULL;
	prompt = (char *)ft_calloc(BUFFER_SIZE, 1);
	tmp_prompt = prompt;
	ft_strlcpy(tmp_prompt, "\033[1;31mRaRe\033[0m:\033[1;34m", 24);
	tmp_prompt += 23;
	value = get_env_value(shell->env, "PWD");
	if (value)
	{
		ft_strlcpy(tmp_prompt, value, ft_strlen(value) + 1);
		tmp_prompt += ft_strlen(value);
	}
	ft_strlcpy(tmp_prompt, "\033[0m$ ", 7);
	if (value)
		free(value);
	return (prompt);
}

static int	main_loop(t_shell *shell)
{
	char	*prompt;

	prompt = create_prompt(shell);
	shell->line = readline(prompt);
	free(prompt);
	if (!shell->line)
	{
		free_all(shell);
		ft_exit(0);
	}
	if (shell->line && !*shell->line)
		return (free(shell->line), 1);
	add_history(shell->line);
	if (check_odd_quotes(shell, shell->line))
		return (free(shell->line), 1);
	shell->tokens = tokenizer(shell, shell->line, shell->env);
	free(shell->line);
	if (!shell->tokens)
		return (1);
	return (0);
}

static void	main_loop2(t_shell *shell)
{
	shell->cmd = create_cmds(shell, *shell->tokens);
	free_token(shell->tokens);
	if (!shell->cmd)
		return ;
	parse_cmds(shell);
	execute_cmd(shell);
	shell->cmd->is_builtin = false;
	free_cmds(shell);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = init_shell(env);
	if (!shell)
		return (-1);
	while (1)
	{
		if (main_loop(shell))
			continue ;
		main_loop2(shell);
	}
	free_all(shell);
	ft_exit(*shell->exit_status);
}
