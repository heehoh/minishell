/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:30:37 by migo              #+#    #+#             */
/*   Updated: 2023/02/23 17:23:08 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	char	**path;
	t_tree	*parse;

	while (1)
	{
		str = readline("minishell$ ");
		if (str == NULL)
		{
			printf(" exit\n");
			return (0);
		}
		add_history(str);
		parse = make_tree(str);
		//명령어 실행. + builtin 
		free(str);
	}
}
