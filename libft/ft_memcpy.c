/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/24 18:16:34 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/01/25 23:21:48 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*ptd;
	char	*pts;

	i = 0;
	ptd = (char *)dst;
	pts = (char *)src;
	while (i != n)
	{
		ptd[i] = pts[i];
		i++;
	}
	ptd = pts;
	return (dst);
}
