#ifndef YKSULS_H
#define YKSULS_H

#include "libmx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>

#define INVALID_USAGE   "usage: uls [-ali] [file ...]"
#define ILLEGAL_OPT     "uls: illegal option -- "

#define FLAGS   "a l i \0"

#define RED     "\x1B[31m"
#define GRN     "\x1B[32m"
#define YEL     "\x1B[33m"
#define BLU     "\x1B[34m"
#define MAG     "\x1B[35m"
#define CYN     "\x1B[36m"
#define WHT     "\x1B[37m"
#define RESET   "\x1B[0m"

typedef struct s_flags {
    int argc;
    char **argv;
    char **all_flags;
    int *switch_flags;
    char **all_obj; // dir and files
    int fi; // flag index
    int count_obj; // number of objects from argv
    int num_dir_file; // number of files and dirs from root
}       t_flags;

typedef struct s_lattrib {
    int id;
    int bl;
    char ftype;
    char *rights;
    int links;
    char *user;
    int group;
    int size;
    char *time;
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

//additional
void mx_struct_sort(t_lattrib **lattrib, t_flags *flags);

// errors
void mx_error_illegal_option(t_flags *flags);
void mx_no_file_dir(char *fd);

// flags
t_lattrib **mx_flag_l(t_flags *flags, t_sorted_odj *sort);
void mx_specify_type_file(struct stat sb, t_lattrib **lattrib, int i);
void mx_print_permissions_list(t_lattrib **lattrib, struct stat sb, int i);
void mx_time_modif(struct stat sb, t_lattrib **lattrib, int i);
void mx_check_and_connect_flags(t_flags *flags, t_sorted_odj *sort);

// print output
void mx_print_root_files(t_flags *flags);

void mx_flag_a(t_flags *flags);
void mx_flag_i(t_flags *flags, t_sorted_odj *sort);
void mx_flag_a_l(t_flags *flags);

// ilay
void mx_output_by_size_of_wind(char **array, int len_of_array);
void mx_alphabet_sort2(char **array, int len);
int mx_the_biggest_name(char **array, int len);

#endif
