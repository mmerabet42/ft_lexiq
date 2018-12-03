#include "libft/includes/ft_lexiq.h"
#include "libft/includes/ft_str.h"
#include "libft/includes/ft_mem.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/ft_printf_ext.h"
#include "libft/includes/get_next_line.h"
#include "libft/includes/ft_list.h"

/*
** The usage is printed if the required argument are not provided.
*/
#define USAGE_STR "Usage: ./lexiq [-tv] [-s subject] [-e expression] [-i file] ...\n"

static int	getoptions(char ***argv, char **subject, char **expr);

int main(int argc, char **argv)
{
	int		options;
	char	*subject;
	char	*expr;

	(void)argc;
	expr = "?[@MAIN]";
	subject = NULL;
	/* Parse the options. */
	if ((options = getoptions(&argv, &subject, &expr)) == -1)
		return (1);
	if (!subject)
	{
		ft_printf_fd(2, USAGE_STR);
		return (1);
	}
	/* If the '-e' option never occured, */
	if (!(options & 1))
	{
		/* We need to check if the 'MAIN' rule is declared, if it is not, we exit. */
		void *main_ptr = NULL;
		ft_lexiq(LQ_GETRULE, "MAIN", NULL, &main_ptr);
		if (!main_ptr)
		{
			ft_printf("lexiq: 'MAIN' rule not declared\n");
			return (1);
		}
		/* Set the 'MAIN' rule 'transparent' by setting its id to -2. */
		((t_lq_func *)main_ptr)->id = -2;
	}

	if (options & 3)
		ft_printf("Executing '%s'\n\n", expr);

	if (expr && subject)
	{
		/*
		** Execute the expression on the subject string.
		*/
		t_list *matches = NULL;
		int n = ft_lexiq(LQ_GLOBAL, expr, subject, &matches);

		/* Print the matches in a tree, if the '-t' option is specified, */
		if (options & 2)
			ft_print_matches_tree(matches, 0);
		/* Otherwise print it normally. */
		else
			ft_print_matches(subject, matches);
		ft_printf("\n%d match(es)\n", n);

		ft_lexiq(LQ_FREE, NULL, NULL, &matches);
	}

	/*
	** Clean everything.
	*/
	ft_lexiq(LQ_CLEAN, NULL, NULL);
	get_next_line(-1, NULL);
	get_next_delimstr(-1, NULL, NULL);
	ft_printf_free_formats();
	return (0);
}

/* Function that parses the options */
static int	getoptions(char ***argv, char **subject, char **expr)
{
	t_opt	opt;
	int		options;

	/* We jump the program name, as the ft_getopt function assumes that it is not a part of the array. */
	++(*argv);
	options = 0;
	while (ft_getopt(argv, "s.1e.1i.1tv;subject.1;expression.1;import.1;tree", &opt) != OPT_END)
	{
		/* If the option is unknown or if its arguments are missing, we exit. */
		if (opt.ret == OPT_UNKNOWN || opt.ret == OPT_MISSING)
		{
			ft_printf_fd(2, USAGE_STR);
			ft_lexiq(LQ_CLEAN, NULL, NULL);
			return (-1);
		}
		/* If the '-s' option is met, get its argument (opt.ptr[0]) */
		if (opt.c == 's' || (opt.c == '-' && *opt.clong == 's'))
			*subject = opt.ptr[0];
		/* If the '-e' option is met, get its argument */
		else if (opt.c == 'e' || (opt.c == '-' && *opt.clong == 'e'))
		{
			*expr = opt.ptr[0];
			options |= 1;
		}
		/* If the '-i' option is met, import the file specified in argument, */
		else if (opt.c == 'i' || (opt.c == '-' && *opt.clong == 'i'))
		{
			/* If the importation failed, we exit. */
			if (ft_lexiq(LQ_IMPORT, opt.ptr[0], NULL) == -1)
			{
				ft_printf_fd(2, "lexiq: Error when importing '%s'\n", opt.ptr[0]);
				ft_lexiq(LQ_CLEAN, NULL, NULL);
				return (-1);
			}
		}
		/* If the '-t' option is met, enable the second bit of `options` */
		else if (opt.c == 't' || (opt.c == '-' && *opt.clong == 't'))
			options |= 2;
		else if (opt.c == 'v')
			options |= 4;
	}
	return (options);
}
