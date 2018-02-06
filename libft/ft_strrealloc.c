/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrealloc.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/06 16:26:43 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/06 16:26:47 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrealloc(char *str, char *to_append)
{
	char	*tmp;
	char	*str_pointer;
	char	*tmp_pointer;

	if (str == NULL || to_append == NULL ||
			(tmp = malloc(ft_strlen(str) + ft_strlen(to_append) + 1)) == NULL)
		return (NULL);
	str_pointer = str;
	tmp_pointer = tmp;
	while (*str)
		*tmp++ = *str++;
	ft_strdel(&str_pointer);
	while (*to_append)
		*tmp++ = *to_append++;
	*tmp = '\0';
	return (tmp_pointer);
}
