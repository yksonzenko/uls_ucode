#include "yksuls.h"

void mx_cleaner(t_flags *flags, t_lattrib **lattrib) {
    if (flags->all_obj)
        mx_del_strarr(&flags->all_obj);
}
