#ifndef YKSULS_H
#define YKSULS_H

#include "libmx.h"

#define INVALID_USAGE "usage: uls [-l] [file ...]"

#define FLAGS "a l i \0"
#define FLAG_a "a"

typedef struct s_flags {
    char **all_flags;
    int *switch_flags;
    bool flag_a;
    bool flag_l;
    bool flag_i;
}       t_flags;

#endif
