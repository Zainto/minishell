/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 04:17:45 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/04 18:45:22 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

static int	replacer_var(t_prgm *glob, t_list *node, int index)
{
	t_variable	*holder;
	char		*tmp;
	int			len;
	int			diff;

	len = ft_strcspn(glob->line, "$");
	if (!node)
	{
		if (ft_asprintf(&tmp, "%.*s", len, glob->line) < 0)
			return (glob->error = FAILED_MALLOC);
	}
	else if (!(tmp = NULL))
	{
		holder = node->data;
		diff = len + index + 1;
		ft_asprintf(&tmp, "%.*s%s%s"
					, len, glob->line, holder->data, &glob->line[diff]);
		if (!tmp)
			return (glob->error = FAILED_MALLOC);
	}
	ft_strdel(&glob->line);
	glob->line = tmp;
	return (0);
}

int			replace_variable(t_prgm *glob)
{
	char	*str;
	char	*to_find;
	t_list	*node;

	if (!glob->line)
		return (glob->error = NULL_ARG_PASSED);
	str = glob->line;
	while (*str)
	{
		if (*str++ == '$')
		{
			to_find = ft_strsub(str, 0, ft_strcspn(str, " "));
			node = ft_lstfind(glob->env, to_find, varcmp);
			if (replacer_var(glob, node, ft_strlen(to_find)))
				return (glob->error);
			ft_strdel(&to_find);
			str = glob->line;
		}
		str += ft_strcspn(str, "$");
	}
	return (0);
}

static int	replacer_home(t_prgm *glob, int id, int flag)
{
	char	*tmp;
	char	*res;
	char	*str;
	int		diff;

	res = NULL;
	str = glob->line;
	diff = flag == 0 ? 1 : 2;
	if (flag == 0)
		tmp = ms_getenv(glob, "HOME");
	if (flag == 1)
		tmp = ms_getenv(glob, "PWD");
	if (flag == 2)
		tmp = ms_getenv(glob, "OLDPWD");
	if (ft_asprintf(&res, "%.*s%s%s", id, str, tmp, str + id + diff) < 0)
		return (glob->error = FAILED_MALLOC);
	ft_strdel(&glob->line);
	glob->line = res;
	return (0);
}

int			replace_home(t_prgm *glob)
{
	char	*str;
	int		id;
	int		ret;

	if (!glob->line)
		return (glob->error = NULL_ARG_PASSED);
	str = glob->line;
	id = 0;
	while (str[id])
	{
		if (str[id] == '~' && (id == 0 || str[id - 1] == ' '))
			ret = replacer_home(glob, id, 0);
		else if (ft_strequ(&str[id], "~+") && (id == 0 || str[id - 1] == ' '))
			ret = replacer_home(glob, id, 1);
		else if (ft_strequ(&str[id], "~-") && (id == 0 || str[id - 1] == ' '))
			ret = replacer_home(glob, id, 2);
		str = glob->line;
		id++;
		id += ft_strcspn(&str[id], "~");
	}
	return (0);
}

int			process_line(t_prgm *glob)
{
	ft_freetab(&glob->tab.av);
	ft_bzero(&glob->tab, sizeof(t_tab));
	ft_putstr("$> ");
	if (ft_getdelim(0, &glob->line, '\n') != 1)
		glob->error = FAILED_READ;
	if (!glob->error)
	{
		replace_variable(glob);
		replace_home(glob);
		split_input(glob);
	}
	if (!glob->tab.ac && !glob->error)
		glob->error = EMPTY_LINE;
	ft_strdel(&glob->line);
	return (1);
}
