/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 15:34:18 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/06 14:34:08 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int		sh_cd(char *path, char ***env)
{
	char	**test;
	char	*cur;
	int		i;

	if (path == NULL)
		path = sh_getenv("HOME", *env);
	if (!cd_error(path))
		return (-1);
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

int		sh_unsetenv(char **env)
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

int		sh_execute(char **arg, char **env)
{
	pid_t	pid;
	char	*tmp;

	tmp = ft_strjoin("/bin/", arg[0]);
	if (access(tmp, 0) == -1)
	{
		ft_strdel(&tmp);
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(tmp, arg, env);
		ft_putstr("\e[31mFork: ERROR\e[0m\n");
	}
	ft_strdel(&tmp);
	if (pid != 0)
	{
		wait(NULL);
		return (1);
	}
	return (-1);
}
