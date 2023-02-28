/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ss.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:36:36 by hujeong           #+#    #+#             */
/*   Updated: 2023/02/28 11:45:22 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(__attribute__((unused))int argc, __attribute__((unused))char *argv[],
			char *env[])
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}
