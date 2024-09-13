/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/09/13 14:06:36 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>

void	ft_exit(t_shell *shell, int exit_code)
{
	rl_clear_history();
	free_all(shell);
	exit(exit_code);
}

static char	*create_prompt(t_shell *shell)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_strjoin("\033[1;31mRaRe\033[0m:\033[1;34m",
			get_env_value(shell->env, "PWD"));
	tmp = prompt;
	prompt = ft_strjoin(tmp, "\033[0m$ ");
	free(tmp);
	return (prompt);
}

void	exchange_var(char *str, int *j, char *new, int *k, t_shell *shell)
{
	char	*key;
	char	*value;

	key = get_env_key(str + *j);
	if (!key)
		return ;
	if (ft_strncmp(key, "$", higher_len(key, "$")) == 0)
		value = ft_strdup("$");
	else if (ft_strncmp(key, "?", 1) == 0)
		value = ft_itoa(*(shell->last_exit_status));
	else
		value = get_env_value(shell->env, key);
	ft_strlcpy(new + *k, value, ft_strlen(value) + 1);
	*k += ft_strlen(value);
	if (ft_strncmp(key, "$", higher_len(key, "$")) == 0)
		return ;
	*j += ft_strlen(key);
}

char	*allocate_str(t_shell *shell, int buff_size)
{
	char	*new;

	new = (char *)ft_calloc(sizeof(char), buff_size + 1);
	if (!new)
		print_error(shell, "HATA", NULL, ERR_MEMALLOC, 1);
	return (new);
}

char	*parse_cmd_loop(t_cmd *cmd, t_shell *shell, int *i)
{
	bool	quote[2];
	int		j;
	int		k;
	char	*new;

	new = allocate_str(shell, BUFFER_SIZE);
	j = -1;
	k = 0;
	quote[0] = false;
	quote[1] = false;
	while (cmd->arr[*i][++j])
	{
		if (cmd->arr[*i][j] == '\'' && !quote[1])
			quote[0] = !quote[0];
		else if (cmd->arr[*i][j] == '"' && !quote[0])
			quote[1] = !quote[1];
		else if (quote[0] && cmd->arr[*i][j] != '\'')
			new[k++] = cmd->arr[*i][j];
		else if ((!quote[0] && !quote[1]) || cmd->arr[*i][j] != '"')
		{
			if (cmd->arr[*i][j] != '$')
			{
				new[k++] = cmd->arr[*i][j];
			}
			if (cmd->arr[*i][j] == '$')
			{
				exchange_var(cmd->arr[*i], &(j), new, &(k), shell);
			}
		}
	}
	return (new);
}

void	parse_cmd(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (cmd->arr[i])
	{
		new = parse_cmd_loop(cmd, shell, &i);
		if (new[0] != '\0')
		{
			free(cmd->arr[j]);
			cmd->arr[j] = ft_strdup(new);
			j++;
		}
		free(new);
		i++;
	}
	cmd->arr[j++] = NULL;
	while (cmd->arr[j])
	{
		free(cmd->arr[j++]);
	}
}

char	*parse_file(t_shell *shell, t_cmd *cmd, char *file)
{
	bool	quote[2];
	int		i;
	int		j;
	char	*new;

	new = allocate_str(shell, BUFFER_SIZE);
	i = 0;
	j = 0;
	while (file[i])
	{
		if (file[i] == '\'' && !quote[1])
			quote[0] = !quote[0];
		else if (file[i] == '"' && !quote[0])
			quote[1] = !quote[1];
		else if ((quote[0] && file[i] != '\'') || (quote[1] && file[i] != '"')
				|| (!quote[0] && !quote[1]))
			new[j++] = file[i];
		i++;
	}
	return (new);
}

void	parse_cmds(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		remove_redirs(shell, cmd);
		parse_cmd(shell, cmd);
		cmd = cmd->next;
	}
}

void	main_loop(t_shell *shell, int tester, char **arg_input, int *i)
{	
	char	*prompt;
	
	prompt = create_prompt(shell);
	if (!tester)
	{
		shell->line = readline(prompt);
		free(prompt);
		if (!shell->line)
			return ;
		add_history(shell->line);
	}
	else
		shell->line = arg_input[*i];
	shell->tokens = tokenizer(shell->line, shell->env);
	if (!shell->tokens)
		return ;
	shell->cmd = create_cmds(shell, shell->tokens);
	parse_cmds(shell);
	// print_cmd(shell);
	execute_cmd(shell);
	shell->cmd->is_builtin = false;
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	shell = init_shell(env);
	if (!shell)
		return (-1);
	// while (1)
		main_loop(shell, 0, NULL, NULL);
	ft_exit(shell, *(shell->last_exit_status));
}
