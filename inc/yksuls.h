#ifndef YKSULS_H
#define YKSULS_H

#include "libmx.h"
#include <dirent.h>
#include <sys/types.h>

#define INVALID_USAGE "usage: uls [-l] [file ...]"

#define FLAGS "a l i \0"
#define FLAG_a

typedef struct s_flags {
    int argc;
    char **argv;
    char **all_flags;
    int *switch_flags;
    bool flag_a;
    bool flag_l;
    bool flag_i;
}       t_flags;

void mx_flag_i(t_flags *flags);

#endif
