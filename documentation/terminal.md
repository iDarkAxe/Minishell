# Terminal management #

## Basics ##

```C
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
```

Toutes les fonctions pour modifier le comportement du terminal.

Exemple d'utilisation des fonctions `tcgetattr()` et `tcsetattr()`.

```C
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main() {
    struct termios oldt, newt;

    // Récupérer les paramètres actuels
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Désactiver l’écho
    newt.c_lflag &= ~ECHO;

    // Appliquer les nouveaux paramètres immédiatement
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Lire quelque chose (l’utilisateur tape sans que ça s'affiche)
    printf("Tape ton mot de passe : ");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    printf("\nTu as tapé : %s", buffer);

    // Restaurer les anciens paramètres
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
```

## tcsetattr ##

Modifier les paramètres du terminal.

```C
int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p);

struct termios newt;
tcsetattr(STDIN_FILENO, TCSANOW, &newt);
```

* If optional_actions is `TCSANOW`, the change shall occur immediately.
* If optional_actions is `TCSADRAIN`, the change shall occur after all output written to fildes is transmitted. This function should be used when changing parameters that affect output.
* If optional_actions is `TCSAFLUSH`, the change shall occur after all output written to fildes is transmitted, and all input so far received but not read shall be discarded before the change is made.

## tcgetattr ##

Récupérer les paramètres actuels du terminal dans une structure.

```C
struct termios oldt;
tcgetattr(STDIN_FILENO, &oldt);
```

## tgetent ##

Charger les infos du terminal

```C
int tgetent(char *bp, const char *term);
```

## tgetflag ##

Lire une 'capacité' booléenne (1 ou 0)

```C
int tgetflag(const char *id);
```

## tgetnum ##

Lire une capacité numérique

```C
int tgetnum(const char *id);
```

## tgetstr ##

Obtenir une séquence d’échappement

```C
char *tgetstr(const char *id, char **area);
```

## tgoto ##

Formater une séquence avec coordonnées

```C
char *tgoto(const char *cm, int col, int row);
```

## tputs ##

Afficher proprement la séquence

```C
int tputs(const char *str, int affcnt, int (*putc)(int));
```
