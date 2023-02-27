/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:27:55 by hujeong           #+#    #+#             */
/*   Updated: 2023/02/26 20:23:36 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

t_cmd	*parse_cmd(char **cmd_set)
{
	t_cmd	*cmd_head;
	t_cmd	*cmd_node;
	char	**cmd;
	int		count;

	cmd_head = (t_cmd *)malloc(sizeof(t_cmd));
	cmd_head->file
	while (cmd_set[count])
	{

		++count;
	}
}

t_cmd	*parsing(char *input)
{
	t_cmd	*cmd;
	char	**cmd_set;
	int		count;

	cmd_set = ft_split(input, '|');
	cmd = parse_cmd(cmd_set)
}
