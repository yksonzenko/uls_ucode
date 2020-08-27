#include "yksuls.h"

/*
 * Speciying type of files for -l flag
 */
void mx_specify_type_file(struct stat sb) {
    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:  mx_printchar('b'); break; /*block device*/
        case S_IFCHR:  mx_printchar('c'); break; /*character device*/
        case S_IFDIR:  mx_printchar('d'); break; /*directory*/
        case S_IFIFO:  mx_printchar('p'); break; /*named pipe (fifo)*/
        case S_IFLNK:  mx_printchar('l'); break; /*symlink*/
        case S_IFREG:  mx_printchar('-'); break; /*regular file*/
        case S_IFSOCK: mx_printchar('s'); break; /*socket*/
        default:       mx_printchar('?'); break; /**/
    }
}
