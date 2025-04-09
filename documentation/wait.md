# Wait functions #

```C
#include <sys/wait.h>
```

## Notes ##

`wait3()` and `wait4()` are both deprecated interfaces; they were attempts to implement something similar to waitpid()—and predates waitpid()—but turned out to be inferior. You shouldn’t use either of them.

## wait ##

```C
pid_t wait(int *wstatus)
```

just waits for the first forked child to die, returns the pid that died, and the status (if set) in wstatus.

## waitpid ##

```C
pid_t waitpid(pid_t pid, int *wstatus, int options)
```

`waitpid()` is a more generalized version; it allows you to pass in flags, and a specific process to wait for; waitpid(-1, &wstatus, 0) is equivalent to wait(&wstatus).

## wait3 ##

```C
pid_t wait3(int *wstatus, int options, struct rusage *rusage)
```

`wait3()` is equivalent to waitpid(-1, &wstatus, options).

## wait4 ##

```C
pid_t wait4(pid, int *wstatus, int options, struct rusage *rusage)
```

`wait4()`is equivalent to waitpid(pid, &wstatus, options).
