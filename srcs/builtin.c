/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 15:34:18 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/07 21:19:20 by mmoya       ###    #+. /#+    ###.fr     */
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
	char	**bin;
	char	**aenv;
	int		i;
	int		y;

	y = 0;
	i = -1;
	while (arg[y])
		y++;
	aenv = malloc(sizeof(char*) * (y + 1));
	while (arg[++i])
		aenv[i] = ft_strdup(arg[i][0] == '$' ? sh_getenv(arg[i] + 1, env) : arg[i]);
	aenv[i] = NULL;
	bin = ft_strsplit(sh_getenv("PATH", env), ':');
	i = 0;
	while (bin[i])
	{
		if (sh_execute_path(bin[i++], aenv, env))
		{
			i = -1;
			while (aenv[++i])
				ft_strdel(&aenv[i]);
			free(aenv);
			i = -1;
			while (bin[++i])
				ft_strdel(&bin[i]);
			free(bin);
			return (1);
		}
	}
	return (0);

	/*
	pid_t		pid;
	char		*tmp;
	char		*tmp2;
	struct stat	path_stat;

	tmp2 = sh_getenv("PWD", env);
	tmp = ft_strjoin(tmp, arg[0]);
	stat(tmp, &path_stat);
	if (access(tmp, 0) == -1 || S_ISREG(path_stat.st_mode) == 0)
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
	if (pid != 0)
	{
		wait(NULL);
		ft_strdel(&tmp);
		return (1);
	}
	ft_strdel(&tmp);
	return (-1);
	*/
}
