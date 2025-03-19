# Minishell #

`#include <signal.h>`

## signal ##

Version moins pratique que sigaction. On utilise donc sigaction

## sigaction ##



## sigemptyset ##

```C
int sigemptyset(sigset_t *set);
```

Prends en paramètre un masque de la structure `sigaction`. Initialise le masque et le met à 0.

```C
action_receive.sa_flags = SA_RESTART | SA_SIGINFO;
```

`SA_SIGINFO` permet de récupérer les infos du process qui a envoyé le signal.

`SA_SIGINFO` permet de redémarrer les appels système lents interrompus par l'arrivée du signal.

## sigaddset ##

sigaddset peut être utile pour bloquer temporairement SIGUSR1 et SIGUSR2 pendant le traitement des signaux pour éviter des interférences. Cela se fait souvent avec sigprocmask :

```C
sigset_t set;
sigemptyset(&set);
sigaddset(&set, SIGUSR1);
sigaddset(&set, SIGUSR2);
sigprocmask(SIG_BLOCK, &set, NULL); // Bloque SIGUSR1 et SIGUSR2
```

Après traitement, on peut les débloquer avec :

```C
sigprocmask(SIG_UNBLOCK, &set, NULL);
```

En résumé, sigaddset est un outil permettant de construire un ensemble de signaux afin de les manipuler plus facilement avec d'autres fonctions comme sigprocmask, sigpending ou sigsuspend.

## kill ##

```C
int kill(pid_t pid, int sig);
```

Permet d'envoyer un signal à un process.

`<pid_t>` est le numéro du process vers lequel envoyer le signal.

`<sig>` est le signal à envoyer.
