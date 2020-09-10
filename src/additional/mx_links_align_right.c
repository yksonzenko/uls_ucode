#include "uls.h"

static int max_len_of_links(t_lattrib **lattrib, t_flags *flags);

void mx_links_align_right(t_lattrib **lattrib, t_flags *flags) {
    int temp = 0;
    char *temp_str = NULL;
    int max_len_of_lk = 0;

    max_len_of_lk = max_len_of_links(lattrib, flags);
    for (int i = 0; i < flags->count_obj; i++) {
        lattrib[i]->lk_str = mx_strnew(max_len_of_lk);
        temp = max_len_of_lk - mx_intlen(lattrib[i]->links);
        if (temp != 0) {
            for (int j = 0; j < temp; j++) {
                if (j == 0)
                    lattrib[i]->lk_str = mx_strcpy(lattrib[i]->lk_str, " ");
                else
                    lattrib[i]->lk_str = mx_strcat(lattrib[i]->lk_str, " ");
            }
            temp_str = mx_itoa(lattrib[i]->links);
            lattrib[i]->lk_str = mx_strcat(lattrib[i]->lk_str, temp_str);
        }
        else {
            temp_str = mx_itoa(lattrib[i]->links);
            lattrib[i]->lk_str = mx_strcpy(lattrib[i]->lk_str, temp_str);
        }
        if (temp_str)
            mx_strdel(&temp_str);
    }
}
static int max_len_of_links(t_lattrib **lattrib, t_flags *flags) {
    int res = 0;

    for (int i = 0; i < flags->count_obj; i++) {
        if (mx_intlen(lattrib[i]->links) > res)
            res = mx_intlen(lattrib[i]->links);
    }
    return res;
}
