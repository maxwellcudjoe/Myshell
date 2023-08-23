#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* this is comments for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/*this is comments for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*this is comments for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/*this is comments 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - this will singly linked list
 * @num: defines the number field
 * @str: a variable for a string
 * @next: this will be a pointer that points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - this will be a container that contains pseudo-arguements to pass into a function,
 *		by allowing a uniform prototype that will be used for function pointer struct
 *@arg: this is a variable for a string generated that will be from getline containing arguements
 *@argv:this is a container for  an array of strings generated from arg
 *@path: this is will be a string path for the current command
 *@argc: ths is will be the argument count
 *@line_count: this will be used forthe error count
 *@err_num: this will be for  the error code for in the exit()s
 *@linecount_flag:this will used if on count this line of input
 *@fname: this is the variable for the program filename
 *@env: this is variable for a linked list for a  local copy of environ
 *@environ: This will be a custom modified copy of the environ from LL env
 *@history: This is variable for the the history node
 *@alias: the Variable name for the actual alias node
 *@env_changed: the variable that will be used on if the environ was changed
 *@status: this is the return status of the last exec'd command 
 *@cmd_buf: This is the pointer addres that will be the address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: The actual CMD_type ||, &&, ;
 *@readfd: This is the variable for fd from which to read line input
 *@histcount: This will be used for the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /*for a  pointer to cmd ; then a chain buffer, in  for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - This will contain a built in string and its related function
 *@type: This is the Built in command flag
 *@func: This represent the Function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



/* MyCode__errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* MyCode__string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* MyCode__string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char); 

/* MyCode__shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* MyCode__parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* MyCode_loophsh.c */
int loophsh(char **);

/* MyCode__exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* MyCode__tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* MYCode__environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* MyCode__getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* MyCode___history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* MyCode__realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* MyCode__memory.c */
int bfree(void **);

/* Mycode___atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* MyCode__ors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* MyCode__builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* MyCode__builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*MyCode_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* MyCode__getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
/* MyCode__ts.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* MyCode___lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* MyCode__vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

