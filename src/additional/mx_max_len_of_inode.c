#include "uls.h"

int mx_max_len_of_inode(char *obj) {
    int res = 0;
    DIR *d;
    struct dirent *directory;
    d = opendir(obj);
    if (d) {
        while ((directory = readdir(d)) != NULL) {
            if (directory->d_name[0] != '.') {
                if (mx_intlen(directory->d_ino) > res) {
                    res = mx_intlen(directory->d_ino);
                }
            }
        }
    }
    closedir(d);
    return res;
}
