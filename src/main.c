/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:30:37 by migo              #+#    #+#             */
/*   Updated: 2023/03/06 16:44:02 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft/libft.h"
#include <fcntl.h>

int	rule_cd(char *str)
{
	int fd;
	int i;
	char path[4096];

	if (getcwd(path, 4096) == NULL)
		return (0);
	if (str[0] == '.' && str[1] == '.')
	{
		i = ft_strlen((path)) - 1;
		while ((path)[i] != '/')
			i--;
		(path)[i] = '\0';
		chdir(path);
		return (0);
	}
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		printf("cd: %s: No such file or directory\n", str);
		return (0);
	}
	return (1);
}

void	cd_option(char *str)
{
	char	path[4096];
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (getcwd(path, 4096) == NULL)
		return ;
	if (rule_cd(str) == 0)
		return ;
	if (str[0] == '/')
	{
		if (chdir(str) < 0)
			printf("cd: %s: Not a directory\n", str);
		return ;
	}
	while (path[i])
		i++;
	path[i] = '/';
	i++;
	while (str[j])
	{
		path[i] = str[j];
		i++;
		j++;
	}
	path[i] = str[j];
	if (chdir(path) < 0)
		printf("cd: %s: Not a directory\n", str);
}

void	builtin_cd(t_cmd *cmd)
{
	t_env	*tmp;
	char	*str;

	tmp = g_global;
	if (ft_strncmp((cmd->option[0]), "cd", ft_strlen(cmd->option[0])) == 0)
	{
		if (cmd->option[1] != NULL)
		{
			cd_option(cmd->option[1]);
		}
		else
		{
			while (tmp)
			{
				if (ft_strncmp(tmp->var, "HOME", 4) == 0)
					break ;
				tmp = tmp->next;
			}
			if (ft_strncmp(tmp->var, "HOME", 4) == 0)
			{
				str = ft_strdup((tmp->var + 5));
				chdir(str);
				free(str);
			}
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_cmd	*cmd;
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
		read_cmd(cmd);
		builtin_cd(cmd);
		getcwd(path, 4096);
		printf("%s\n", path);
		free(input);
	}
}
/*널문자만 들어올 경우 main에서 처리"
cc src/main.c src/parse/* src/env/env.c src/libft/ft_strdup.c src/libft/ft_isalnum.c src/libft/ft_split.c src/libft/ft_strlen.c -lreadline*/