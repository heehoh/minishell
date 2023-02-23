/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:30:37 by migo              #+#    #+#             */
/*   Updated: 2023/02/23 12:29:56 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>

// 0 
// 1 > 2 >> 3 < 4 <<

typedef struct cmd
{
	char	*file;
	int		redirection;
	char	**option; 
} cmd;

typedef struct set
{
	struct cmd *cmd;
	int		pipe;
	char	**path;
}t_set ;

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_set	set;

	while (1)
	{
		str = readline("minishell$ ");
		if (str == NULL)
		{
			printf(" exit\n");
			return (0);
		}
		add_history(str);
		//명령어 파싱.
		//명령어 실행. + builtin 
		free(str);
	}
}
