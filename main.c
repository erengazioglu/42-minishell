#include <stdio.h>
#include <readline/readline.h>
#include <readline/readline.h>
// #include <readline/history.h>

int main(int ac, char **av){
	(void )ac;
	printf("buffer = <%s>", readline(av[1]));
	return 0;
}
