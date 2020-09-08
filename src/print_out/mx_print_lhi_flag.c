#include "uls.h"

void mx_print_lhi_flag(t_lattrib **lattrib, t_flags *flags) {
    mx_size_align_right(lattrib, flags);
    mx_index_align_right(lattrib, flags);
    for (int j = 0; j < flags->count_obj; j++) {
        mx_printstr(lattrib[j]->id_str);
        mx_printchar(' ');
        mx_printchar(lattrib[j]->ftype);
        mx_printstr(lattrib[j]->rights);
        mx_printchar(' ');
        mx_printint(lattrib[j]->links);
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
    mx_cleaner(flags, lattrib); // delete struct
}
