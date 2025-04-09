# Recherche d'informations #

```C
str = readline();
```

```r
str == "ec""ho bonjour | cat | ls"
str == "ec""ho bonjour "
str == " | cat"
str == " | ls"
```

```r
str == "ec""ho bonjour | cat | ls"
cherche '|'
split sur str : 3 morceaux
str == "ec""ho bonjour "
str == " | cat"
str == " | ls"
nettoie morceaux
str == "echo bonjour "
str == " | cat"
str == " | ls"
executer
```

```r
str == "ec""ho bonjour | cat | ls"
nettoyer
str == "echo bonjour | cat | ls"
cherche '|'
split sur str : 3 morceaux
str == "echo bonjour "
str == " | cat"
str == " | ls"
executer
```

```r
str == "< infile cat | ls > outfile"
executer
```

```r
str == "< infile cat | ls > outfile | cat > outfile2"
cherche '|'
split sur str : 2 morceaux
str == "< infile cat | ls > outfile"
str == "< outfile cat > outfile2"
executer
```

```r
str == "< infile cat | ls | cat > outfile2"
cherche '|'
split sur str : 2 morceaux
str == "< infile cat | ls > outfile"
str == "< outfile cat > outfile2"
suppr outfile
executer
```

```r
str == "< infile cat | ls | cat > outfile2 | cat infile > outfile"
cherche '|'
split sur str : 2 morceaux
str == "< infile cat | ls > outfile"
str == "< outfile cat > outfile2"
str == "< outfile2 cat > outfile"
suppr outfile
executer
```

MEMES :

* `< infile cat | ls | cat > outfile2 | cat infile > outfile`
* `< infile cat | ls | cat > outfile2 | < infile cat > outfile`
* `< infile cat | ls | cat > outfile2 | cat < infile > outfile`
* `< infile cat | ls | cat > outfile2 | cat outfile2 < infile > outfile`

DIFFERENT :

* `< infile cat | ls | cat > outfile2 | cat > outfile`

ici, outfile est vide MAIS est créé.

```r
< infile cat | ls | cat > outfile2
cat outfile2 < infile > outfile
```

MEME QUE

* `< infile cat | ls | cat > outfile2 | cat outfile2 < infile > outfile`

EN GROS :

* SI `>` -> rien dans le pipe, comme si `;`
* SI `<` -> ignorer le pipe, comme si `;`
