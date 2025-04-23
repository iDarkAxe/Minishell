# Directories #

## Types ##

```C
/**
 * @struct dirent
 * @brief Représente une entrée dans un répertoire (retournée par readdir).
 */
struct dirent {
    ino_t          d_ino;     /**< Numéro d'inode du fichier. */
    off_t          d_off;     /**< Offset vers l'entrée suivante dans le flux de lecture. */
    unsigned short d_reclen;  /**< Longueur de cette structure d'entrée. */
    unsigned char  d_type;    /**< Type de fichier (voir DT_*). */
    char           d_name[];  /**< Nom de l'entrée (chaîne de caractères terminée par '\0'). */
};
```

```C
/**
 * @name Valeurs possibles pour d_type
 * @{
 */
#define DT_UNKNOWN  0  /**< Type de fichier inconnu. */
#define DT_FIFO     1  /**< File FIFO (pipe nommé). */
#define DT_CHR      2  /**< Fichier spécial caractère. */
#define DT_DIR      4  /**< Répertoire. */
#define DT_BLK      6  /**< Fichier spécial bloc. */
#define DT_REG      8  /**< Fichier régulier. */
#define DT_LNK     10  /**< Lien symbolique. */
#define DT_SOCK    12  /**< Socket. */
#define DT_WHT     14  /**< Marqueur "whiteout" (systèmes spécifiques). */
/** @} */
```

```C
struct timespec {
    time_t tv_sec;   // secondes
    long   tv_nsec;  // nanosecondes
};

/**
 * @struct stat
 * @brief Contient les informations sur un fichier (utilisée avec stat, lstat, fstat).
 */
struct stat {
    dev_t     st_dev;     /**< ID du périphérique contenant le fichier. */
    ino_t     st_ino;     /**< Numéro d'inode. */
    mode_t    st_mode;    /**< Mode de protection (type et permissions du fichier). */
    nlink_t   st_nlink;   /**< Nombre de liens matériels. */
    uid_t     st_uid;     /**< UID du propriétaire. */
    gid_t     st_gid;     /**< GID du groupe propriétaire. */
    dev_t     st_rdev;    /**< ID du périphérique (si fichier spécial). */
    off_t     st_size;    /**< Taille totale en octets. */
    blksize_t st_blksize; /**< Taille des blocs pour les E/S du fichier. */
    blkcnt_t  st_blocks;  /**< Nombre de blocs alloués (en 512 octets). */

    struct timespec st_atim; /**< Temps d'accès (dernier accès). */
    struct timespec st_mtim; /**< Temps de modification (contenu modifié). */
    struct timespec st_ctim; /**< Temps de changement d'état (métadonnées modifiées). */
};
```

## 🔄 chdir ##

```C
#include <unistd.h>

int chdir(const char *path);
```

La fonction prend en paramètre une chaîne de caractère représentant le chemin vers le répertoire où l'on souhaite se déplacer. Ce chemin peut être absolu (commençant par /) ou relatif par rapport au répertoire courant.

### Retour ###

La fonction renvoie 0 en cas de succès et -1 en cas d’échec. En cas d’erreur, `errno` est défini :

- `EACCES` (13): Permission refusée pour accéder au répertoire spécifié.
- `ENOENT` (2): Le répertoire spécifié n'existe pas.
- `ENOTDIR` (20): Une partie du chemin spécifié n'est pas un répertoire.

---

## 📋 stat ##

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int stat(const char *pathname, struct stat *statbuf);
```

La fonction `stat` permet de récupérer des informations sur un fichier ou un répertoire, telles que sa taille, ses permissions, son propriétaire, etc. Elle suit les liens symboliques (contrairement à `lstat`).

### Paramètres ###

- `pathname` : Chemin vers le fichier ou répertoire.
- `statbuf` : Pointeur vers une structure `struct stat` où les informations seront stockées.

### Retour ###

Renvoie 0 en cas de succès, -1 en cas d’échec. En cas d’erreur, `errno` est défini :

- `EACCES` (13) : Permission refusée.
- `ENOENT` (2) : Le fichier n'existe pas.
- `ENOTDIR` (20) : Une composante du chemin n'est pas un répertoire.

---

## 🧲 lstat ##

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int lstat(const char *pathname, struct stat *statbuf);
```

`lstat` est identique à `stat`, mais **ne suit pas** les liens symboliques. Il permet d’obtenir des infos sur le lien lui-même.

### Paramètres ###

- `pathname` : Chemin du fichier ou lien symbolique.
- `statbuf` : Pointeur vers une structure `stat`.

### Retour ###

Renvoie 0 en cas de succès, -1 sinon. En cas d’erreur, `errno` est défini (mêmes valeurs que `stat`).

---

## 🧾 fstat ##

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int fstat(int fd, struct stat *statbuf);
```

`fstat` fonctionne comme `stat`, mais utilise un **descripteur de fichier** au lieu d’un chemin.

### Paramètres ###

- `fd` : Descripteur de fichier valide.
- `statbuf` : Structure où seront stockées les infos.

### Retour ###

Renvoie 0 si tout va bien, -1 sinon. Principales erreurs :

- `EBADF` (9) : `fd` n’est pas un descripteur de fichier valide.

---

## 📂 opendir ##

```C
#include <dirent.h>

DIR *opendir(const char *name);
```

Ouvre un répertoire pour pouvoir en lire le contenu avec `readdir`.

### Paramètres ###

- `name` : Chemin vers le répertoire à ouvrir.

### Retour ###

Retourne un pointeur de type `DIR*` si succès, ou `NULL` sinon.

- `ENOENT` (2) : Le répertoire n'existe pas.
- `ENOTDIR` (20) : Ce n'est pas un répertoire.

---

## 📄 readdir ##

```C
#include <dirent.h>

struct dirent *readdir(DIR *dirp);
```

Lit une entrée (fichier ou dossier) dans un répertoire ouvert avec `opendir`.

### Paramètres ###

- `dirp` : Pointeur `DIR*` obtenu via `opendir`.

### Retour ###

Retourne un pointeur vers une structure `dirent`, ou `NULL` à la fin du répertoire ou en cas d'erreur.

---

## ❌ closedir ##

```C
#include <dirent.h>

int closedir(DIR *dirp);
```

Ferme un répertoire précédemment ouvert avec `opendir`.

### Paramètres ###

- `dirp` : Pointeur vers le répertoire ouvert.

### Retour ###

Retourne 0 en cas de succès, -1 sinon.

- `EBADF` (9) : `dirp` n’est pas un pointeur valide.

---

## 🧵 strerror ##

```C
#include <string.h>

char *strerror(int errnum);
```

Retourne une chaîne de caractères lisible correspondant à un code d’erreur `errno`.

### Paramètres ###

- `errnum` : Code d’erreur (souvent `errno`).

### Retour ###

Retourne une chaîne de caractères statique décrivant l’erreur (ex : `"Permission denied"`).
