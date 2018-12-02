
# The .lq extension

`.lq` stands for '.LexiQ' and is the 'official' extension of the lexiq engine.

It is not needed for a file to have this extension for it to be imported by the lexiq engine, but it is just a norm and it is cool.

The `lq.vim` file tells vim how to highlight files that ends with with this extension.

## Installation

The `lq.vim` file must be in the 'syntax' folder of your '.vim' folder, if the folder doesn't exist it must be created.

Also, a file with the same name (lq.vim) must be in the 'ftdetect' folder in the '.vim' folder, again if it doesn't exist, it must be created. This file must contain:
```vim
autocmd BufRead,BufNewFile *.lq set filetype=lq
```
