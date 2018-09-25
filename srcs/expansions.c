/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expansions.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/19 16:29:14 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/09/25 14:26:50 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	dollar_expansion(char **arg, char **env, int i, int j)
{
	char *tmp;
	char *tmp2;

	tmp = arg[i];
	if (!(tmp2 = ft_strndup(tmp, j - 1)))
		return (1);
	dprintf(1, "%s\n", tmp2);
	if (sh_getenv(arg[i] + j, env))
	{
		if (!(arg[i] = ft_strjoin(tmp2, sh_getenv(arg[i] + j, env))))
			return (1);
		ft_strdel(&tmp2);
	}
	else
	{
		if (!(arg[i] = tmp2))
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
	int		j;

	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '~' && (arg[i][1] == '/' || arg[i][1] == 0))
			tilde_expansion(arg, env, i);
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] == '$')
			{
				dollar_expansion(arg, env, i, j + 1);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
