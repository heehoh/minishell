/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:02:52 by migo              #+#    #+#             */
/*   Updated: 2023/03/01 20:37:32 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

t_cmd	*get_cmd(char *sep_pipe)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (cmd == 0)
		return (0);
	cmd->file = parse_file(sep_pipe);
	cmd->option = parse_cmd_option(sep_pipe);
	cmd->next = NULL;
	return (cmd);
}

void	cmd_lstadd_back(t_cmd *lst, t_cmd *new)
{
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

void	replace_env(t_cmd *cmd, t_env *env)
{
	int		i;

	while (cmd)
	{
		i = -1;
		while (cmd->option[++i])
			replace_util(&(cmd->option[i]), env);
		i = -1;
		while (cmd->file[++i].name)
			replace_util(&(cmd->file[i].name), env);
		cmd = cmd->next;
	}
}

t_cmd	*parse_input(char *str)
{
	t_cmd	*cmd;
	char	**sep_pipe;
	int		i;

	sep_pipe = ft_split(str, '|');
	cmd = get_cmd(sep_pipe[0]);
	i = 0;
	while (sep_pipe[++i])
		cmd_lstadd_back(cmd, get_cmd(sep_pipe[i]));
	replace_env(cmd, g_global);
	return (cmd);
}
