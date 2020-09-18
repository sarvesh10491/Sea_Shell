// Builtin shell commands functions declarations

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

int shell_builtins_cnt();

static char *builtin_cmdstr[] = {
  "cd",
  "help",
  "exit"
};

static int (*builtin_func[]) (char **) = {
  &shell_cd,
  &shell_help,
  &shell_exit
};