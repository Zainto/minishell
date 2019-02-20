/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_getenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 03:27:13 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/20 08:20:31 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

int		NullArgName(void)
{
	t_prgm	glob;

	if (ft_getenv(&glob, NULL) == NULL)
		return (ISTRUE);
	else
		return (ISFALSE);
}

int		EmptyEnv(void)
{
	t_prgm	glob;

	glob.env = NULL;
	if (ft_getenv(&glob, "slt") == NULL)
		return (ISTRUE);
	else
		return (ISFALSE);
}

int		NoMatchFoundInEnv(void)
{
	t_prgm	glob;
	t_env	variable = {.name = "toto", .data = "tata"};

	glob.env = NULL;
	ft_lstadd(&glob.env, ft_lstnew(&variable, sizeof(t_env)));
	if (ft_getenv(&glob, "slt") == NULL)
		return (ISTRUE);
	else
		return (ISFALSE);
}

int		OneMatchFoundInEnv(void)
{
	t_prgm	glob;
	t_env	variable = {.name = "toto", .data = "tata"};

	glob.env = NULL;
	ft_lstadd(&glob.env, ft_lstnew(&variable, sizeof(t_env)));
	if (ft_getenv(&glob, "toto"))
		return (ISTRUE);
	else
		return (ISFALSE);
}

int		CorrectReturnIfMatchFound(void)
{
	t_prgm	glob;
	t_env	variable = {.name = "toto", .data = "tata"};

	glob.env = NULL;
	ft_lstadd(&glob.env, ft_lstnew(&variable, sizeof(t_env)));
	if (ft_strequ(ft_getenv(&glob, "toto"), "tata"))
		return (ISTRUE);
	else
		return (ISFALSE);
}

int		CorrectReturnIfSearchEnv(void)
{
	t_prgm	glob;

	glob_test_init(&glob);
	if (ft_strequ(ft_getenv(&glob, "totm"), "tatb"))
	{
		glob_test_destructor(&glob);
		return (ISTRUE);
	}
	return (ISFALSE);
}

int		test_ft_getenv(void)
{
	t_stack tests;

	ft_stckinit(&tests);
	ft_printf("%@s: \n", "39", "FT_GETENV");
	load_test(&tests, "NULL Name argument", NullArgName);
	load_test(&tests, "Empty Environement", EmptyEnv);
	load_test(&tests, "One Match found in environement", OneMatchFoundInEnv);
	load_test(&tests, "No match found in environement", NoMatchFoundInEnv);
	load_test(&tests, "Correct Value if match found", CorrectReturnIfMatchFound);
	load_test(&tests, "Correct Value if search env", CorrectReturnIfSearchEnv);
	return (run_test(&tests));
}
