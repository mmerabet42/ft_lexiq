# A simplistic lexiq interpreter

Let me present you a program that uses the lexiq engine.

It is a lexiq interpreter that will perform an `expression` on a `subject` string.

`Usage: ./regex [-t(--tree)] [-s(--subject) subject] [-e(--expression) expression] [-i(--import) file] ...`

The `expression` will be perfomed on `subject`, `expression` is considered as the entry point only if the `-e` option is specified, if it is not, the `MAIN` rule is used as the entry point which must be declared in one of the `file` specified in argument with the `-i` option.

The file(s) must follow the [`lexiq`](https://github.com/mmerabet42/ft_regex) syntax
```C
#import "other.lq"

MAIN "*[@space]"
```

In this example, the file `other.lq` is imported, then the `MAIN` rule is declared. 

### Installation

You just need to `make` the project
```bash
$> make
```

It will generate a `./lexiq` executable.
If you want to perform an expression on a particular file, or multiple files you need to use the backquotes inside the double quotes
```bash
$> ./regex -s "`cat file`" -i rules.lq
```
will execute the `MAIN` imported from `rules.lq` on the content of `file`.
