#include "yksuls.h"

/*
 * ACL for -l flag
 */
void mx_print_permissions_list(t_lattrib **lattrib, struct stat sb) {
    for (int i = 0; i < 10; i++) {
        lattrib[i]->rights = mx_strnew(9);
            for (int j = 0; j < 9; j++) {
                lattrib[i]->rights[j] = '-';
                int mode = sb.st_mode;
                    lattrib[i]->rights[0] = ((mode & S_IRUSR) ? 'r' : '-');
                    lattrib[i]->rights[1] = ((mode & S_IWUSR) ? 'w' : '-');
                    lattrib[i]->rights[2] = ((mode & S_IXUSR) ? 'x' : '-');
                    lattrib[i]->rights[3] = ((mode & S_IRGRP) ? 'r' : '-');
                    lattrib[i]->rights[4] = ((mode & S_IWGRP) ? 'w' : '-');
                    lattrib[i]->rights[5] = ((mode & S_IXGRP) ? 'x' : '-');
                    lattrib[i]->rights[6] = ((mode & S_IROTH) ? 'r' : '-');
                    lattrib[i]->rights[7] = ((mode & S_IWOTH) ? 'w' : '-');
                    lattrib[i]->rights[8] = ((mode & S_IXOTH) ? 'x' : '-');
                // mx_printstr(lattrib->rights);
            }
    }
}
