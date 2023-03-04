/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:19:48 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/04 14:41:25 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include "./src/libft/libft.h"

int	heredoc(char *limiter, char *tmp)
{
	int		fd;
	char	*str;
	char	*end;

	fd = open(tmp, O_WRONLY | O_CREAT, 0600);
	if (fd < 0)
		printf("hi\n");
	end = ft_strjoin(limiter, "\n");
	while (1)
	{
		str = readline("> ");
		if (ft_strncmp(str, end, ft_strlen(str)) == 0)
		{
			free(str);
			free(end);
			close(fd);
			fd = open(tmp, O_RDONLY);
			return (fd);
		}
		write(fd, str, ft_strlen(str));
		free(str);
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;

	if (argc != 2)
		return (0);
	fd = heredoc(argv[1], "tmp/tmp1");
	str = get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	unlink("/tmp/temp");
	return (0);
}
