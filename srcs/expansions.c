/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   expansions.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/19 16:29:14 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/09/20 23:45:52 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
static int	env_exp(const char *line, int i, char **env)
{
	int		j;
	int		k;
	char	*tmp;

	k = 0;
	j = i;
	while (!ft_isspace(line[j]) && line[j])
		j++;
	tmp = ft_strndup(line + i + 1, j - i - 1);
	dprintf(1, "TMP = %s\n", tmp);
	k += ft_strlen(sh_getenv(tmp, env));
	ft_strdel(&tmp);
	k -= j;
	return (k);
}

static int	prompt_length(const char *line, char **env)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (line[i])
	{
		dprintf(1, "k = %i c = %c\n", k, line[i]);
		if (line[i] == '$')
			k += env_exp(line, i, env);
		i++;
		k++;
	}
	return (k);
}

int    	sh_expansions(const char *line, char **env)
{
	return (prompt_length(line, env));
}
*/

int    	sh_expansions(char **arg, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	(void)env;
	while (arg[i])
	{
		if (arg[i][0] == '$')
		{
			tmp = arg[i];
			if (sh_getenv(arg[i] + 1, env))
				arg[i] = ft_strdup(sh_getenv(arg[i] + 1, env));
			else
				arg[i] = ft_strnew(0);
			ft_strdel(&tmp);
		}
		if (arg[i][0] == '~')
		{
			tmp = arg[i];
			if (sh_getenv("HOME", env))
			{
				arg[i] = ft_strjoin(sh_getenv("HOME", env), arg[i] + 1);
				ft_strdel(&tmp);
			}
		}
		i++;
	}
	return (0);
}