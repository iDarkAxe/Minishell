#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main(void)
{
	char *str;

	str = readline("bonjour : ");
	if (str)
		printf("%s", str);
	free(str);
}
