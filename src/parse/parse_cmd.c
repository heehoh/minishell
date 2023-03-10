/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:02:52 by migo              #+#    #+#             */
/*   Updated: 2023/03/10 14:05:20 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../libft/libft.h"

t_cmd	*get_cmd(char *sep_pipe)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (cmd == NULL)
		error_malloc();
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

t_cmd	*parse_input(char *input, t_env *env, int status)
{
	t_cmd	*cmd;
	char	**sep_pipe;
	int		i;

	sep_pipe = ft_split(input, '|');
	if (sep_pipe == NULL)
		error_malloc();
	free(input);
	replace_env(sep_pipe, env, status);
	cmd = get_cmd(sep_pipe[0]);
	i = 0;
	while (sep_pipe[++i])
		cmd_lstadd_back(cmd, get_cmd(sep_pipe[i]));
	str_array_clear(sep_pipe);
	delete_quote(cmd);
	return (cmd);
}
