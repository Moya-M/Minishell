/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 16:43:28 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/09/21 16:22:51 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		sh_builtin(char **arg, char ***env, int out)
{
	if (*arg == NULL || arg[0][0] == 0)
		return (0);
	else if (ft_strcmp(arg[0], "cd") == 0)
		return (sh_cd(arg, env));
	else if (ft_strcmp(arg[0], "pwd") == 0)
		return (sh_pwd(*env));
	else if (ft_strcmp(arg[0], "env") == 0)
		return (sh_env(*env));
	else if (ft_strcmp(arg[0], "setenv") == 0)
		return (sh_setenv(arg[1], arg[2], env, 1));
	else if (ft_strcmp(arg[0], "unsetenv") == 0)
		return (sh_unsetenv(arg[1], *env));
	else if (ft_strcmp(arg[0], "echo") == 0)
		return (sh_echo(arg, *env));
	else if (ft_strcmp(arg[0], "exit") == 0)
		return (sh_exit(out, arg, *env));
	else if (ft_strnstr(arg[0], "./", 2) || ft_strnstr(arg[0], "../", 3) ||
	ft_strnstr(arg[0], "/", 1))
		return (sh_execute_path(NULL, arg, *env));
	else if (sh_getenv("PATH", *env) != NULL)
		return (sh_execute(arg, *env));
	return (-1);
}

void	sh_prompt(char **env)
{
	int		i;
	char	*pwd;
	char	*home;

	i = 0;
	!(pwd = ft_strnew(PATH_MAX)) ? sh_exit(-1, NULL, env) : 0;
	getcwd(pwd, PATH_MAX);
	home = sh_getenv("HOME", env);
	ft_putstr("\e[1;36m");
	if (home == NULL)
		home = ".";
	if (ft_strcmp(home, pwd) == 0)
		ft_putstr("~");
	else if (ft_strncmp(home, pwd, ft_strlen(home)))
		ft_putstr(ft_strrchr(pwd, '/'));
	else
		ft_putstr(ft_strrchr(pwd, '/') + 1);
	ft_putstr("\e[1;33m $ \e[0m");
	ft_strdel(&pwd);
}

int		sh_cmd(char ***env)
{
	char			*line;
	char			**arg;
	int				i;
	int				j;
	static int		out = 0;

	i = 0;
	j = 0;
	!(get_next_line(1, &line)) ? sh_exit(-1, NULL, *env) : 0;
	!(arg = ft_strsplitq(line)) ? sh_exit(-1, NULL, *env) : 0;
	sh_expansions(arg, *env);
	while (arg[i])
		i++;
	ft_strdel(&line);
	if ((out = sh_builtin(arg, env, out)) == -1)
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(arg[0]);
	}
	if (out == -1)
		out = 1;
	while (--i >= 0)
		ft_strdel(&arg[i]);
	free(arg);
	return (out);
}

char	**sh_environ(char **environ)
{
	char	**env;
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (environ[i])
		i++;
	if (!(env = (char**)malloc(sizeof(char*) * (i + 1))))
		sh_exit(-1, NULL, NULL);
	i = 0;
	while (environ[i])
	{
		if (!(env[i] = ft_strdup(environ[i])))
			sh_exit(-1, NULL, NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int		main(int ac, char **av, char **environ)
{
	int		out;
	char	**env;

	(void)ac;
	(void)av;
	env = sh_environ(environ);
	while (1)
	{
		sh_prompt(env);
		out = sh_cmd(&env);
	}
	return (1);
}
