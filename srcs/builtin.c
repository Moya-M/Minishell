/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 15:34:18 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/04/07 19:42:38 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		sh_cd(char **arg, char ***env)
{
	char	*cur;
	char	*new;

	new = arg[1];
	if (new == NULL)
		if ((new = sh_getenv("HOME", *env)) == 0)
			new = ".";
	if (ft_strcmp(new, "-") == 0)
		if ((new = sh_getenv("OLDPWD", *env)) == 0)
			new = ".";
	if (cd_error(new) != 1)
		return (1);
	(cur = ft_strnew(PATH_MAX)) ? 0 : sh_exit(-1, arg, *env);
	if (chdir(new) == 0)
	{
		cur = getcwd(cur, PATH_MAX);
		if (sh_setenv("OLDPWD", sh_getenv("PWD", *env), env) ||
		sh_setenv("PWD", cur, env))
			sh_exit(-1, arg, *env);
		ft_strcmp(new, "-") ? 0 : sh_pwd(*env);
		ft_strdel(&cur);
		return (0);
	}
	return (1);
}

int		sh_pwd(char **env)
{
	char	*cur;
	char	*tmp;

	(void)env;
	if (!(cur = ft_strnew(PATH_MAX + 1)))
		sh_exit(-1, NULL, env);
	cur = getcwd(cur, PATH_MAX);
	tmp = ft_strjoin(cur, "\n");
	ft_putstr(tmp);
	ft_strdel(&cur);
	ft_strdel(&tmp);
	return (0);
}

int		sh_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		ft_putendl(env[i++]);
	return (0);
}

int		sh_unsetenv(char **arg, char ***ptr)
{
	int		i;
	int		j;
	size_t	len;
	char	**env;

	i = -1;
	j = 0;
	if (arg[1] == NULL)
		return (err_usage("unsetenv key"));
	len = ft_strlen(arg[1]);
	env = *ptr;
	while (env[++i])
	{
		if (ft_strncmp(env[i], arg[1], len) == 0 && env[i][len] == '=')
			j++;
		if (j)
		{
			ft_strdel(&env[i]);
			if (env[i + j] == NULL)
				env[i] = NULL;
			else
				!(env[i] = ft_strdup(env[i + j])) ? sh_exit(-1, arg, env) : 0;
		}
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
