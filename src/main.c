/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 12:48:00 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"

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

void	main_loop(t_shell *shell)
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
		return (free(shell->line));
	add_history(shell->line);
	shell->tokens = tokenizer(shell, shell->line, shell->env);
	free(shell->line);
	if (!shell->tokens)
		return ;
	shell->cmd = create_cmds(shell, *shell->tokens);
	free_token(shell->tokens);
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
		main_loop(shell);
	ft_exit(*shell->exit_status);
}
