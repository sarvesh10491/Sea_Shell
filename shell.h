// Shell commands functions declarations

char *cmdline_read();
char **cmdline_split(char *line);
int shell_launch(char **args);
int cmd_execute(char **args);
void shell_loop();