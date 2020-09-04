#include "yksuls.h"

int mx_max_len_of_size(t_lattrib **lattrib, t_flags *flags) {
    int res = 0;

    for (int i = 0; i < flags->count_obj; i++) {
        if (mx_intlen(lattrib[i]->size) > res)
            res = mx_intlen(lattrib[i]->size);
    }
    return res;
}
