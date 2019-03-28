/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_qsort.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 12:38:57 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 12:22:33 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static size_t	choose_pivot(void *base, size_t szof,
		int (*compar)(const void *, const void *))
{
	if (compar(&base[0], &base[szof]) && compar(&base[0], &base[szof * 2]))
	{
		if (compar(&base[szof], &base[szof * 2]))
			return (szof);
		else
			return (szof * 2);
	}
	if (compar(&base[szof], &base[0]) && compar(&base[szof], &base[szof * 2]))
	{
		if (compar(&base[0], &base[szof * 2]))
			return (0);
		else
			return (szof * 2);
	}
	if (compar(&base[0], &base[szof]))
		return (0);
	return (szof);
}

static void		qswap(void *a, void *b, const size_t szof)
{
	unsigned char s[szof];

	ft_memcpy(s, a, szof);
	ft_memcpy(a, b, szof);
	ft_memcpy(b, s, szof);
}

static int		pivot_sort(void *base, size_t len, size_t szof,
		int (*compar)(const void *, const void *))
{
	size_t pivot;
	size_t i;
	size_t j;

	pivot = choose_pivot(base, szof, compar) / szof;
	len = len - 1;
	qswap(&base[len * szof], &base[pivot * szof], szof);
	j = 0;
	i = 0;
	while (i < len)
	{
		if (compar(&base[i * szof], &base[len * szof]))
		{
			qswap(&base[i * szof], &base[j * szof], szof);
			j++;
		}
		i++;
	}
	qswap(&base[j * szof], &base[len * szof], szof);
	return (j);
}

int				ft_qsort(void *base, size_t len, size_t szof,
		int (*compar)(const void *, const void *))
{
	size_t pivot;

	if (compar(&pivot, &pivot) != 1)
		return (-1);
	if (len > 2)
	{
		pivot = pivot_sort(base, len, szof, compar);
		ft_qsort(base, pivot, szof, compar);
		ft_qsort(base + pivot * szof, len - pivot, szof, compar);
	}
	else if (!compar(&base[0], &base[szof]))
		qswap(&base[0], &base[szof], szof);
	return (1);
}
