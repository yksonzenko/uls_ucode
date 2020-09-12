#include "uls.h"

void mx_print_li_flag(t_lattrib **lattrib, t_flags *flags, t_sorted_odj *sort) {
    mx_size_align_right(lattrib, flags, sort);
    mx_index_align_right(lattrib, flags, sort);
    mx_links_align_right(lattrib, flags, sort);
    for (int j = 0; j < sort->len_of_files_array; j++) {
        mx_printstr(lattrib[j]->id_str);
        mx_printchar(' ');
        mx_printchar(lattrib[j]->ftype);
        mx_printstr(lattrib[j]->rights);
        mx_printchar(' ');
        mx_printstr(lattrib[j]->lk_str);
        mx_printchar(' ');
        mx_printstr(lattrib[j]->user);
        mx_printstr("  ");
        mx_printstr(lattrib[j]->group);
        mx_printstr("  ");
        mx_printstr(lattrib[j]->size_str);
        mx_printchar(' ');
        mx_printstr(lattrib[j]->time);
        mx_printchar(' ');
        mx_printstr(lattrib[j]->name);
        mx_printchar('\n');
    }
    for (int i = 0; i < sort->len_of_files_array; i++)
        if (lattrib[i]->id_str)
            mx_strdel(&lattrib[i]->id_str);
}
