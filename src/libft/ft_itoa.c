/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:23:12 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/04 18:04:07 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	fill_nbr(char *nbr, int n, size_t len)
{
	nbr[len] = '\0';
	if (n < 0)
	{
		nbr[0] = '-';
		nbr[--len] = -(n % 10) + '0';
		n = -(n / 10);
	}
	else if (n == 0)
		nbr[0] = '0';
	while (n)
	{
		nbr[--len] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		nb;
	size_t	len;

	nb = n;
	len = 0;
	if (nb <= 0)
		++len;
	while (nb)
	{
		nb /= 10;
		++len;
	}
	nbr = (char *)malloc(len + 1);
	if (nbr == 0)
		return (0);
	fill_nbr(nbr, n, len);
	return (nbr);
}
