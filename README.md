# What is a regular expression ?
A regular expression (or regex) is a way to define a search pattern, wich is usually used for 'find' operations. 
There are many regex engines out there in almost all programming languages, and they all follow the same syntax, there could be some differences but in general they do not vary that much.
### ft_regex
The regex engine i am going to present you works differently, and has a different syntax. But still follows the same 'idea', meaning that each character in a regular expression is still either a metacharacter, which are in number of two, or a literal character. This will be explained later, we will first talk about how it differs from most regex engines and why it could be powerfull.

First of all, it is important to know that it has started as a school project, so it may not be perfect, and has definetely a tons of flaws.

Secondly, this regex engine does not compile or precompile, it reads the regex string character by character without using dynamic allocation. It uses the concept of 'rules' which is where the main difference and power stands, we will get to it later.

So, before diving into the code, and learn how to use the `ft_regex` function, we will first look at the syntax.

# How a regular expression works ?

As told earlier, a regular expression is just a bunch of charcaters that are either a metacharacter or a literal character.
A metacharacter do not define itself, and controls how the matching is done. Where a literal character define itself.
For example the regex `abc.` *abc* are literal characters, which matches just *abc*, while *.* is a metacharacter, which matches any single character. So this regex might match different strings that starts with *abc* and ends with any single character. This regex engine would rather define the regex as `abc?`.

Well i wont give a hole tutorial on how regular expression works as it is defenitely not the goal of this. But you could check [this website](https://www.regular-expressions.info/tutorial.html) to learn more.

## Two metacharacter are enough

I talked about this regex having only two metacharacter and it should be enough to match any possible string, this is the first reason of it being limited to two, the second one is to keep it simple and generic.

They are:
- `*`, the wildcard might match multiple times, and is kind of a 'while' loop.
- `?`, the question mark will match only once, and is more of an 'if'.

Something else to know that i forgot to mention, is that there is no such as backslashing character, so to match the *?*, `\?` will not work. The backslash character is a literal character. I refused to choose the backslash character because things could get ugly really quickly as the C language already use the backslash inside quotes, you would need to backslash the backslash etc.

But how would you match these metacharacters you ask me ? Well i will go straight to the answer : `?[?]`.

Here we used the braces '[]' to have more control on what should match, we specify inside the braces the only characters that shall match, in this case the question mark. If you remembered the question mark means match only once, so the wildcard (`*[?]`) awaits any number of question marks and will eventually match strings that only contains question marks.

So as i said earlier this regex follow the same 'idea', and in this context the braces works the same, so to specify a range for example, `*[A-Z0-9?*]` will match any character between A-Z, so uppercase letters, or between 0-9, so digits, or the characters question mark or wildcard, and we used the wildcard which means that it wont stop after the first match and will continue if possible.

## Negating and quantifying

You can negate a match by following a metacharacter with an exlamation mark `?![...]` or `*![...]`, so `?![A-Za-z]` will match any single character that is not a letter (neither an uppercase letter nor a lowercase letter).

We use quantifiers to control how many times a match shall occur, it is possible with the `@` sign inside of braces and with the `*` metacharacter `*[A-Z@=4]` matches exactly four times characters between uppercase A and uppercase Z. And `*![A-Z@=4]` matches exactly four times characters that are not uppercase letters. 

Now what if you want an '@' sign inside of a character set as there is no such as backslash ? To do this, you would need to understand that the braces always takes the last occurence of the '@' sign to delimit the character set and the quantifier. 
`?[@@@]` the character set here is made of two '@' sign, the last one is the delimitation of the quantifier

So with quantifying we could mimic the question mark behaviour with the wildcard `*[...@=1]`.
Never forget that quantifying only works with the wildcard metacharacter and wont have any effect with the question mark metacharacter, it wont make any sense otherwise.

There are two other operators that are used for quantifying matches, they are:
- `[...@<n]`, the match shall occur less than n times.
- `[...@>n]`, the match shall occur more than n times.

It is possible to give an empty character set to both of the metacharacters, for the wildcard it means match any single character between one and unlimited times, while the wildcard alone means match between zero and unlimited times For the question mark it doesn't change it's behaviour and will always match any single character once and only once.

## Backslash limitation

There is a question that has not been raised yet which concerns how the braces works and how to have any possible character in a character set, because as we know we can't backslash a closing bracket and with the concept of 'rules' things could get really messy, so we had to counter the problem by letting the user control what starts a character set and what closes it.
> An opening brace followed by n opening curly bracket shall be closed by n closing bracket followed by a closing brace.

We would get something of this shape `?[{{...}}]`, and here we reached the limitation of not using backslashes, because with this solution how would you have a character set that starts with an opening curly bracket ? You may think that this question does not make any sense as the order of a character set shall not change it's behaviour, well it is true for this context but not for the context of rules, that are going to be seen in the next part (finally). To counter this other problem, backslashing is coming back but stays only for the very first character, and it just cancel the meaning of the '\\' and the '{' characters. So the solution of the problem is `?[{\{...}]` or `?[{{{{\\....}}}}]` or `?[{...]...}]`. The '@' sign should always appair before whatever closing has been used: `?[{{...@=3}}]`.

At this point we solve the backslashing problem.
