#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "shell.h"
#include "builtin.h"

// Builtin shell commands functions
//==================================

int shell_builtins_cnt() {
    return sizeof(builtin_cmdstr) / sizeof(char *);
}

int shell_custom_cnt() {
    return sizeof(custom_cmdstr) / sizeof(char *);
}


int shell_cd(char **args)
{
    if(args[1] == NULL){
        fprintf(stderr, "Shell: expected argument to \"cd\"\n");
    } 
    else{
        if(chdir(args[1]) != 0){
            perror("SeaShell");
        }
    }
    return 1;
}


int shell_help(char **args)
{
    int i;
    printf("Custom shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < shell_builtins_cnt(); i++) {
        printf("  %s\n", builtin_cmdstr [i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}


int shell_exit(char **args)
{
    return 0;
}


void shell_ll(char ***args)
{
    (*args)[0] = "ls";
    (*args)[1] = "-lrt";
}
//####################
// End of builtin.c
//####################