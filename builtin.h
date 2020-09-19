// Builtin shell commands functions declarations

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

void shell_ll(char ***args);

int shell_builtins_cnt();
int shell_custom_cnt();

static char *builtin_cmdstr[] = {
  "cd",
  "help",
  "exit"
};

static char *custom_cmdstr[] = {
  "ll"
};

static int (*builtin_func[]) (char **) = {
  &shell_cd,
  &shell_help,
  &shell_exit
};

static void (*custom_func[]) (char ***) = {
  &shell_ll
};