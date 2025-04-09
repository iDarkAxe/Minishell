# Readline #

## Includes ##

```C
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
```

<https://tiswww.case.edu/php/chet/readline/readline.html>

## readline ##

```C
char *readline (const char *prompt);
```

Readline will read a line from the terminal and return it, using prompt as a prompt.  If prompt is NULL or the empty string, no prompt is issued.

* If input is `Enter`,
readline returns a string with a NULL at index 0 (`str[0] = '\0'`).
* If input is `Ctrl+D`, readline returns `NULL`
* If `EOF` is encountered while reading a line, and the line is empty, `NULL` is returned.
* If an `EOF` is read with a non-empty line, it is treated as a newline.

## rl_clear_history ##

```C
void rl_clear_history (void)
```

Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.

## rl_on_new_line ##

```C
int rl_on_new_line (void)
```

Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

Works without it ???

## rl_replace_line ##

```C
void rl_replace_line (const char *text, int clear_undo)
```

Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.

## rl_redisplay ##

```C
void rl_redisplay (void)
```

Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

## add_history ##

```C
void add_history (const char *string)
```

Add the string to the history of readline, so when you click 'UpArrow', readline prints the old command in place
