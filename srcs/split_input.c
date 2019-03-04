/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:17:06 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/04 17:33:50 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checker(const char *str)
{
	int		index;

	if (*str == '\"')
		index = ft_strcspn(str + 1, "\"");
	else
		index = ft_strcspn(str + 1, "\'");
	return (str[index + 1] ? index : -1);
}

static int	parser(t_prgm *glob, const char *str)
{
	int		index;

	if (glob->error)
		return (glob->error);
	while (ft_strchr(SPACE"=", *str) && *str)
		str++;
	if (*str == '\0')
		return (0);
	if (ft_strchr("\"\'", *str))
	{
		if ((index = checker(str)) == -1)
			return (glob->error = UNCLOSED_COMMA);
		return (1 + parser(glob, str + index + 2));
	}
	else
		while (!ft_strchr(SPACE"=", *str) && *str)
			str++;
	return (1 + parser(glob, str));
}

static int	writer(t_prgm *glob, char const *str, char ***tab, int word)
{
	int		i;

	while (ft_strchr(SPACE"=", *str) && *str)
		str++;
	if (*str == '\0')
		return (1);
	if (ft_strchr("\"\'", *str))
	{
		i = checker(str);
		tab[0][word] = ft_strsub(str, 1, i);
		i += 2;
	}
	else
	{
		i = ft_strcspn(str, SPACE"=");
		tab[0][word] = ft_strsub(str, *str == '=' ? 1 : 0, i);
	}
	if (writer(glob, str + i, tab, word + 1) == 1)
		return (1);
	return (-1);
}

int			split_input(t_prgm *glob)
{
	if (glob->line == NULL)
		return (glob->error = NULL_ARG_PASSED);
	glob->tab.ac = parser(glob, glob->line);
	if (glob->error)
		return (glob->error);
	if (!(glob->tab.av = ft_memalloc(sizeof(char *) * (glob->tab.ac + 1))))
		return (glob->error = FAILED_MALLOC);
	if (writer(glob, glob->line, &glob->tab.av, 0) == -1)
		return (glob->error == FAILED_MALLOC);
	glob->tab.av[glob->tab.ac] = NULL;
	return (0);
}
