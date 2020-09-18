#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "shell.h"
#include "builtin.h"

#define TOKEN_BUF_SIZE 64
#define TOKEN_DELIMIT " \t\r\n\a"

char *cmdline_read()
{
    char *line = NULL;
    size_t bufsize = 0;

    if(getline(&line, &bufsize, stdin) == -1){
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);  // EOF was received
        } 
        else{
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}


char **cmdline_split(char *line)
{
    int bufsize = TOKEN_BUF_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens){
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIMIT);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if(position >= bufsize){
            bufsize += TOKEN_BUF_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMIT);
    }
    tokens[position] = NULL;
    return tokens;
}


int shell_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {   // Child process
        if (execvp(args[0], args) == -1){
            perror("SeaShell");
        }
        exit(EXIT_FAILURE);
    } 
    else if(pid < 0){   // Error forking
        perror("SeaShell");
    } 
    else{    // Parent process
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}


int cmd_execute(char **args)
{
    int i;

    if(args[0] == NULL)     // Check : empty command input
        return 1;

    for(i = 0; i < shell_builtins_cnt(); i++){
        if(strcmp(args[0], builtin_cmdstr[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }

    return shell_launch(args);
}


void shell_loop()
{
    char *cmdline;
    char **cmdargs;
    int status;
    char cwd[1024];

    do{
        getcwd(cwd, sizeof(cwd)); 
        printf("%s => ", cwd);

        cmdline = cmdline_read();
        cmdargs = cmdline_split(cmdline);
        status = cmd_execute(cmdargs);

        free(cmdline);
        free(cmdargs);
        
    } while (status);
}
//####################
// End of shell.c
//####################