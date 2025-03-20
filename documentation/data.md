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

# GETENV #

```sh
#include <stdlib.h>

char *getenv(const char *name);
```

La fonction getenv recherche dans la liste d'environnement pour trouve les variables d'environnements, et return un pointeur a lavaleur correspondante ou NULL si rien trouve.

# GETCWD #

```sh
#include <unistd.h>

char *getcwd(char *buf, size_t size);
```

Retourne une string NULL terminee contenant le chemin absolument du repertoire courant. Le pathname est return avec le resultat de la fonction et a travers l'argument buf qui est de longueur size.
Si la longueur du chemin absolue du repertoire courant, incluant le caractere de fin exceed size bytes, NULL est return. et errno est set en ERANGE

# OPEN #

```sh
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *path, int oflag, ...);
```

Etablit une connexion entre le file et le file descripteur. L'argument path est le chemin du fichier a ouvrir. 
