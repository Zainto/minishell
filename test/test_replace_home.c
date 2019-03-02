/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_replace_home.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 00:46:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 01:39:31 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

static int		NullArg(void)
{
	t_prgm	glob;

	glob.line = NULL;
	if (replace_home(&glob) == NULL_ARG_PASSED)
		return (ISTRUE);
	return (ISFALSE);
}

static int		NoReplacement(void)
{
	t_prgm	glob;

	glob.line = ft_strdup("Salut");
	replace_home(&glob);
	if (ft_strequ("Salut", glob.line))
		return (ISTRUE);
	ft_printf("//expected : %s | result : |%s| \\\\", "Salut", glob.line);
	return (ISFALSE);
}

static int		OneReplacement(void)
{
	t_prgm	glob;

	glob_test_init(&glob);
	glob.line = ft_strdup("~");
	replace_home(&glob);
	if (ft_strequ(HOME, glob.line))
	{
		glob_test_destructor(&glob);
		return (ISTRUE);
	}
	ft_printf("expected : %s | result : |%s|", HOME, glob.line);
	glob_test_destructor(&glob);
	return (ISFALSE);
}

static int		ValidReplacement(void)
{
	t_prgm	glob;

	glob_test_init(&glob);
	glob.line = ft_strdup("echo ~");
	replace_home(&glob);
	if (ft_strequ("echo " HOME, glob.line))
	{
		glob_test_destructor(&glob);
		return (ISTRUE);
	}
	ft_printf("expected : %s | result : |%s|","echo " HOME, glob.line);
	glob_test_destructor(&glob);
	return (ISFALSE);
}

static int		MultipleReplacement(void)
{
	t_prgm	glob;

	glob_test_init(&glob);
	glob.line = ft_strdup("echo ~ ~ ~");
	replace_home(&glob);
	if (ft_strequ("echo " HOME " " HOME" "HOME, glob.line))
	{
		glob_test_destructor(&glob);
		return (ISTRUE);
	}
	ft_printf("\nexpected : %s | result : |%s|","echo "HOME" "HOME" "HOME, glob.line);
	glob_test_destructor(&glob);
	return (ISFALSE);
}

int		test_replace_home(void)
{
	t_stack tests;

	ft_stckinit(&tests);
	ft_printf("%@s: \n", "39", "REPLACE HOME");
	load_test(&tests, "Multiple Replacement", MultipleReplacement);
	load_test(&tests, "Valid Replacement", ValidReplacement);
	load_test(&tests, "One Replacement", OneReplacement);
	load_test(&tests, "No Replacement", NoReplacement);
	load_test(&tests, "Null Argument", NullArg);
	return (run_test(&tests));
}
