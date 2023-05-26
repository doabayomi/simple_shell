#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

char *get_input();
int count_args(char *input, char *delimiter);
char **get_args(char *input, char *delimiter);
void free_args(char **args, int arg_count);
char *get_path_var(char **env);
char *create_path(char *command_arg, char *path_dir);
char *get_path(char *command_arg, char **env);

#define MAX_INPUT_SIZE 1024

#endif /* SHELL_H_ */
