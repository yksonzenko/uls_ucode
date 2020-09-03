#include "yksuls.h"

/*
 * ACL for -l flag
 */
void mx_print_permissions_list(t_lattrib **lattrib, struct stat sb, int i) {
    lattrib[i]->rights = mx_strnew(11);
    int mode = sb.st_mode;
    // ssize_t lxattr = listxattr(, NULL, 0, XATTR_NOFOLLOW);

    lattrib[i]->rights[0] = ((mode & S_IRUSR) ? 'r' : '-');
    lattrib[i]->rights[1] = ((mode & S_IWUSR) ? 'w' : '-');
    lattrib[i]->rights[2] = ((mode & S_IXUSR) ? 'x' : '-');
    lattrib[i]->rights[3] = ((mode & S_IRGRP) ? 'r' : '-');
    lattrib[i]->rights[4] = ((mode & S_IWGRP) ? 'w' : '-');
    lattrib[i]->rights[5] = ((mode & S_IXGRP) ? 'x' : '-');
    lattrib[i]->rights[6] = ((mode & S_IROTH) ? 'r' : '-');
    lattrib[i]->rights[7] = ((mode & S_IWOTH) ? 'w' : '-');
    lattrib[i]->rights[8] = ((mode & S_IXOTH) ? 'x' : '-');
    // lattrib[i]->rights[9] = ((lxattr) ? '@' : ' ');
}
