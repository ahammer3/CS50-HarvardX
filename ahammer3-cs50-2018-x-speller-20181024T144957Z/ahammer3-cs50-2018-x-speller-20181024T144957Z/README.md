# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

The longest word in the dictionary. More correctly, the example used for the longest length of a word used as a constant in our header file (LENGTH 45).

## According to its man page, what does `getrusage` do?

"get resource usage" - basically returns resource usage statistics for 'who' that is passed in. In other words, it basically times the execution of the program.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 - 2 of which are other structs

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

instead of creating copies of before and after every single time we call it, better to just reference them "once".

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

'main' will read characters one by one until EOF. The words that it reads can only contain alphabetical numbers and "'". If a word is longer than LENGTH, or has a number, the word reads in the rest of the 'faulty' word and then drops it entirely and ignores it.
Else, we have found a whole word and terminate it with a '\0' character, and then the word is checked against the dictionary of valid words, and time_check, etc. are updated.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf would have difficulties discriminating individual characters such as numbers, uppercase, other characters that do not fit the criteria.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

We ensure by 'const' that the data that check and load point to are not changing and must stay the same.
