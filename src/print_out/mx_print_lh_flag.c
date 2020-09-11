#include "uls.h"

void mx_print_lh_flag(t_lattrib **lattrib, t_flags *flags, t_sorted_odj *sort) {
    mx_size_align_right(lattrib, flags, sort);
    mx_links_align_right(lattrib, flags, sort);
    for (int j = 0; j < sort->len_of_files_array; j++) {
        mx_printchar(lattrib[j]->ftype);
        mx_printstr(lattrib[j]->rights);
        mx_printchar(' ');
        mx_printstr(lattrib[j]->lk_str);
        mx_printchar(' ');
        mx_printstr(lattrib[j]->user);
        mx_printstr("  ");
        mx_printstr(lattrib[j]->group);
        mx_printstr("  ");
        mx_printstr(lattrib[j]->size_with_type);
        mx_printchar(' ');
        mx_printstr(lattrib[j]->time);
        mx_printchar(' ');
        mx_printstr(lattrib[j]->name);
        mx_printchar('\n');
    }
    // for (int i = 0; i < flags->count_obj; i++)
    //     if (lattrib[i]->size_with_type)
    //         mx_strdel(&lattrib[i]->size_with_type);
}
