/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:01:27 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/08 15:30:04 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "process.h"

int	create_process(t_cmd *cmd, t_env *env);

//void    read_cmd(t_cmd *cmd)
//{
//    int i;
//    int j;

//    j = 1;
//    while (cmd)
//    {
//        i = 0;
//        while (cmd->option[i])
//        {
//            printf("%d pipe -> option : %s\n",j, cmd->option[i]);
//            i++;
//        }
//        i = 0;
//        while (cmd->file[i].redirection != 0)
//        {
//            printf("redirection : %d\n", cmd->file[i].redirection);
//            printf("file : %s\n", cmd->file[i].name);
//            i++;
//        }
//        cmd = cmd->next;
//        ++j;
//    }
//}

int	main(int argc, __attribute__((unused))char **argv, char **env)
{
	char	*input;
	t_cmd	*cmd;
	t_env	*env_list;
	int		g_status;

	if (argc != 1)
		return (1);
	env_list = get_env_list(env);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		if (input[0] == '\0')
			exit(0);
		add_history(input);
		g_status = syntax_error(input, 0, 0);
		if (g_status == 258)
		{
			free(input);
			continue ;
		}
		cmd = parse_input(input, env_list);
		g_status = create_process(cmd, env_list);
		cmd_clear(cmd);
	}
}
