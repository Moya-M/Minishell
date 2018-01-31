/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 16:43:28 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 18:21:06 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int		sh_builtin(char **arg, char **env)
{
	char *cur;
	
	cur = ft_strnew(50);
	if (ft_strnstr(arg[0], "cd", 2) && arg[0][2] == '\0')
	{
		sh_cd(arg[1], env);
		return (1);
	}
	if (ft_strnstr(arg[0], "pwd", 3) && arg[0][3] == '\0')
	{
		sh_pwd(env);
		return (1);
	}
	return (0);
}

void	sh_prompt(char **env)
{
	int		i;
	char	*home;

	i = 0;
	while (!ft_strnstr(env[i], "HOME=", 5))
		i++;
	home = env[i];
	i = 0;
	while (!ft_strnstr(env[i], "PWD=", 4))
		i++;
	ft_putstr("\e[1m@ \e[34;1m");
	if (ft_strstr(env[i], home))
		ft_putstr("~");
	else
		ft_putstr(ft_strrchr(env[i], '/') + 1);
	ft_putstr("\e[31m ▶ \e[0m");
}

void	sh_cmd(char **env)
{
	char	*line;
	char	**arg;

	if (env[0])
		;
	get_next_line(1, &line);
	arg = ft_strsplit(line, ' ');
	if (!sh_builtin(arg, env))
	{
		ft_putstr("miniSH: command not found: ");
		ft_putstr(arg[0]);
		ft_putstr("\n");
	}
	// printf("%s\n", line);
}

char	**sh_environ(char **environ)
{
	char	**env;
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (environ[i])
		size += ft_strlen(environ[i++]);
	if (!(env = malloc(size)))
		return (NULL);
	printf("%zu\n", size);
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
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
		sh_cmd(env);
	}
	return (0);
}
