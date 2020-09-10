#include "uls.h"

static void one_obj(char *obj, t_flags *flags, t_lattrib **lattrib);
static void get_attributes(t_lattrib **lattrib, struct stat sb, int i,
                            struct dirent *dir);
static void two_and_more_obj(t_flags *flags, t_lattrib **lattrib);

t_lattrib **mx_flag_l(t_flags *flags, t_sorted_odj *sort) {
    flags->num_dir_file = mx_get_dir_len(".", flags);
    t_lattrib **lattrib = (t_lattrib **)malloc(sizeof(t_lattrib *) *
                            flags->num_dir_file);
    for (int i = 0; i < flags->num_dir_file; i++) {
        lattrib[i] = malloc(sizeof(t_lattrib));
    }
    if (flags->count_obj == 0) {
        one_obj(".", flags, lattrib);
    }
    else if (flags->count_obj >= 1) {
        two_and_more_obj(flags, lattrib);
    }
    return lattrib;
}

static void one_obj(char *obj, t_flags *flags, t_lattrib **lattrib) {
    DIR *d;
    struct stat sb;
    struct dirent *dir;
    int i = 0;

    flags->count_obj = flags->num_dir_file;
    d = opendir(obj);
    while ((dir = readdir(d)) != NULL)
            if (flags->switch_flags[0] == 1 || flags->switch_flags[6] == 1) {
                if (flags->switch_flags[0] == 1) { // '-a' case
                    lattrib[i]->name = mx_strdup(dir->d_name);
                    lstat(lattrib[i]->name, &sb);
                    get_attributes(lattrib, sb, i, dir);
                    mx_get_acl_xattr(lattrib, i);
                    i++;
                }
                else if (flags->switch_flags[6] == 1 && (mx_strcmp(".", dir->d_name) != 0 &&
                        mx_strcmp("..", dir->d_name) != 0)) { // case '-A'
                    lattrib[i]->name = mx_strdup(dir->d_name);
                    lstat(lattrib[i]->name, &sb);
                    get_attributes(lattrib, sb, i, dir);
                    mx_get_acl_xattr(lattrib, i);
                    i++;
                }
            }
            else {
                if (dir->d_name[0] != '.') { // case without '-a' and '-A'
                    lattrib[i]->name = mx_strdup(dir->d_name);
                    lstat(lattrib[i]->name, &sb);
                    get_attributes(lattrib, sb, i, dir);
                    mx_get_acl_xattr(lattrib, i);
                    i++;
                }
            }
    closedir(d);
    mx_struct_sort(lattrib, flags);
    mx_check_what_to_print(flags, lattrib);
}


static void get_attributes(t_lattrib **lattrib, struct stat sb, int i,
                            struct dirent *dir) {
    struct passwd *passwd; // get username
    struct group *groupid; // get group id name
    mx_specify_type_file(sb, lattrib, i);
    mx_print_permissions_list(lattrib, sb, i);
    lattrib[i]->id = sb.st_ino;
    lattrib[i]->links = sb.st_nlink;
    passwd = getpwuid(sb.st_uid);
    lattrib[i]->user = mx_strdup(passwd->pw_name);
    groupid = getgrgid(sb.st_gid);
    if (groupid == NULL)
        lattrib[i]->group = mx_itoa(sb.st_gid);
    else
        lattrib[i]->group = mx_strdup(groupid->gr_name);

    lattrib[i]->size = sb.st_size;
    mx_time_modif(sb, lattrib, i);
    lattrib[i]->bl = sb.st_blocks;
}

static void two_and_more_obj(t_flags *flags, t_lattrib **lattrib) {
    t_sorted_odj *sort = (t_sorted_odj *)malloc(sizeof(t_sorted_odj));
    sort->len_of_dirs_array = sort->len_of_files_array = 0;
    mx_file_dir_sort(sort, flags);
    // if (sort->len_of_files_array > 0) {
    // mx_print_strarr(sort->files, " ");
        // for (int i = 0; i < sort->len_of_files_array; i++)
    //         one_obj(sort->files[0], flags, lattrib);
    // }
    // mx_printint(sort->len_of_dirs_array);
    if (sort->len_of_dirs_array > 0) {
        one_obj(sort->dirs[0], flags, lattrib);
    }
    // if (sort->len_of_files_array != 0) {
    //     mx_output_by_size_of_wind(sort->files, sort->len_of_files_array);
    // }
    // for (int j = 0; j < sort->len_of_dirs_array; ++j) {
    //     if (flags->number_of_obj != 1) {
    //         if (j != 0 || sort->len_of_files_array != 0)
    //             mx_printchar('\n');
    //         mx_printstr(sort->dirs[j]);
    //         mx_printstr(":\n");
    //     }
    //     one_obj(sort->dirs[j], flags, lattrib);
    // }
        if (sort->files)
            mx_del_strarr(&sort->files);
        if (sort->dirs)
            mx_del_strarr(&sort->dirs);
        free(sort);
}
