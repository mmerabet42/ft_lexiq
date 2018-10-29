#include "ft_regex.h"
#include "ft_printf.h"
#include "ft_list.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
  t_list  *matches = NULL;
  int     ret;
  
  // A bracket is either '(...)', '[...]' or '{...}' each one of them is tested by a respective rule.
  // And this rule test the 3 of them.
  ft_regex(RGX_ADD | RGX_ID, "BRACKET", "?[?[@BRACKET1]|?[@BRACKET2]|?[@BRACKET3]@or]", NULL, -2);
  
  // This rule test for opening round bracket and closing round bracket with possibly other nested brackets insde.
  ft_regex(RGX_ADD, "BRACKET1", "(*[?[@BRACKET]|?![{(){}[]}]@or?])", NULL);
  
  // This rule test for opening square bracket and closing square bracket with possibly other nested brackets insde.
  ft_regex(RGX_ADD, "BRACKET2", "[*[?[@BRACKET]|?![{(){}[]}]@or?]]", NULL);
  
  // This rule test for opening curly bracket and closing curly bracket with possibly other nested brackets insde.
  ft_regex(RGX_ADD, "BRACKET3", "{*[?[@BRACKET]|?![{(){}[]}]@or?]}", NULL);
  
  // This call will match every bracket of the first argument. To have the content of a file : ./exe "`cat file`"
  ret = ft_regex(RGX_GLOBAL, "?[@BRACKET]", argv[1], &matches);
  
  // We use the ft_print_matches function to print elegantly all the matches.
  ft_print_matches(argv[2], matches);
  ft_printf("%d matches\n");
  
  // We clean everything.
  ft_regex(RGX_FREE, NULL, NULL, &matches);
  ft_regex(RGX_CLEAN, NULL, NULL);
  
  return (0);
}
