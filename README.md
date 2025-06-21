# Minishell #

## <a name="introduction-en">📖 Introduction ##

Make your own shell that performs worse than bash but it's yours.

### Requirements ###

* Display a prompt when waiting for a new command.
* Have a working history.
* Search and launch the right executable (based on the PATH variable or using a relative or an absolute path)
* Not interpret unclosed quotes or special characters which are not required by the subject such as `\` (backslash) or `;` (semicolon).
* Handle `’` (single quote) and `"` (double quote).
* Implement redirections:
  * `<` should redirect input.
  * `>` should redirect output.
  * `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
  * `>>` should redirect output in append mode.
* Implement pipes (`|` character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
* Handle environment variables (`$` followed by a sequence of characters) which should expand to their values.
* Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.
* Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash.
* In interactive mode:
  * `ctrl-C` displays a new prompt on a new line.
  * `ctrl-D` exits the shell.
  * `ctrl-\` does nothing.
* Your shell must implement the following builtins:
  * `echo` with option -n
  * `cd` with only a relative or absolute path
  * `pwd`
  * `export`
  * `unset`
  * `env` with no options or arguments
  * `exit`
* The readline() function can cause memory leaks. You don’t have to fix them. But that doesn’t mean your own code, yes the code you wrote, can have memory leaks

**In an easier language :**

* Read the stdin inputs and parse the given string
* Handle at least `SIGINT` and `SIGQUIT` signals properly (no leaks)
* There will be no unclosed `'` or `"` quotes, only even number of quotes
* Handle file redirection (`<`, `>`, `<<` and `>>`) and pipes
* Handle environment variables
* It should works at least with the following functions without options or arguments :
  * pwd
  * export
  * unset
  * env
  * exit
* And with options :
  * echo with option -n
  * cd with only a relative or absolute path
  * env with arguments
* readline() leaks, use a suppression file to hide them

## 📋 Table of Contents ##

* [📖 Introduction](#introduction-en)
* [🚀 Usage](#usage-en)
* [⚙️ Compilation](#compilation-en)
* [📝 Additionnal Notes](#notes-en)

## <a name="usage-en">🚀 Usage ##

```sh
./minishell
```

OPTIONNAL :

```sh
./minishell << EOF
> cat file
> echo "$PATH"
> echo '$PATH'
> pwd
> exit
> EOF
```

You can directly write a HERE-DOC to use minishell purely in cli-mode, otherwise it's interactive.

## <a name="compilation-en">⚙️ Compilation ##

Use ``make`` for compiling the executable

```sh
make
```

## <a name="notes-en">📝 Additionnal Notes ##

It's a group project. The project has been managed through Miro. Each tasks has been written in advance and everyone could chose what task they wanted to do.

---

# Minishell #

## <a name="introduction-fr">📖 Introduction ##

Fais ton propre shell qui marche moins bien que bash, mais c'est le tien .

### Prérequis ###

* Affiche un prompt qui attends une nouvelle commande.
* Avoir un historique fonctionnel.
* Rechercher et lancer avec le bon exécutable (basé sur la variable PATH ou utiliser un chemin relatif ou absolu)
* Ne pas interprêter les apostrophes et les guillemets non fermés ou les caractères spéciaux qui ne sont pas requis dans le sujet comme `\` (backslash) or `;` (point virgule).
* Interprêter les `'` (apostrophes) et les `"` (guillemets).
* Implémenter les redirections :
  * `<` devrait rediriger l'entrée.
  * `>` devrait rediriger la sortie.
  * `<<` avec un délimiteur, et ainsi lire les lignes tant qu'on ne trouve pas un délimiteur. Mais, pas besoin de mettre à jour l'historique
  * `>>` devrait rediriger la sortie en mode 'ajouter à la fin'.
* Implémter les pipes (caractère `|`). La sortie de chaque commande dans le pipeline est reliée à l'entrée de la commande suivante via un pipe.
* Traiter les variables d'environnement (`$` suivi par une séquence de caractère) qui devrait être remplacé par leurs valeurs.
* Traiter `$?` devrait être remplacé par le statut de la commande la plus récente en premier plan.
* Traiter les raccourcis `ctrl-C`, `ctrl-D` et `ctrl-\` qui devraient fonctionne comme bash.
* En mode interactif :
  * `ctrl-C` affiche à nouveau le prompt sur une nouvelle ligne.
  * `ctrl-D` ferme le shell.
  * `ctrl-\` me fait rien.
* Votre shell doit implémenter les fonctions fournies suivantes :
  * `echo` avec option -n
  * `cd` avec un chemin relatif ou absolu
  * `pwd`
  * `export`
  * `unset`
  * `env` sans option ou avec arguments
  * `exit`

* La fonction readline() peut causer des fuites de mémoires. Vous n'avez pas à essayer de les réparer. Mais ça ne veut pas dire que votre code doit avoir des fuites de mémoires.

**Ou de façon plus simple :**

* Lire l'entrée standard et découper et trier la chaîne d'entrée
* Traiter au moins les signaux `SIGINT` et `SIGQUIT` proprement (sans fuite de mémoire)
* Il n'y aura pas de `'` ou `"` non fermés, uniquement un nombre pair de signes
* Traiter la redirection de fichier (`<`, `>`, `<<` and `>>`) et les pipes
* Traiter les variables d'environnement
* Ça devrait fonctionner pour au moins toutes les fonctions fournies sans argument ou options :
  * pwd
  * export
  * unset
  * env
  * exit
* Et avec options :
  * echo avec option -n
  * cd avec un chemin relatif ou absolu
  * env avec des arguments
* readline() fuit, utilisez un fichier de suppression pour les cacher

## 📋 Table des matières ##

* [📖 Introduction](#introduction-fr)
* [🚀 Usage](#usage-fr)
* [⚙️ Compilation](#compilation-fr)
* [📝 Notes supplémentaires](#notes-fr)

## <a name="usage-fr">🚀 Utilisation ##

```sh
./minishell
```

OPTIONNEL :

```sh
./minishell << EOF
> cat file
> echo "$PATH"
> echo '$PATH'
> pwd
> exit
> EOF
```

Vous pouvez écrire directement dans un HERE-DOC pour utiliser minishell en mode CLI, sinon c'est interactif.

## <a name="compilation-fr">⚙️ Compilation ##

Utiliser ``make`` pour compiler l'exécutable

```sh
make
```

## <a name="notes-fr">📝 Notes Supplémentaires ##

C'est un project de groupe. Le projet a été géré sur Miro. Chaque tâche a été définie à l'avance et chacun pouvait choisir celle qu'il voulait faire.
