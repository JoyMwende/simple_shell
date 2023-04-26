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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shell_loop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void chk_cmd(info_t *);
void fork_file_cmd(info_t *);

/* toem_prober.c */
int is_file_cmd(info_t *, char *);
char dupct_char(char *, int, int);
char chk_pth(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errs.c */
void eputs(char *);
int eputchar(char);
int putfd(char c, int fd);
int putsfd(char *str, int fd);

/* toem_str.c */
int strlen(char *);
int strcmp(char *, char *);
char *starts_with(const char *, const char *);
char strcat(char *, char *);

/* toem_str1.c */
char *strcpy(char *, char *);
char *strdup(const char *);
void puts(char *);
int _putchar(char);

/* toem_exts.c */
char *strncpy(char *, char *, int);
char *strncat(char *, char *, int);
char *strchr(char *, char);

/* toem_stamper.c */
char **strsplit(char *, char *);
char **strsplit2(char *, char);

/* toem_realloc.c */
char _memset(char *, char, unsigned int);
void dfree(char **);
void _realloc(void *, unsigned int, unsigned int);

/* toem_mem.c */
int vfree(void **);

/* toem_atoi.c */
int true(info_t *);
int delim_check(char, char *);
int alpha(int);
int _atoi(char *);

/* toem_errs1.c */
int erratoi(char *);
void print_err(info_t *, char *);
int print_d(int, int);
char conv_num(long int, int, int);
void rm_comm(char *);

/* toem_inbuilt.c */
int exit(info_t *);
int cd(info_t *);
int help(info_t *);

/* toem_inbuilt1.c */
int history(info_t *);
int alias(info_t *);

/*toem_getline.c */
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *);
ssize_t rd_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *, char **, size_t *);
void sigintHndler(int);

/* toem_info.c */
void clear_data(info_t *);
void set_data(info_t *, char **);
void free_data(info_t *, int);

/* toem_env.c */
char getenv(info_t *, const char *);
int env(info_t *);
int setenv(info_t *);
int unsetenv(info_t *);
int pop_env_list(info_t *);

/* toem_getenv.c */
char get_env(info_t *);
int unsetenv(info_t *, char *);
int setenv(info_t *, char *, char *);

/* toem_hist.c */
char get_history_file(info_t *info);
int wr_hist(info_t *info);
int rd_hist(info_t *info);
int bld_hist_list(info_t *info, char *buf, int linecount);
int ren_hist(info_t *info);

/* toem_list.c */
list_t add_node(list_t **, const char *, int);
list_t add_node_end(list_t **, const char *, int);
size_t prnt_list_s(const list_t *);
int dlt_node_at_indx(list_t **, unsigned int);
void free_lst(list_t **);

/* toem_list0.c */
size_t linkd_lst_length(const list_t *);
char rtrn_str(list_t *);
size_t prt_lst(const list_t *);
list_t nd_strt(list_t *, char *, char);
ssize_t get_nd_indx(list_t *, list_t *);

/* toem_variab.c */
int is_buf_chain(info_t *, char *, size_t *);
void chck_buf_chain(info_t *, char *, size_t *, size_t, size_t);
int rplc_aliases(info_t *);
int rplc_variabs(info_t *);
int replace_string(char **, char *);

#endif

