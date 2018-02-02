/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 15:34:18 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/02 21:41:09 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int		sh_cd(char *path, char ***env)
{
	char	**test;
	char	*cur;
	int		i;

	i = 0;
	test = *env;
	cur = ft_strnew(PATH_MAX);
	chdir(path);
	cur = getcwd(cur, PATH_MAX);
	sh_setenv("PWD", cur, env);
	ft_strdel(&cur);
	return (1);
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
	return (1);
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
	return (1);
}
