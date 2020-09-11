#include "uls.h"

// static void total_blocks(t_flags *flags, t_lattrib **lattrib);

// ./uls -l print output
void mx_check_what_to_print(t_flags *flags, t_lattrib **lattrib, t_sorted_odj *sort) {
    // total_blocks(flags, lattrib);
    if (flags->switch_flags[1] == 1 && flags->switch_flags[2] == 0 &&
            flags->switch_flags[3] == 0)
        mx_print_l_flag(lattrib, flags, sort);
    else if (flags->switch_flags[2] == 1 && flags->switch_flags[1] == 1 &&
            flags->switch_flags[3] == 0)
        mx_print_li_flag(lattrib, flags, sort);
    if (flags->switch_flags[2] == 0 && flags->switch_flags[1] == 1 &&
            flags->switch_flags[3] == 1) {
        mx_flag_h(lattrib, flags);
        mx_print_lh_flag(lattrib, flags, sort);
    }
    if (flags->switch_flags[2] == 1 && flags->switch_flags[1] == 1 &&
            flags->switch_flags[3] == 1) {
        mx_flag_h(lattrib, flags);
        mx_print_lhi_flag(lattrib, flags, sort);
    }
}

// static void total_blocks(t_flags *flags, t_lattrib **lattrib) {
//     int bl_sum = 0;
//     for (int i = 0; i < flags->count_obj; i++) {
//         bl_sum += lattrib[i]->bl;
//     }
//     mx_printstr("total ");
//     mx_printint(bl_sum);
//     mx_printchar('\n');
// }
