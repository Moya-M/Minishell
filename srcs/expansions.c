/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expansions.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/19 16:29:14 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 23:55:29 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	dollar_expansion(char **arg, char **env, int i)
{
	char *tmp;

	tmp = arg[i];
	if (sh_getenv(arg[i] + 1, env))
	{
		if (!(arg[i] = ft_strdup(sh_getenv(arg[i] + 1, env))))
			return (1);
	}
	else
	{
		if (!(arg[i] = ft_strnew(0)))
			return (1);
	}
	ft_strdel(&tmp);
	return (0);
}

static int	tilde_expansion(char **arg, char **env, int i)
{
	char *tmp;

	tmp = arg[i];
	if (sh_getenv("HOME", env))
	{
		if (!(arg[i] = ft_strjoin(sh_getenv("HOME", env), arg[i] + 1)))
			return (1);
		ft_strdel(&tmp);
	}
	return (0);
}

int			sh_expansions(char **arg, char **env)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '$')
			dollar_expansion(arg, env, i);
		if (arg[i][0] == '~')
			tilde_expansion(arg, env, i);
		i++;
	}
	return (0);
}
