/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   setenv.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/01 15:58:55 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/20 13:18:09 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		setenv_free(char **env)
{
	int i;

	i = 0;
	while (env[i])
		ft_strdel(&env[i++]);
	free(env);
}

static int		setenv_alloc(char *name, char *value, char **old, char ***ptr)
{
	char	**tmp;
	char	*tmp2;
	int		i;
	int		j;

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
		if (!(tmp[i] = ft_strdup(old[i + j])))
			sh_exit(-1, NULL, NULL);
		i++;
	}
	!(tmp2 = ft_strjoin("=", value)) ? sh_exit(-1, NULL, NULL) : 0;
	!(tmp[i] = ft_strjoin(name, tmp2)) ? sh_exit(-1, NULL, NULL) : 0;
	ft_strdel(&tmp2);
	tmp[i + 1] = NULL;
	setenv_free(old);
	return (1);
}

int				setenv_modify(char *name, char *value, char ***ptr_env)
{
	char	**env;
	char	*tmp;
	int		i;

	env = *ptr_env;
	if ((i = sh_getenv_id(name, env)) != -1)
	{
		ft_strdel(&env[i]);
		!(tmp = ft_strjoin(name, "=")) ? sh_exit(-1, NULL, NULL) : 0;
		!(env[i] = ft_strjoin(tmp, value)) ? sh_exit(-1, NULL, NULL) : 0;
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

int				sh_setenv(char *name, char *value, char ***env, int cmd)
{
	char	**tmp;
	char	**old;
	int		i;

	i = 0;
	if (!name || !value)
		return (cmd ? err_usage("setenv key value") : 1);
	if (setenv_modify(name, value, env))
		return (0);
	old = *env;
	while (old[i])
		i++;
	!((tmp = malloc(sizeof(char*) * (i + 2)))) ? sh_exit(-1, NULL, NULL) : 0;
	if (setenv_alloc(name, value, old, &tmp) == -1)
		return (1);
	*env = tmp;
	return (0);
}
