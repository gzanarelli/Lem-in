/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 00:01:38 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 19:14:28 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	nb;
	char			stmp[12];
	int				i;

	i = 0;
	nb = n < 0 ? -n : n;
	while (nb > 0)
	{
		stmp[i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	if (n < 0)
	{
		stmp[i] = '-';
		i++;
	}
	if (n == 0)
	{
		stmp[i] = '0';
		i++;
	}
	stmp[i] = '\0';
	ft_strrev(stmp);
	ft_putstr(stmp);
}
