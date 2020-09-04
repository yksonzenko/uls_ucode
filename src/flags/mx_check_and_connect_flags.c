#include "yksuls.h"

void mx_check_and_connect_flags(t_flags *flags, t_sorted_odj *sort) {
    t_lattrib **lattrib = NULL;
// flag -a
    if (flags->switch_flags[0] == 1 && flags->switch_flags[1] == 0 &&
        flags->switch_flags[2] == 0)
        mx_flag_a(flags);
// flag -l
    if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 1 &&
        flags->switch_flags[2] == 0)
        lattrib = mx_flag_l(flags, sort);
// flag -i
    if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 0 &&
        flags->switch_flags[2] == 1)
        mx_flag_i(flags, sort);
// flags -a and -l
    if (flags->switch_flags[0] == 1 && flags->switch_flags[1] == 1)
        mx_flag_a_l(flags);
    if (flags->switch_flags[1] == 1 && flags->switch_flags[2] == 1)
        mx_flag_l(flags, sort);
    // mx_cleaner(flags, lattrib); // delete struct
}
