
# The .rls extension

`.rls` stands for '.RuLeS' and is the 'official' extension of the `ft_regex` engine.

It is not needed for a file to have this extension for it to be imported by the `ft_regex` engine, but it is a norm and is needed by vim for highlighting the related files.

The `rls.vim` file tells vim how to highlight files that ends with `.rls`

## Installation

The `rls.vim` file must be in the 'syntax' folder of your '.vim' folder, if the 'syntax' folder doesn't exist it must be created.

Also, a file with the same name (rls.vim) must be in the 'ftdetect' folder in the '.vim' folder, again if it doesn't exist, it must be created. This file must contain:
```vim
autocmd BufRead,BufNewFile *.rls set filetype=rls
```
