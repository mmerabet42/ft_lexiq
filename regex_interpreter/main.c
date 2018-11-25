#include "libft/includes/ft_regex.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/ft_list.h"

int main(int argc, char **argv)
{
	/*
	** If there is not at least 2 arguments, we print the usage and exit.
	*/
	if (argc < 3 || (argv[1][0] == '-' && argv[1][1] != 's'))
	{
		ft_printf("Usage: ./regex [-s] subject file ...\n");
		return (1);
	}

	/*
	** If the option '-s' is specified, we change the print mode.
	*/
	int print_mode = 0;
	if (argv[1][0] == '-')
		print_mode = 1;

	/* 
	** Import all the files.
	*/
	int i = (print_mode ? 2 : 1);
//	if (argv[i][0] == '-' && argv[i][1] == 'm')
	while (++i < argc)
	{
		/*
		** If the importation of a file failed, we clean all the already imported files and exit.
		*/
		if (ft_regex(RGX_IMPORT, argv[i], NULL) == -1)
		{
			ft_regex(RGX_CLEAN, NULL, NULL);
			ft_printf("Error: failed to open '%s'\n", argv[i]);
			return (1);
		}
	}
	
	/*
	** Check if the 'MAIN' rule exists, if not, exit.
	*/
	void *main_ptr = NULL;
	ft_regex(RGX_GETRULE, "MAIN", NULL, &main_ptr);
	if (!main_ptr)
	{
		ft_printf("Error: no 'MAIN' rule found\n");
		return (1);
	}
	char *subject = (print_mode ? argv[2] : argv[1]);
	/*
	** Execute the 'MAIN' rule.
	*/
	int n = ft_regex(RGX_GLOBAL, "?[@MAIN]", subject, &matches);
	
	if (print_mode)
		ft_print_matches_tree(matches, 0);
	else
		ft_print_matches(subject, matches);
	ft_printf("\n%d match(es)\n", n);
	return (0);
}
