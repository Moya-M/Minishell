/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 16:43:28 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/02/06 17:52:39 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <curses.h>
#include <term.h>

int		sh_builtin(char **arg, char ***env)
{
	if (!arg[0])
		return (1);
	else if (ft_strnstr(arg[0], "cd", 2) && arg[0][2] == '\0')
		return (sh_cd(arg[1], env));
	else if (ft_strnstr(arg[0], "pwd", 3) && arg[0][3] == '\0')
		return (sh_pwd(*env));
	else if (ft_strnstr(arg[0], "env", 3) && arg[0][3] == '\0')
		return (sh_env(*env));
	else if (ft_strnstr(arg[0], "setenv", 6) && arg[0][6] == '\0')
		return (sh_setenv(arg[1], arg[2], env));
	else
		return(sh_execute(arg, *env));
	return (0);
}

void	sh_prompt(char **env)
{
	int		i;
	char	*pwd;
	char	*home;

	i = 0;
	pwd = ft_strnew(PATH_MAX);
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

void	sh_cmd(char ***env)
{
	char	*line;
	char	**arg;
	int		i;

	get_next_line(1, &line);
	arg = ft_strsplit(line, ' ');
	ft_strdel(&line);
	if (!(i = sh_builtin(arg, env)))
	{
		ft_putstr("miniSH: command not found: ");
		ft_putstr(arg[0]);
		ft_putstr("\n");
	}
	i = -1;
	while (arg[++i])
		ft_strdel(&arg[i]);
	free(arg);
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
		return (NULL);
	printf("%i\n", i);
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int		main(int ac, char **av, char **environ)
{
	int		i;
	char	**env;

	env = sh_environ(environ);
	i = 0;
	if (av[ac])
		;
	while (1)
	{
		sh_prompt(env);
		sh_cmd(&env);
	}
	return (0);
}
