# Library for C Project at 42 #

These functions are clones of functions that already exist in C. We must mimic their behavior as perfectly as possible.

## How to use ##

You can compile all the library at once using

```sh
make
```

or

```sh
make debug-cc
```

To compile with a lot more compilation flag to avoid confusion.

## Groups ##

The functions are in different groups.

* `src/`
* `mem/`
* `char/`
* `str/`
* `print/`
* `sort/`
* `swap/`
* `lst/`

### P_SRC = src/ ###

Standard functions in the default directory.

### P_MEM = mem/ ###

Memory related functions

### P_CHAR = char/ ###

Character related functions

### P_STR = str/ ###

String related functions

### P_PRINT = print/ ###

Print related functions

### P_PRINT = ft_printf/ ###

Own implementation of printf and dprintf without the memory allocation.
see [ft_printf repo](https://github.com/iDarkAxe/ft_printf/) for more infos.

### P_SORT = sort/ ###

Sorting related functions

### P_SWAP = swap/ ###

Swap related functions

### P_LST = lst/ ###

Linked list related functions

## NOTES ##

### Macros ###

`FX_VA` is set by default as 0. It means that all functions that uses va_list are disabled BUT compiled in the library. If you set the value to `1`, the header will make the functions usable.

ft_printf and ft_dprintf can be use nevertheless of the value.
