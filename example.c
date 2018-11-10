#include "libft/includes/ft_regex.h"
#include "libft/includes/ft_list.h"
#include "libft/includes/ft_printf.h"

/*
** As a first example we will parse a JSON file
*/

/*
** This function will print the matched patterns properly.
*/
void print_matches(t_list *matches);

int main(int argc, char **argv)
{
/*
** For readability purpose i have put the rules in the 'rules.rgx' file.
** So we will load them with the RGX_LOAD flag.
** If the call failed for any reason, we exit.
*/
	if (ft_regex(RGX_LOAD, "rules.rgx", NULL) == -1)
		return (0);
/*
** Now we have the @JSON_FORMAT rule loaded. We can test it on the argument we received.
** We will use the RGX_GLOBAL flag to allow multiple JSON structure.
** By the way it is important to mention that argv[1] should be the content of the string to test.
** So if you are willing to test a file you should write:
**             ./a.out "`cat file`"
*/
	int		n;
	t_list	*matches;

	n = ft_regex(RGX_GLOBAL, "?[@JSON_FORMAT]", argv[1], &matches);

	ft_print_matches(argv[1], matches);
	print_matches(matches);
	ft_printf("%d matches\n", n);

	return (0);
}

void print_groups(t_list *groups, int tab)
{
	while (groups)
	{
		t_regex_group	*grp = (t_regex_group *)groups->content;
		ft_printf("%?*\tgroup: %d %d %d '%.*s'\n", tab, grp->pos, grp->len, grp->id, grp->len, grp->str);
		print_groups(grp->groups, tab + 1);
		groups = groups->next;
	}
}

void print_matches(t_list *matches)
{
	while (matches)
	{
		t_regex_match	*mch = (t_regex_match *)matches->content;
		ft_printf("match: %d %d %d '%.*s'\n", mch->pos, mch->len, mch->id, mch->len, mch->str);
		print_groups(mch->groups, 1);
		matches = matches->next;
	}
}

