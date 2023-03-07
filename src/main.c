/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:30:37 by migo              #+#    #+#             */
/*   Updated: 2023/03/07 17:15:15 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft/libft.h"
#include <fcntl.h>

int	ft_isalpha(int c)
{
	if (65 <= c && c <= 90)
		return (1);
	else if (97 <= c && c <= 122)
		return (1);
	else
		return (0);
	return (0);
}

int	cp_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i - 1);
}

int	builtin_unset(t_cmd *cmd, t_env *env)
{
	t_env	*tmp;
	t_env	*pre_tmp;
	int		i;

	i = 0;
	if (ft_isalpha(cmd->option[1][0]) == 0)
	{
		printf("export: \'%s\': not a valid identifier\n", cmd->option[1]);
		return (1);
	}
	while (cmd->option[++i])
	{
		tmp = env;
		if (ft_strncmp(cmd->option[i], tmp->var, cp_env(tmp->var)) == 0)
		{
			env = tmp->next;
			free(tmp);
		}
		while (tmp)
		{
			pre_tmp = tmp;
			tmp = tmp->next;
			if (ft_strncmp(cmd->option[i], tmp->var, cp_env(tmp->var)) == 0)
			{
				pre_tmp->next = tmp->next;
				free(tmp);
			}
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_cmd	*cmd;
	t_env	*env1;
	char	path[4096];

	get_env_list(env);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			printf(" exit\n");
			return (0);
		}
		add_history(input);
		cmd = parse_input(input);
		builtin_unset(cmd, g_global);
		env1 = g_global;
		while (env1)
		{
			printf("%s\n", env1->var);
			env1 = env1->next;
		}
		free(input);
	}
}
/*널문자만 들어올 경우 main에서 처리"
cc src/main.c src/parse/* src/env/env.c src/libft/ft_strdup.c src/libft/ft_isalnum.c src/libft/ft_split.c src/libft/ft_strlen.c -lreadline*/