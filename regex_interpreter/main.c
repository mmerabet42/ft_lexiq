#include "libft/includes/ft_regex.h"
#include "libft/includes/ft_str.h"
#include "libft/includes/ft_mem.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/ft_printf_ext.h"
#include "libft/includes/get_next_line.h"
#include "libft/includes/ft_list.h"

/*
** The usage is printed if the required argument are not provided.
*/
#define USAGE_STR "Usage: ./regex [-sm] subject [regex] file ...\n"

static int	getoptions(int argc, char ***argv);

int main(int argc, char **argv)
{
	int		options;
	char	*subject;
	char	*regex;

	/* Parse the options. */
	if ((options = getoptions(argc, &argv)) == -1)
		return (1);
	/* The subject string comes first, or after the options, if any.  */
	subject = *(argv++);
	/* If no arguments after the subject string, then the usage isn't respected, we exit. */
	if (!*argv)
	{
		ft_printf(USAGE_STR);
		return (1);
	}

	/* If the options '-m' is given (options & 2), then the regex is the next argument. */
	if (options & 2)
		regex = *(argv++);
	/* Otherwise use the 'MAIN' rule declared in one of the files. */
	else
		regex = "?[@MAIN]";
	/* If files are provided, import them. */
	while (*argv)
	{
		/* If the importation of a file failed, we clean all the already imported files and exit. */
		if (ft_regex(RGX_IMPORT, *argv, NULL) == -1)
		{
			ft_regex(RGX_CLEAN, NULL, NULL);
			ft_printf("regex: Failed to open '%s'\n", *argv);
			return (1);
		}
		++argv;
	}
	/* If the '-m' option is absent, */
	if (!(options & 2))
	{
		/* We check if the 'MAIN' rule is declared, if it is not, we exit. */
		void *main_ptr = NULL;
		ft_regex(RGX_GETRULE, "MAIN", NULL, &main_ptr);
		if (!main_ptr)
		{
			ft_printf("regex: 'MAIN' rule not found\n");
			return (1);
		}
		/* Set the 'MAIN' rule 'transparent' by setting its id to -2. */
		((t_regex_func *)main_ptr)->id = -2;
	}

	/*
	** Execute the regex on the subject string.
	*/
	t_list *matches = NULL;
	int n = ft_regex((!(options & 4) ? RGX_GLOBAL : RGX_GROUP), regex, subject, &matches);

	/* Print the matches in a tree form, if the '-s' option is given, */
	if (options & 1)
		ft_print_matches_tree(matches, 0);
	/* Otherwise print it normally. */
	else
		ft_print_matches(subject, matches);
	ft_printf("\n%d match(es)\n", n);

	/*
	** Free the allocated matches, and rules.
	*/
	ft_regex(RGX_FREE, NULL, NULL, &matches);
	ft_regex(RGX_CLEAN, NULL, NULL);
	get_next_line(-1, NULL);
	get_next_delimstr(-1, NULL, NULL);
	ft_printf_free_formats();
	return (0);
}

/* Function that gathers the options */
static int	getoptions(int argc, char ***argv)
{
	t_opt	opt;
	int		options;

	/* If there is not at least 2 argument, we exit. */
	if (argc < 3)
	{
		ft_printf(USAGE_STR);
		return (-1);
	}
	/* We jump the program name, as the ft_getopt function assumes that it is not a part of the array. */
	++(*argv);
	options = 0;
	while (ft_getopt(argv, "smg", &opt) != OPT_END)
	{
		/* If an unknown option is given, we exit. */
		if (opt.ret == OPT_UNKNOWN)
		{
			ft_printf(USAGE_STR);
			return (-1);
		}
		/* If the option 's' is met, then enable the first bit of `options` */
		if (opt.c == 's')
			options |= 1;
		/* If the option 'm' is met, then enable the second bit of `options` */
		else if (opt.c == 'm')
			options |= 2;
		/* If the option 'm' is met, then enable the third bit of `options` */
		else if (opt.c == 'g')
			options |= 4;
	}
	/* If no arguments after the options, then the usage isn't respected, we exit. */
	if (!**argv)
	{
		ft_printf(USAGE_STR);
		return (-1);
	}
	return (options);
}
