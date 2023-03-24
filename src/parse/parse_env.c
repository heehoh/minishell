/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:22:47 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/24 17:35:26 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../libft/libft.h"

int	num_env_word(char *str, t_env *env, int *count)
{
	int		i;

	while (env)
	{
		i = 0;
		while (str[i] && ft_is_space(str[i]) == 0 && str[i] == env->var[i])
			i++;
		if (env->var[i] == '=' && ft_isalnum(str[i]))
			*count += ft_strlen(&(env->var[i + 1]));
		env = env->next;
	}
	while (ft_isalnum(str[i]) == 0)
		i++;
	return (i + 1);
}

int	cnt_env(char *str, t_env *env, int status)
{
	int	quote_flag;
	int	count;

	quote_flag = 0;
	count = 0;
	while (*str)
	{
		flag_quote(str, &quote_flag);
		if (*str == '$' && quote_flag != 1)
		{
			if (*(str + 1) == '?')
				str += num_env_exit(&count, status);
			else
				str += num_env_word((str + 1), env, &count);
		}
		else
		{
			str++;
			count++;
		}
	}
	return (count);
}

int	put_env_word(char *change, char *str, t_env *env, int *count)
{
	int		i;

	while (env)
	{
		i = 0;
		while (str[i] && ft_is_space(str[i]) == 0 && str[i] == env->var[i])
			i++;
		if (env->var[i] == '=' && ft_isalnum(str[i]))
		{
			while (env->var[i + 1])
			{
				change[*count] = env->var[i + 1];
				i++;
				(*count)++;
			}
		}
		env = env->next;
	}
	i = 0;
	while (ft_isalnum(str[i]) == 0)
		i++;
	return (i + 1);
}

void	insert_env(char *prev, char *str, t_env *env, int status)
{
	int	quote_flag;
	int	count;

	quote_flag = 0;
	count = 0;
	while (*prev)
	{
		flag_quote(prev, &quote_flag);
		if (*prev == '$' && quote_flag != 1)
		{
			if (*(prev + 1) == '?')
				prev += put_env_exit(str, &count, status);
			else
				prev += put_env_word(str, (prev + 1), env, &count);
		}
		else
		{
			str[count] = *prev;
			count++;
			prev++;
		}
	}
}

void	replace_env(char **sep_pipe, t_env *env, int status)
{
	int		i;
	char	*prev;
	int		count;

	i = 0;
	while (sep_pipe[i])
	{
		prev = sep_pipe[i];
		count = cnt_env(sep_pipe[i], env, status);
		sep_pipe[i] = malloc(sizeof(char) * (count + 1));
		if (sep_pipe[i] == NULL)
			error_malloc();
		sep_pipe[i][count] = '\0';
		insert_env(prev, sep_pipe[i], env, status);
		free(prev);
		++i;
	}
}
