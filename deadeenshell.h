#ifndef DEADEENSHELL_H
#define DEADEENSHELL_H

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

/* for read/write buffers */
#define LETS_SET_LIMITS 1024
#define SIZE_OF_BUF_WRITE 1024
#define THE_BONEBUFF -1

/* for command chaining */
#define THE_DEF_STATS	0
#define THE_DEF_OR		1
#define THE_DEF_AND		2
#define THE_DEF_SALSAL	3

/* for convert_number() */
#define THE_LETTERS_SMALL_CON	1
#define THE_NUM_PLUS_CONV	2

/* 1 if using system getline() */
#define MY_GETLINESHELL 0
#define MY_STRTOKSHELL 0

#define MY_PAST_ISIN	".simple_shell_history"
#define MY_PAST_MAKS	4096

extern char **myuniver;


/**
 * struct myliststruct - singly linked list
 * @denum: the number field
 * @denstr: a string
 * @next: points to the next node
 */
typedef struct myliststruct
{
	int denum;
	char *denstr;
	struct myliststruct *next;
} list_t;

/**
 *struct theinfopass - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@bein: a string generated from getline containing arguements
 *@beins: an array of strings generated from bein
 *@direct: a string direct for the current command
 *@beinsh: the argument count
 *@numline: the error count
 *@numerrline: the error code for exit()s
 *@flagslines: if on count this line of input
 *@thename: the program filename
 *@theenv: linked list local copy of myuniver
 *@myuniver: custom modified copy of myuniver from LL theenv
 *@pasthist: the pasthist node
 *@friends: the friends node
 *@changecurrent: on if myuniver was changed
 *@stawhats: the return stawhats of the last exec'd command
 *@bashshellbuff: address of pointer to bashshellbuff, on if chaining
 *@ourtype: CMD_type ||, &&, ;
 *@letsread: the fd from which to read line input
 *@numofhist: the pasthist line number count
 */
typedef struct theinfopass
{
	char *bein;
	char **beins;
	char *direct;
	int beinsh;
	unsigned int numline;
	int numerrline;
	int flagslines;
	char *thename;
	list_t *theenv;
	list_t *pasthist;
	list_t *friends;
	char **myuniver;
	int changecurrent;
	int stawhats;

	char **bashshellbuff; /* pointer to cmd ; chain buffer, for memory mangement */
	int ourtype; /* CMD_type ||, &&, ; */
	int letsread;
	int numofhist;
} info_t;

#define INTER_FORAMTION \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct frominside - contains a frominside string and related function
 *@type: the frominside command flag
 *@truefunction: the function
 */
typedef struct frominside
{
	char *type;
	int (*truefunction)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* direct.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *denstr, int fd);

/* string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_functions2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* string_functions3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* string_functions4.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* memory_functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int bfree(void **);

/* more_functions.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* more_functions2.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin_emulators.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* builtin_emulators2.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* getline.c module */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* info.c module */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* theenv.c module */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* env2.c module */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* file_io_functions.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* myliststruct.c module */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* liststr2.c module */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* chain.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
