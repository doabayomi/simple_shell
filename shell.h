#ifndef SHELL_H_
#define SHELL_H_

int _strcmp(char *first, char *second);
char **get_args(char *command, char *delimiter);
int count_args(char *command, char *delimiter);
char *get_command();
char *get_env_var(char *env_var, int value);
char *construct_new_path(char *command_arg, char *path_dir);
char *get_path(char *command_arg, char **env);
typedef struct builtins
{
	char *name;
	int (*func)(void);
} builtin;

int bin_exit(void);
int bin_env(void);
int (*get_builtin(char *cmd))(void);

#endif
