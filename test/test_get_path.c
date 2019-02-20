/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_load_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 06:22:24 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/20 07:36:50 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include <fcntl.h>

int		PathCorrectlyIfNoPathInEnv(void)
{
	t_prgm	glob;

	glob.env = NULL;
	if (ft_strequ(get_path(&glob), NO_ENV_PATH))
		return (ISTRUE);
	else
		return (ISFALSE);
}

int		PathLoadedCorrectlyIfInEnv(void)
{
	t_prgm	glob;
	t_env	path = {.name = "PATH", .data = ENV_PATH};

	glob.env = NULL;
	ft_lstadd(&glob.env, ft_lstnew(&path, sizeof(t_env)));
	if (ft_strequ(get_path(&glob), ENV_PATH))
		return (ISTRUE);
	else
		return (ISFALSE);
}

int		test_get_path(void)
{
	t_stack tests;

	ft_stckinit(&tests);
	ft_printf("%@s: \n", "39", "GET_PATH");
	load_test(&tests, "Path Loaded Correctly if no PATH in env"\
			, PathCorrectlyIfNoPathInEnv);
	load_test(&tests, "Path Loaded Correctly With a PATH in env"\
			, PathLoadedCorrectlyIfInEnv);
	return (run_test(&tests));
}
