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
#include <sys/ioctl.h>

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
    char ftype;
    char *rights;
    int *lins;
    char *user;
    int *group;
    off_t size;
    int *full_time;
    char *name;
}       t_lattrib;

typedef struct s_sorted_obj {
    char **files;
    char **dirs;
    int len_of_files_array;
    int len_of_dirs_array;
}              t_sorted_odj;

void mx_check_flags(t_flags *flags, t_sorted_odj *sort);
void mx_cleaner(t_flags *flags, t_lattrib **lattrib);

// errors
void mx_error_illegal_option(t_flags *flags);
void mx_no_file_dir(char *fd);

void mx_print_root_files(t_flags *flags);

// flags
void mx_flag_l(t_flags *flags, t_sorted_odj *sort);
void mx_specify_type_file(struct stat sb, t_lattrib **lattrib, int i);
void mx_print_permissions_list(t_lattrib **lattrib, struct stat sb);

void mx_flag_a(t_flags *flags);
void mx_flag_i(t_flags *flags, t_sorted_odj *sort);
void mx_flag_a_l(t_flags *flags);

// ilay
void mx_output_by_size_of_wind(char **array, int len_of_array);
void mx_alphabet_sort2(char **array, int len);
int mx_the_biggest_name(char **array, int len);

#endif
