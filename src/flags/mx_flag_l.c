#include "yksuls.h"

static void one_obj(char *obj, t_flags *flags, t_lattrib **lattrib);
static void total_blocks(t_flags *flags, t_lattrib **lattrib);

t_lattrib **mx_flag_l(t_flags *flags, t_sorted_odj *sort) {
    t_lattrib **lattrib = (t_lattrib **)malloc(sizeof(t_lattrib *) * 1000);
    for (int i = 0; i < 1000; i++) {
        lattrib[i] = malloc(sizeof(t_lattrib));
    }
    if (flags->count_obj == 0) {
        one_obj(".", flags, lattrib);
    }
    return lattrib;
}

static void one_obj(char *obj, t_flags *flags, t_lattrib **lattrib) {
    DIR *d;
    struct stat sb;
    struct dirent *dir;
    struct passwd *passwd; // get username
    int i = 0;

    d = opendir(obj);
        while ((dir = readdir(d)) != NULL)
            if (dir->d_name[0] != '.')
                flags->count_obj++;
    closedir(d);
    d = opendir(obj);

    while ((dir = readdir(d)) != NULL) {
        if (dir->d_name[0] != '.') {
            lattrib[i]->name = mx_strdup(dir->d_name);
            stat(lattrib[i]->name, &sb);
            mx_specify_type_file(sb, lattrib, i);
            mx_print_permissions_list(lattrib, sb, i);
            lattrib[i]->links = sb.st_nlink;
            passwd = getpwuid(sb.st_uid);
            lattrib[i]->user = mx_strdup(passwd->pw_name);
            lattrib[i]->group = sb.st_gid;
            lattrib[i]->size = sb.st_size;
            mx_time_modif(sb, lattrib, i);
            lattrib[i]->bl = sb.st_blocks;
            i++;
        }
    }
    closedir(d);
// ./uls -l print output
    mx_struct_sort(lattrib, flags);
    total_blocks(flags, lattrib);
    for (int j = 0; j < flags->count_obj; j++) {
        // mx_printint(lattrib[j]->bl);
        // mx_printchar('\t');

        mx_printchar(lattrib[j]->ftype);
        mx_printstr(lattrib[j]->rights);
        mx_printchar(' ');

        mx_printint(lattrib[j]->links);
        mx_printchar('\t');
        mx_printstr(lattrib[j]->user);
        mx_printchar('\t');
        mx_printint(lattrib[j]->group);
        mx_printchar('\t');
        mx_printint(lattrib[j]->size);
        mx_printchar('\t');
        mx_printstr(lattrib[j]->time);
        mx_printchar('\t');
        mx_printstr(lattrib[j]->name);
        mx_printchar('\n');
    }
}

static void total_blocks(t_flags *flags, t_lattrib **lattrib) {
    int bl_sum = 0;
    for (int i = 0; i < flags->count_obj; i++) {
        bl_sum += lattrib[i]->bl;
    }
    mx_printstr("total ");
    mx_printint(bl_sum);
    mx_printchar('\n');
}



// // id flag -i
//             lattrib->id = mx_strdup(dir->d_ino);
//             mx_printint(lattrib->id);
//             // mx_printint(dir->d_ino);
//             mx_printchar('\t');
// // bl flag -s
//             mx_printint(sb.st_blocks);
//             mx_printchar(' ');
// // rights
//             mx_specify_type_file(sb);
//             mx_print_permissions_list(lattrib, sb);
// // end rights
//             char buff[100];
//             ssize_t lxattr = listxattr(string, buff, 100, 0);
//             if (lxattr > 0)
//                 mx_printchar('@');
//             mx_printchar('\t');
//             // ssize_t gxattr = getxattr();
//             mx_printint(sb.st_nlink);
//             mx_printchar('\t');
//             struct passwd *pwd;
//             pwd = getpwuid(sb.st_uid);
//             mx_printstr(pwd->pw_name);
//             mx_printchar('\t');
//             mx_printint(sb.st_gid);
//             mx_printchar('\t');
//             mx_printint(sb.st_size);
//             mx_printchar('\t');
            // char *time = ctime(&sb.st_mtime);
//             time[mx_strlen(time) - 1] = '\0';
//             mx_printstr(time);
//             mx_printchar('\t');
//             mx_printstr(dir->d_name);
//             mx_printchar('\n');
