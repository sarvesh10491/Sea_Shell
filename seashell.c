#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "shell.h"

//####################
int main()
{
    shell_loop();

    return EXIT_SUCCESS;
}
//####################
// End of seashell.c
//####################