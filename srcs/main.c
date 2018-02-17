/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 16:43:28 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/16 00:24:56 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>
#include <curses.h>
#include <term.h>

int		sh_builtin(char **arg, char ***env, int out)
{
	if (*arg == NULL)
		return (0);
	else if (ft_strnstr(arg[0], "cd", 2) && arg[0][2] == '\0')
		return (sh_cd(arg, env));
	else if (ft_strnstr(arg[0], "pwd", 3) && arg[0][3] == '\0')
		return (sh_pwd(*env));
	else if (ft_strnstr(arg[0], "env", 3) && arg[0][3] == '\0')
		return (sh_env(*env));
	else if (ft_strnstr(arg[0], "setenv", 6) && arg[0][6] == '\0')
		return (sh_setenv(arg[1], arg[2], env));
	else if (ft_strnstr(arg[0], "unsetenv", 8) && arg[0][8] == '\0')
		return (sh_unsetenv(arg, env));
	else if (ft_strnstr(arg[0], "echo", 4) && arg[0][4] == '\0')
		return (sh_echo(arg, *env));
	else if (ft_strnstr(arg[0], "exit", 4) && arg[0][4] == '\0')
		return(sh_exit(out, arg, *env));
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
	home = sh_getenv("HOME", env);
	getcwd(pwd, PATH_MAX);
	ft_putstr("\e[31;1m● \e[34m");
	if (ft_strcmp(home, pwd))
		ft_putstr(ft_strrchr(pwd, '/') + 1);
	else
		ft_putstr("~");
	ft_putstr("\e[37m $> \e[0m");
	ft_strdel(&pwd);
}

int		sh_cmd(char ***env)
{
	char			*line;
	char			**arg;
	int				i;
	static int		out = 0;

	get_next_line(1, &line);
	!(arg = ft_strsplit(line, ' ')) ? sh_exit(-1, NULL, *env) : 0;
	i = 0;
	while (arg[i])
		i++;
	ft_strdel(&line);
	if ((out = sh_builtin(arg, env, out)) == -1)
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(arg[0]);
		ft_putstr("\n");
	}
	if (out == -1)
		out = 1;
	while (arg[i])
		ft_strdel(&arg[--i]);
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
	int		i;
	int		out;
	char	**env;

	env = sh_environ(environ);
	i = 0;
	if (av[ac])
		;
	while (1)
	{
		sh_prompt(env);
		out = sh_cmd(&env);
	}
	return (out);
}
