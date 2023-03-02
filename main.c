/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:14:47 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/02 10:47:36 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cc main.c src/parse/* src/env/env.c src/libft/ft_strdup.c src/libft/ft_isalnum.c src/libft/ft_split.c src/libft/ft_strlen.c
// 컴파일  할 때 위에거 쓰면 됨
// 

#include "./src/minishell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_cmd *cmd;
	int j = 1;

	get_env_list(env);
	cmd = parse_input("'$HOME'");
	while (cmd)
	{
		int i = 0;
		while (cmd->option[i])
		{
			printf("%d pipe -> option : %s\n",j, cmd->option[i]);
			i++;
		}
		i = 0;
		while (cmd->file[i].redirection != 0)
		{
			printf("redirection : %d\n", cmd->file[i].redirection);
			printf("file : %s\n", cmd->file[i].name);
			i++;
		}
		cmd = cmd->next;
		j++;
	}
	return (0);
}
