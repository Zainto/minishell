/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 01:42:38 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/13 06:20:10 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replacer_var(t_prgm *glob, t_list *node, int index, char **str)
{
	t_variable	*holder;
	char		*tmp;
	int			len;
	int			diff;

	len = ft_strcspn(*str, "$");
	if (!(tmp = NULL) && !node)
	{
		if (ft_asprintf(&tmp, "%.*s", len, *str) < 0)
			return (glob->error = FAILED_MALLOC);
	}
	else
	{
		holder = node->data;
		diff = len + index + 1;
		ft_asprintf(&tmp, "%.*s%s%s"
					, len, *str, holder->data, &str[0][diff]);
		if (!tmp)
			return (glob->error = FAILED_MALLOC);
	}
	ft_strdel(str);
	*str = tmp;
	return (0);
}

int			replace_variable(t_prgm *glob, char **str)
{
	char	*to_find;
	int		i;
	t_list	*node;

	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '$' && (!str[0][i + 1]
				|| ft_strchr(SPACE, str[0][i + 1])))
			i++;
		else if (str[0][i] == '$' && str[0][i + 1])
		{
			i++;
			to_find = ft_strsub(&str[0][i], 0, ft_strcspn(&str[0][i], " $"));
			node = ft_lstfind(glob->env, to_find, varcmp);
			if (replacer_var(glob, node, ft_strlen(to_find), str))
				return (glob->error);
			ft_strdel(&to_find);
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

static int	replacer_home(t_prgm *glob, int id, int flag, char **str)
{
	char	*tmp;
	char	*res;
	int		diff;

	res = NULL;
	diff = flag == 0 ? 1 : 2;
	if (flag == 0)
		tmp = ms_getenv(glob, &glob->env, "HOME");
	if (flag == 1)
		tmp = ms_getenv(glob, &glob->env, "PWD");
	if (flag == 2)
		tmp = ms_getenv(glob, &glob->env, "OLDPWD");
	if (ft_asprintf(&res, "%.*s%s%s", id, *str, tmp, *str + id + diff) < 0)
		return (glob->error = FAILED_MALLOC);
	ft_strdel(str);
	*str = res;
	return (0);
}

static int	replace_home(t_prgm *glob, char **str)
{
	int		i;
	int		ret;

	i = 0;
	while (str[0][i])
	{
		if (ft_strnequ(*str + i, "~-", 2) && (i == 0 || str[0][i - 1] == ' '))
			ret = replacer_home(glob, i, 2, str);
		if (ft_strnequ(*str + i, "~+", 2) && (i == 0 || str[0][i - 1] == ' '))
			ret = replacer_home(glob, i, 1, str);
		if (ft_strnequ(*str + i, "~/", 2) && (i == 0 || str[0][i - 1] == ' '))
			ret = replacer_home(glob, i, 0, str);
		if (ft_strnequ(*str + i, "~ ", 2) && (i == 0 || *(*str + i - 1) == ' '))
			ret = replacer_home(glob, i, 0, str);
		if (ft_strequ(*str + i, "~"))
			ret = replacer_home(glob, i, 0, str);
		i++;
	}
	return (0);
}

int			replacer(t_prgm *glob)
{
	int		index;

	index = 1;
	while (glob->tab.av[index])
	{
		replace_variable(glob, &glob->tab.av[index]);
		replace_home(glob, &glob->tab.av[index]);
		index++;
	}
	return (glob->error);
}
