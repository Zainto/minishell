/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_replace_variable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 21:32:53 by cempassi          #+#    #+#             */
/*   Updated: 2019/03/01 00:51:59 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"


static int		NullArg(void)
{
	t_prgm		glob;

	glob.line = NULL;
	if (replace_variable(&glob) == NULL_ARG_PASSED)
		return (ISTRUE);
	return (ISFALSE);
}

static int		NoReplacement(void)
{
	t_prgm		glob;

	glob.line = ft_strdup("Salut");
	replace_variable(&glob);
	if (ft_strequ(glob.line, "Salut"))
		return (ISTRUE);
	return (ISFALSE);
}

static int		OneReplacement(void)
{
	t_prgm		glob;

	glob_test_init(&glob);
	glob.line = ft_strdup("$toti");
	replace_variable(&glob);
	if (ft_strequ(glob.line, "tatf"))
		return (ISTRUE);
	return (ISFALSE);
}

static int		TwoReplacementWithCharacters(void)
{
	t_prgm		glob;

	glob_test_init(&glob);
	glob.line = ft_strdup("$toti coucou $totp");
	replace_variable(&glob);
	if (ft_strequ(glob.line, "tatf coucou tata"))
		return (ISTRUE);
	ft_printf("expected : |%s| | output :|%s| |", "tatf coucou tata", glob.line);
	return (ISFALSE);
}

static int		NonExistentReplacement(void)
{
	t_prgm		glob;

	glob_test_init(&glob);
	glob.line = ft_strdup("$toti $lol");
	replace_variable(&glob);
	if (ft_strequ(glob.line, "tatf "))
		return (ISTRUE);
	ft_printf("expected : |%s| | output :|%s| |", "tatf ", glob.line);
	return (ISFALSE);
}

int		test_replace_variable(void)
{
	t_stack	tests;

	ft_stckinit(&tests);
	ft_printf("%@s: \n", "39", "REPLACE VARIABLE");
	load_test(&tests, "Non-Existent remplacement", NonExistentReplacement);
	load_test(&tests, "Two remplacement with char", TwoReplacementWithCharacters);
	load_test(&tests, "One remplacement", OneReplacement);
	load_test(&tests, "No remplacement", NoReplacement);
	load_test(&tests, "Null Argument", NullArg);
	return (run_test(&tests));
}
