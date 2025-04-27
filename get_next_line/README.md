# Line reader from a file descriptor, line by line #

A library to read a file descriptor, line by line, and storing the rest of "too much read" in memory.

## 📋 Table of Contents ##

* [How does it work](#howitwork-en)
* [🚀 How to use `get_next_line()`](#usage-en)

## <a name="howitwork-en">How does it work ##

Each time the `get_next_line()` function is used, it reads a fixed amount of characters of the file descriptor until the end of line or end of file is detected.
It returns the line rode (needs to be freed after use).
The amount of characters rode is fixed by a MACRO defined in the header file, lengths smaller than 30 and higher than 100 could make the function working poorly in certain conditions.

## <a name="usage-en">🚀 How to use `get_next_line()` ##

Just start it using :

```C
char *ptr;

ptr = get_next_line(<FD>);
if (ptr != NULL)
  printf("%s", ptr);
```

`FD` is a file descriptor, it can be set with a `open()` or directly from the standard input (stdin is fd:0).

For the bonus version, you can read multiple `FDs` without loosing track of the position in the file.
If you are using multiple call of get_next_line() with the standard version, all the characters will be shuffled from multiple backup of all files.

---

## Lecteur de descripteur de fichier, ligne par ligne ##

Bibliothèque pour lire un decripteur de fichier, ligne par ligne, en stockant le "trop lu" en mémoire.

## 📋 Table des matières ##

* [📖 Comment ça marche ?](#howitwork-fr)
* [🚀 Comment utiliser la fonction `get_next_line()`](#usage-fr)

## <a name="howitwork-fr">📖 Comment ça marche ? ##

Chaque fois que la fonction `get_next_line()` est appelée, elle lis un montant fixe de caractères jusqu'à un charcatère de fin de ligne ou fin de fichier.
Retourne la ligne lue (le pointeur a besoin d'être libéré après utilisation).
Le nombre de caractères lus est fixés par une MACRO définie dans le fichier header, les tailles plus petites que 30 et plus grandes que 100 pourrait rendre la fonction moins performantes dans certaines conditions.

## <a name="usage-fr">🚀 Comment utiliser la fonction `get_next_line()` ##

Voici un code simple :

```C
char *ptr;

ptr = get_next_line(<FD>);
if (ptr != NULL)
  printf("%s", ptr);
```

`FD` est un descripteur de fichier, il peut être défini par une fonction comme `open()` ou être directement sur l'entrée standard (stdin est le fd:0).

Pour la version bonus, la fonction est capable de lire divers `FDs` sans perdre la trace de la postion dans le fichier.
Si vous utiliser de multiples appels de la fonction get_next_line() en version standard, les caractères restants seront mélangés avec les caractères restands des autres descripteurs de fichier sans distinctions.
