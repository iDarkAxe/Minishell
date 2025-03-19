# Minishell #

# CD #
CD utilise probablement la variable d'environnement $PWD pour les chemins relatifs
la commande chdir permet de faire l'equivalent de cd en C

# PWD #

# READLINE #

```sh
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
```
`char * readline (const char *prompt);`

Readline est une fonction qui lit de depuis le terminal et la return. Si la ligne est vide ou quelle est NULL, rien n'est ecrit. La ligne est return avec un malloc donc il faut la free.
La fonction permet des options de navigations dans l'ecriture du texte.

