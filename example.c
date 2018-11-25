#include "libft/includes/ft_regex.h"
#include "libft/includes/ft_list.h"
#include "libft/includes/ft_printf.h"

/*
** As a first example we will parse a JSON file
*/

int main(int argc, char **argv)
{
/*
** For readability purpose i have put the rules in the 'json.rgx' file.
** So we will load them with the RGX_LOAD flag first.
** If the call failed for any reason, we exit.
*/
	if (ft_regex(RGX_IMPORT, "json.rgx", NULL) == -1)
		return (0);
/*
** Now we have the @JSON_FORMAT rule loaded. We can test it on the argument we received.
** We will use the RGX_GLOBAL flag to allow multiple JSON structure.
** By the way it is important to mention that argv[1] should be the content of the string to test.
** So if you are willing to test the content of a file you should write:
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
