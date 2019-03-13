/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 01:42:38 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/13 02:06:03 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replacer_var(t_prgm *glob, t_list *node, int index)
{
	t_variable	*holder;
	char		*tmp;
	int			len;
	int			diff;

	len = ft_strcspn(glob->line, "$");
	if (!(tmp = NULL) && !node)
	{
		if (ft_asprintf(&tmp, "%.*s", len, glob->line) < 0)
			return (glob->error = FAILED_MALLOC);
	}
	else
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
		if (*str == '$' && (!str[1] || ft_strchr(SPACE, str[1])))
			str++;
		else if (*str == '$' && str[1])
		{
			to_find = ft_strsub(str, 1, ft_strcspn(str, " "));
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
		tmp = ms_getenv(glob, &glob->env, "HOME");
	if (flag == 1)
		tmp = ms_getenv(glob, &glob->env, "PWD");
	if (flag == 2)
		tmp = ms_getenv(glob, &glob->env, "OLDPWD");
	if (ft_asprintf(&res, "%.*s%s%s", id, str, tmp, str + id + diff) < 0)
		return (glob->error = FAILED_MALLOC);
	ft_strdel(&glob->line);
	glob->line = res;
	return (0);
}

int			replace_home(t_prgm *glob)
{
	char	*str;
	int		i;
	int		ret;

	if (!glob->line)
		return (glob->error = NULL_ARG_PASSED);
	str = glob->line;
	i = 0;
	while (str[i])
	{
		if (ft_strnequ(&str[i], "~-", 2) && (i == 0 || str[i - 1] == ' '))
			ret = replacer_home(glob, i, 2);
		else if (ft_strnequ(&str[i], "~+", 2) && (i == 0 || str[i - 1] == ' '))
			ret = replacer_home(glob, i, 1);
		else if (ft_strnequ(&str[i], "~/", 2) && (i == 0 || str[i - 1] == ' '))
			ret = replacer_home(glob, i, 0);
		else if (str[i] == '~' && !str[i + 1] && (i == 0 || str[i - 1] == ' '))
			ret = replacer_home(glob, i, 0);
		str = glob->line;
		i++;
		i += ft_strcspn(&str[i], "~");
	}
	return (0);
}
