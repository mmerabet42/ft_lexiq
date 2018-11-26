# A simple regex interpreter

Let me present you a program that uses the `ft_regex` library.

It is a regex interpreter that will perform a search on a string.

`Usage: ./regex [-sm] subject [regex] file ...`

The search will be perfomed on `subject`, `regex` is considered as the entry point only if the `-m` option is specified, if it is not, the `MAIN` rule is used as the entry point which must be declared in one of the `file` specified in argument.

The file(s) must follow the [`ft_regex`](https://github.com/mmerabet42/ft_regex) syntax
```C
#import "other.rgx"

MAIN "*[@space]"
```

In this example, the file `other.rgx` is imported, then the `MAIN` rule is declared. 

### Installation

You just need to `make` the project
```bash
$> make
```

It will generate a `./regex` executable.
If you want to perform the search on a file, or multiple file you need to use the backquotes inside the double quotes
```bash
$> ./regex "`cat file`" rules.rgx
```
will execute the `MAIN` rule on `file`.
