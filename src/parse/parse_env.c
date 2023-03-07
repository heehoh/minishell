/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:22:47 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/07 21:13:26 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

//int	num_env_exit(void)
//{
//	int		len;
//	char	*num;

//	num = ft_itoa(g_status);
//	if (num == NULL)
//		malloc_error();
//	len = ft_strlen(num);
//	free(num);
//	return (len + 1);
//}

//int	put_env_exit(char *change, int *count)
//{
//	int		i;
//	char	*num;

//	num = ft_itoa(g_status);
//	if (num == NULL)
//		malloc_error();
//	i = 0;
//	while (num[i])
//	{
//		change[*count] = num[i];
//		++(*count);
//		++i;
//	}
//	free(num);
//	return (i + 1);
//}

int	num_env_word(char *str, t_env *env, int *count)
{
	int		i;
	char	*num;

	if (*str == '?')
		return (num_env_exit());
	while (env)
	{
		i = 0;
		while (str[i] && str[i] != ' ' && str[i] == env->var[i])
			i++;
		if (env->var[i] == '=' && ft_isalnum(str[i]))
			*count += ft_strlen(&(env->var[i + 1]));
		env = env->next;
	}
	while (ft_isalnum(str[i]) == 0)
		i++;
	return (i + 1);
}

int	cnt_env(char *str, t_env *env)
{
	int	quote_flag;
	int	count;

	quote_flag = 0;
	count = 0;
	while (*str)
	{
		if (flag_quote(str, &quote_flag) == 1)
			str++;
		else if (*str == '$' && quote_flag != 1)
			str += num_env_word((str + 1), env, &count);
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
	char	*num;

	if (*str == '?')
		return (put_env_exit(change, count));
	while (env)
	{
		i = 0;
		while (str[i] && str[i] != ' ' && str[i] == env->var[i])
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

void	insert_env(char *prev, char *str, t_env *env)
{
	int	quote_flag;
	int	count;

	quote_flag = 0;
	count = 0;
	while (*prev)
	{
		if (flag_quote(prev, &quote_flag) == 1)
			prev++;
		else if (*prev == '$' && quote_flag != 1)
			prev += put_env_word(str, (prev + 1), env, &count);
		else
		{
			str[count] = *prev;
			count++;
			prev++;
		}
	}
}

void	replace_util(char **str, t_env *env)
{
	char	*prev;
	int		count;

	prev = *str;
	count = cnt_env(*str, env);
	*str = malloc(sizeof(char) * (count + 1));
	if (*str == NULL)
		return ;
	(*str)[count] = '\0';
	insert_env(prev, *str, env);
	free(prev);
}

//line 이라고 써있는 것 string으로 통일. change -> prev 이전의 문자라는 뜻으로 변수 바꿈
