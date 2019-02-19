/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 20:45:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/19 00:46:01 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	parser(char const *str)
{
	while (ft_strchr(" =", *str) && *str)
		str++;
	if (*str == '\0')
		return (0);
	if (ft_strchr("\"\'", *str))
	{
		if (*str == '\"')
			str += ft_strcspn(str + 1, "\"");
		else
			str += ft_strcspn(str + 1, "\'");
		if (!*str)
			return (-1);
		return (1 + parser(str + 2));
	}
	else
	{
		while (!ft_strchr(" =", *str) && *str)
			str++;
	}
	return (1 + parser(str));
}

static int	writer(char const *str, char ***tab, int word)
{
	int		i;

	while (ft_strchr(" =", *str) && *str)
		str++;
	if (*str == '\0')
		return (1);
	if (ft_strchr("\"\'", *str))
	{
		if (*str == '\"')
			i = ft_strcspn(str + 1, "\"");
		else
			i = ft_strcspn(str + 1, "\'");
		tab[0][word] = ft_strsub(str, 1, i);
		i += 2;
	}
	else
	{
		i = ft_strcspn(str, " =");
		tab[0][word] = ft_strsub(str, *str == '=' ? 1 : 0, i);
	}
	if (writer(str + i, tab, word + 1) == 1)
		return (1);
	return (-1);
}

t_tab		*split_input(char const *str)
{
	t_tab	*args;

	if (!str)
		return (NULL);
	args = ft_memalloc(sizeof(t_tab));
	args->ac = parser(str);
	if (!(args->av = (char **)ft_memalloc(sizeof(char *) * (args->ac + 1))))
		return (NULL);
	if (writer(str, &args->av, 0) == -1)
		return (NULL);
	args->av[args->ac] = NULL;
	return (args);
}

void		destructor(t_prgm *glob, t_tab *args)
{
	ft_strdel (&glob->line);
	ft_freetab(&args->av);
	free(args);
	args = NULL;
}

int			main(int ac, char **av, char **env)
{
	t_prgm		glob;
	//t_list		*exec;
	t_tab		*args;
	int			status;

	ft_bzero(&glob, sizeof(t_prgm));
	glob.args = ft_getargslst(ac, av);
	envsetup(&glob, env);
	status = 1;
	while (status == 1)
	{
		ft_putstr("> : ");
		status = ft_getdelim(0, &glob.line, '\n');
		args = split_input(glob.line);
		status = builtin(&glob, args);
		destructor(&glob, args);
		//exec = generate_path(&glob);
		//ft_lstiter(exec, print_exec);
		if (status == -1)
		{
			ft_printf("An error occured\n");
			status = 1;
		}
	}
	return (0);
}
