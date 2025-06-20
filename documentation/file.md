# File Management #

## Basics ##

The file redirections are tested before the execution of the command. Each file is tested from left to right in theory, one by one, if there's a heredoc, it's tested BEFORE other types.

```sh
$> ls -l
-rw-r--r-- 1 ppontet 2024_lyon  0 Apr  8 13:53 infile
---------- 1 ppontet 2024_lyon 80 Apr  8 10:54 infile2
-rw-rw-rw- 1 ppontet 2024_lyon  0 Apr  8 10:58 outfile
$> cat < infile < infile2 > outfile >outfile2
bash: infile2: Permission denied
$> cat -e outfile
$
```

If all the access are good, it creates the outfiles with permissions 644, but outputs only on the last outfile.

```sh
$> ls -l
-rw-r--r--  1 ppontet 2024_lyon    0 Apr  8 13:55 infile
-rwxrwxrwx  1 ppontet 2024_lyon    0 Apr  8 13:55 infile2
-rw-r--r--  1 ppontet 2024_lyon    0 Apr  8 13:56 outfile
-rw-r--r--  1 ppontet 2024_lyon    0 Apr  8 13:56 outfile2
```

```sh
$> cat < infile < infile2 > outfile >outfile2
$> cat -e infile
contenu du premier fichier$
$> cat -e infile2
un autre contenu$
$> cat -e outfile
$
$> cat -e outfile2
un autre contenu$
```

If just one doesn't have the right permissions, assert an error and stop the execution of the command (pipe still works but receive nothing).

```sh
$> ls -l outfile infile
---------- 1 ppontet 2024_lyon 80 Apr  8 10:54 infile
-rwxrwxrwx 1 ppontet 2024_lyon  0 Apr  8 10:58 outfile
$> cat < infile | cat > outfile
bash: infile: Permission denied
$> cat -e outfile
$
```

## Infile ##

An infile is a file used as an input. It should have the right permissions to work correctly. It should exist AND be readable.

```sh
if
 file->exist == 1
 file->perms_read == 1
return OK
```

```sh
if
 file->exist == 0
return bash: infile: No such file or directory
```

```sh
if
 file->exist == 1
 file->perms_read == 0
return bash: infile: Permission denied
```

Notes : Write permissions doesn't need to be checked as the file is never opened in write mode.

## Here-Doc ##

A Here-Doc is a temporary file used as a cache and stores all the informations from the prompt (interactibe or not). The temporary file is destroyed after use.

If there's a here-doc and other infile after (last has priority over others), it's created and filled but never used.

```sh
$>cat << eof < infile > outfile
>it's
>a
>heredoc
>eof
$>cat infile
contenu du fichier infile
$>cat outfile
contenu du fichier infile
```

Same thing when it's not the first in the line, but as Here-Docs has priority, it's created before anything else and not used in the following case.

```sh
$> ls -l outfile infile
---------- 1 ppontet 2024_lyon 80 Apr  8 10:54 infile2
$>cat < infile << eof < infile2 >> outfile
>heredoc
>eof
bash: infile: No such file or directory
$>cat infile2
contenu du fichier infile2
$>cat outfile
cat: outfile: No such file or directory
```

## Outfile ##

An outfile is a file used as an output. It should have the right permissions to work correctly. It should exist OR not, if it exist, it should be writeable.

```sh
if
 file->exist == 0
return OK
```

```sh
if
 file->exist == 1
 file->perms_write == 1
return OK
```

```sh
if
 file->exist == 1
 file->perms_write == 0
return bash: infile: Permission denied
```

Notes : Read permissions doesn't need to be checked as the file is never opened in read mode.

## Outfile - Append mode ##

Works exactly as a outile but adds the content of the input at the end, not at the start.

### Others - Here-String ###

Works as a Here-Doc but without a delimiter and is not interactive, you just type a string and it's used as input.

```sh
$> cat <<< "here-string right here <-"
here-string right here <-
```
