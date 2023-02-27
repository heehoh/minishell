/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:04:25 by migo              #+#    #+#             */
/*   Updated: 2023/02/26 20:23:38 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	**ft_split(char const *str, char charset, int a);

void	num_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			count++;
		i++;
	}
	if (count % 2 == 1)
	{
		//write("syn");//임시 따음표 갯수가 맞지 않음
		exit(258);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	count(t_list *env)
{
	int	i;

	i = 0;
	while (env->env[i] != '=')
		i++;
	return (ft_strlen(&(env->env[i + 1])));
}

int	num_env_word(char *str, t_list *env)
{
	int	i;

	while (1)
	{
		i = 0;
		while (str[i] != ' ' && str[i])
		{
			if (str[i] != env->env[i])
				break ;
			i++;
		}
		if (env->env[i] == '=' && (str[i] == ' ' || str[i] == '\0'))
			return (count(env) - i - 1);
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	while (str[i] != ' ' && str[i])
		i++;
	return (-i - 1);
}

char	*quote(char *str, t_list *env)
{
	int		i;
	int		j;
	int		flag;
	char	*src;

	i = 0;
    j = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '$' && flag == 0)
		{
			j += num_env_word(&str[i + 1], i + 1, env);
		}
		if (str[i] == '\'')
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		i++;
	}
	src = malloc(sizeof(char) * i + j);
    return (src);
}

t_cmd *make_cmd_set(char *str, char **env)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (cmd = NULL)
	{
		perror("malloc");
		exit(1);
	}
	cmd->next = NULL;
}