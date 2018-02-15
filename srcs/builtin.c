/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 15:34:18 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/15 13:45:03 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		sh_cd(char *path, char ***env)
{
	char	**test;
	char	*cur;
	int		i;

	if (path == NULL)
		path = sh_getenv("HOME", *env);
	if (cd_error(path) != 1)
		return (1);
	dprintf(1, "FAR");
	i = 0;
	test = *env;
	cur = ft_strnew(PATH_MAX);
	chdir(path);
	cur = getcwd(cur, PATH_MAX);
	sh_setenv("PWD", cur, env);
	ft_strdel(&cur);
	return (0);
}

int		sh_pwd(char **env)
{
	char	*cur;

	if (env[0])
		;
	cur = ft_strnew(PATH_MAX + 1);
	cur = getcwd(cur, PATH_MAX);
	ft_putstr(ft_strcat(cur, "\n"));
	ft_strdel(&cur);
	return (0);
}

int		sh_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i++]);
		ft_putchar('\n');
	}
	return (0);
}

int		sh_unsetenv(char **arg, char ***ptr)
{
	int		i;
	int		j;
	size_t	len;
	char	**env;

	i = 0;
	j = 0;
	len = ft_strlen(arg[1]);
	env = *ptr;
	while (env[i])
	{
		if (ft_strncmp(env[i], arg[1], len) == 0 && env[i][len] == '=')
			j++;
		if (j)
		{
			ft_strdel(&env[i]);
			if (env[i + j] == NULL)
				env[i] = NULL;
			else
				env[i] = ft_strdup(env[i + j]);
		}
		i++;
	}
	return (0);
}

int		sh_execute(char **arg, char **env)
{
	char	**bin;
	int		i;
	int		r;

	i = 0;
	bin = ft_strsplit(sh_getenv("PATH", env), ':');
	while (bin[i])
	{
		if ((r = sh_execute_path(bin[i++], arg, env)) != -1)
		{
			i = -1;
			while (bin[++i])
				ft_strdel(&bin[i]);
			free(bin);
			return (r);
		}
	}
	i = -1;
	while (bin[++i])
		ft_strdel(&bin[i]);
	free(bin);
	return (-1);
}
