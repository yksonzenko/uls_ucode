#ifndef YKSULS_H
#define YKSULS_H

#include "libmx.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <time.h>

#define INVALID_USAGE "usage: uls [-ali] [file ...]"
#define ILLEGAL_OPT "uls: illegal option -- "

#define FLAGS "a l i \0"

typedef struct s_flags {
    int argc;
    char **argv;
    char **all_flags;
    int *switch_flags;
    char **all_obj; // dir and files
    int fi; // flag index
    int count_obj;
}       t_flags;

typedef struct s_lattrib {
    int *id;
    int *bl;
    char *ftype;
    char *rights;
    int *lins;
    char *user;
    int *group;
    int *size;
    int *full_time;
    int *name;
}       t_lattrib;

void mx_check_flags(t_flags *flags);

// errors
void mx_error_illegal_option(t_flags *flags);
void mx_no_file_dir(char *fd);

void mx_print_root_files(t_flags *flags);

void mx_flag_a(t_flags *flags);
void mx_flag_l(t_flags *flags);
void mx_flag_i(t_flags *flags);
void mx_flag_a_l(t_flags *flags);

#endif
