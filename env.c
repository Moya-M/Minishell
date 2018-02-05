/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/05 14:32:00 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/05 15:12:35 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_getenv(char *key, char **env)
{
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(key);
	while (env[i])
	{
		if (ft_strnstr(env[i], key, size))
			break ;
		i++;
	}
	if (env[i] != NULL)
		return (env[i] + size + 1);
	return (NULL);
}
