#include "uls.h"

void mx_cleaner(t_flags *flags, t_lattrib **lattrib) {
    // if (flags->all_obj) {
    //     mx_strdel(&flags->all_obj[999]);
    //     mx_del_strarr(&flags->all_obj);
    // }
    if (lattrib) {
        for (int i = 0; i < flags->count_obj; i++) {
            if (lattrib[i]->rights)
                mx_strdel(&lattrib[i]->rights);
            if (lattrib[i]->user)
                mx_strdel(&lattrib[i]->user);
            if (lattrib[i]->time)
                mx_strdel(&lattrib[i]->time);
            if (lattrib[i]->name)
                mx_strdel(&lattrib[i]->name);
            if (lattrib[i]->size_str)
                mx_strdel(&lattrib[i]->size_str);
            // if (lattrib[i]->size_with_type)
            //     mx_strdel(&lattrib[i]->size_with_type);
            if (lattrib[i]->group)
                mx_strdel(&lattrib[i]->group);
            // if (lattrib[i]->id_str)
            //     mx_strdel(&lattrib[i]->id_str);
            if (lattrib[i]->lk_str)
                mx_strdel(&lattrib[i]->lk_str);
            if (lattrib[i])
                free(lattrib[i]);
        }
        free(lattrib);
    }
}
