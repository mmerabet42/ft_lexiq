#include "libft/includes/ft_regex.h"
#include "libft/includes/ft_str.h"
#include "libft/includes/ft_mem.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/ft_list.h"

static int	getoptions(int argc, char ***argv);

int main(int argc, char **argv)
{
	int		options;
	char	*subject;
	char	*regex;

	/*
	** Parse the options
	*/
	if ((options = getoptions(argc, &argv)) == -1)
		return (1);
	subject = *(argv++);
	if (!*argv)
	{
		ft_printf("Usage: ./regex [-sm] subject file ...\n");
		return (1);
	}

	if (options & 2)
		regex = *(argv++);
	else
		regex = "?[@MAIN]";
	/* 
	** Import all the files.
	*/
	while (*argv)
	{
		/*
		** If the importation of a file failed, we clean all the already imported files and exit.
		*/
		if (ft_regex(RGX_IMPORT, *argv, NULL) == -1)
		{
			ft_regex(RGX_CLEAN, NULL, NULL);
			ft_printf("regex: Failed to open '%s'\n", *argv);
			return (1);
		}
		++argv;
	}
	if (!(options & 2))
	{
		/*
		** Check if the 'MAIN' rule exists, if not, exit.
		*/
		void *main_ptr = NULL;
		ft_regex(RGX_GETRULE, "MAIN", NULL, &main_ptr);
		if (!main_ptr)
		{
			ft_printf("regex: 'MAIN' rule not found\n");
			return (1);
		}
		((t_regex_func *)main_ptr)->id = -2;
	}

	/*
	** Execute the regex.
	*/
	t_list *matches = NULL;
	int n = ft_regex(RGX_GLOBAL, regex, subject, &matches);

	if (options & 1)
		ft_print_matches_tree(matches, 0);
	else
		ft_print_matches(subject, matches);
	ft_printf("\n%d match(es)\n", n);

	/*
	** Free all allocated memories.
	*/
	ft_regex(RGX_FREE, NULL, NULL, &matches);
	ft_regex(RGX_CLEAN, NULL, NULL);
	return (0);
}

static int	getoptions(int argc, char ***argv)
{
	t_opt	opt;
	int		options;

	if (argc < 3)
	{
		ft_printf("Usage: ./regex [-sm] subject file ...\n");
		return (-1);
	}
	ft_bzero(&opt, sizeof(t_opt));
	++(*argv);
	options = 0;
	while (ft_getopt(argv, "sm", &opt) != OPT_END)
	{
		if (opt.ret == OPT_UNKNOWN)
		{
			ft_printf("Usage: ./regex [-sm] subject file ...\n");
			return (-1);
		}
		if (opt.c == 's')
			options |= 1;
		else if (opt.c == 'm')
			options |= 2;
	}
	if (!**argv)
	{
		ft_printf("Usage: ./regex [-sm] subject file ...\n");
		return (-1);
	}
	return (options);
}
