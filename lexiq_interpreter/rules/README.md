
# Grammar collection

A collection of files that defines the grammar of some context-free languages.

| Name | Description | Main rule |
| --- | --- | --- |
| `json.lq` | Defines the json grammar. | `@JSON_OBJECT` |
| `html.lq` | Defines the html grammar (The \<style> tag is yet to be implemented with the `css.lq` grammar). | `@HTML` |
| `css.lq` | Not yet. | `@CSS` |
| `javascript.lq` | No way. (but possible) |
| `printf.lq` | Defines the printf grammar. | `@PRINTF` |
| `struct.lq` | Defines the grammar of C structures and C comments only. | `@STRUCTURE` or `@COMMENT` |
| `expression.lq` | Defines the arithmetic grammar of the basic mathematic operations (`+`, `-`, `*`, `/`, `%` and `()`). | `@EXPRESSION` |
| `rules.lq` | Import all the mentionned files above. | NA |
