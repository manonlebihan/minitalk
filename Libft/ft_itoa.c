/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:58:16 by mle-biha          #+#    #+#             */
/*   Updated: 2022/06/17 16:43:33 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_input_length(int n)
{
	int	i;
	int	nb;

	nb = n;
	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	if (nb < 0 || i == 0)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			len;
	int			i;
	long int	nb;

	nb = n;
	i = 0;
	len = ft_input_length(nb);
	res = ft_calloc((len + 1), sizeof(char));
	if (res == NULL)
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		res[0] = '-';
		i++;
	}
	while (len > i)
	{
		len--;
		res[len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (res);
}
