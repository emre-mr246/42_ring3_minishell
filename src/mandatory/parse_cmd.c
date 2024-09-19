/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:22:24 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/19 19:18:46 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
		value = ft_itoa(*(shell->exit_status));
	else
		value = get_env_value(shell->env, key);
	ft_strlcpy(new + *k, value, ft_strlen(value) + 1);
	*k += ft_strlen(value);
	if (value)
		free(value);
	if (ft_strncmp(key, "$", higher_len(key, "$")) == 0)
	{
		free(key);
		return ;
	}
	*j += ft_strlen(key);
	free(key);
}

char	*parse_cmd_loop(t_cmd *cmd, t_shell *shell, int *i)
{
	bool	single_quote;
	bool	double_quote;
	int		j;
	int		k;
	char	*new;

	new = allocate_str(shell, BUFFER_SIZE);
	if (!new)
		return (NULL);
	j = -1;
	k = 0;
	single_quote = false;
	double_quote = false;
	while (cmd->arr[*i][++j])
	{
		if (cmd->arr[*i][j] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (cmd->arr[*i][j] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (single_quote && cmd->arr[*i][j] != '\'')
			new[k++] = cmd->arr[*i][j];
		else if ((!single_quote && !double_quote) || cmd->arr[*i][j] != '"')
		{
			if (cmd->arr[*i][j] != '$')
				new[k++] = cmd->arr[*i][j];
			if (cmd->arr[*i][j] == '$')
				exchange_var(cmd->arr[*i], &(j), new, &(k), shell);
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
		if (new && new[0])
		{
			free(cmd->arr[j]);
			cmd->arr[j] = ft_strdup(new);
			j++;
		}
		free(new);
		i++;
	}
	if (cmd->arr[j])
		free(cmd->arr[j]);
	cmd->arr[j++] = NULL;
	while (cmd->arr[j])
		free(cmd->arr[j++]);
}

char	*parse_file(t_shell *shell, t_cmd *cmd, char *file)
{
	bool	single_quote;
	bool	double_quote;
	int		i;
	int		j;
	char	*new;

	single_quote = false;
	double_quote = false;
	new = allocate_str(shell, BUFFER_SIZE);
	i = 0;
	j = 0;
	while (file[i])
	{
		if (file[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (file[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if ((single_quote && file[i] != '\'') || (double_quote && file[i] != '"')
				|| (!single_quote && !double_quote))
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
