/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 04:17:45 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 04:59:03 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replacer_var(t_prgm *glob, t_list *node, int index)
{
	t_variable	*holder;
	char		*tmp;
	int			len;

	len = ft_strcspn(glob->line, "$");
	if (!node)
	{
		if (ft_asprintf(&tmp, "%.*s", len, glob->line) < 0)
			return (glob->error = FAILED_MALLOC);
	}
	else if (!(tmp = NULL))
	{
		holder = node->data;
		ft_asprintf(&tmp, "%.*s%s%s"
				, len, glob->line, holder->data, glob->line + len + index + 1);
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

	if(!glob->line)
		return (glob->error = NULL_ARG);
	str = glob->line;
	while (*str)
	{
		if(*str++ == '$')
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

static int	replacer_home(t_prgm *glob, int id)
{
	char	*home;
	char	*res;
	char	*str;

	home = ms_getenv(glob, "HOME");
	res = NULL;
	str = glob->line;
	if(ft_asprintf(&res, "%.*s%s%s", id, str, home, str + id + 1) < 0)
		return (glob->error = FAILED_MALLOC);
	ft_strdel(&glob->line);
	glob->line = res;
	return (0);
}

int			replace_home(t_prgm *glob)
{
	char	*str;
	int		id;

	if (!glob->line)
		return (glob->error = NULL_ARG);;
	str = glob->line;
	id = 0;
	while(str[id])
	{
		if(str[id] == '~' && (id == 0 || str[id - 1] == ' '))
		{
			if(replacer_home(glob, id))
				return (glob->error);
			str = glob->line;
			id++;
		}
		id += ft_strcspn(&str[id], "~");
	}
	return (0);
}

int			process_line(t_prgm *glob)
{
	ft_freetab(&glob->tab.av);
	ft_strdel(&glob->line);
	ft_putstr("$> ");
	if (ft_getdelim(0, &glob->line, '\n') != 1)
		return (glob->error = FAILED_READ);
	if (replace_variable(glob))
		return (glob->error);
	if (replace_home(glob))
		return (glob->error);
	return (split_input(glob));
}
