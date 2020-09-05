#include "uls.h"

void mx_check_and_connect_flags(t_flags *flags, t_sorted_odj *sort) {
    t_lattrib **lattrib = NULL;
// all flags: -a -l -i -h -p

// flag -l
    if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 1 &&
        flags->switch_flags[2] == 0)
        lattrib = mx_flag_l(flags, sort);
// flag -i
    if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 0 &&
        flags->switch_flags[2] == 1)
        mx_flag_i(flags);
// flags -i and -l
    if (flags->switch_flags[1] == 1 && flags->switch_flags[2] == 1)
        mx_flag_l(flags, sort);
// flags -h and -l
    if (flags->switch_flags[1] == 1 && flags->switch_flags[3] == 1) {
        mx_flag_h(lattrib, flags);
        mx_print_lh_flag(lattrib, flags);
    }
// flags -h
    if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 0 &&
        flags->switch_flags[2] == 0 && flags->switch_flags[3] == 1 &&
        flags->switch_flags[4] == 0)
        mx_print_root_files(flags);
// flags -p
    if (flags->switch_flags[0] == 0 && flags->switch_flags[1] == 0 &&
        flags->switch_flags[2] == 0 && flags->switch_flags[3] == 0 &&
        flags->switch_flags[4] == 1)
        mx_flag_p(flags);
}
