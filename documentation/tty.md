# TTY (teletype) #

`#include <unistd.h>`

## isatty ##

```C
int isatty(int desc);
```

Renvoie 1 si desc est un descripteur de fichier ouvert connecté à un terminal, ou 0 autrement.  

## ttyname ##

```C
char *ttyname(int fd);
```

La fonction `ttyname()` renvoie un pointeur sur le chemin d'accès. En cas d'erreur, elle renvoie NULL et remplit errno avec le code d'erreur.

ERRORS:

* EBADF : Mauvais descripteur de fichier.
* ENOTTY : Le descripteur de fichier ne se rapporte pas à un terminal.
* ERANGE : buflen est trop court pour stocker le chemin d'accès.

## ttyslot ##

```C
int ttyslot(void);
```

La fonction ttyslot() renvoie la position de l'entrée du terminal en cours dans un fichier.

http://manpagesfr.free.fr/man/man3/ttyslot.3.html 
