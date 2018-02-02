/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/01 15:58:55 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/02 21:17:19 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

static void		setenv_free(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_strdel(&env[i++]);
	}
	free(env);
}

static int		setenv_alloc(char *name, char *value, char **old, char ***ptr)
{
	char	**tmp;
	char	*tmp2;
	int		i;
	int		j;

	if (name || value)
		;
	i = 0;
	j = 0;
	tmp = *ptr;
	while (old[i + j])
	{
		if (ft_strnstr(old[i + j], name, ft_strlen(name)))
		{
			j++;
			continue;
		}
		tmp[i] = ft_strdup(old[i + j]);
		i++;
	}
	tmp2 = ft_strjoin("=", value);
	if (!(tmp[i] = ft_strjoin(name, tmp2)))
		return (-1);
	ft_strdel(&tmp2);
	tmp[i + 1] = NULL;
	setenv_free(old);
	return (1);
}

int				sh_setenv(char *name, char *value, char ***env)
{
	char	**tmp;
	char	**old;
	int		i;
	int		j;

	i = 0;
	j = 0;
	old = *env;
	while (old[i])
	{
		if (ft_strnstr(old[i], name, ft_strlen(name)))
			j++;
		i++;
	}
	//i += j;
	if (!(tmp = malloc(sizeof(char*) * (i + 1))))
		return (-1);
	if (setenv_alloc(name, value, old, &tmp) == -1)
		return (-1);
	*env = tmp;
	return (1);
}
