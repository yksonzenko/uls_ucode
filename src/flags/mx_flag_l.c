#include "uls.h"

static void get_attributes(t_lattrib **lattrib, struct stat sb, int i);
static void check_and_print_files(t_lattrib **lattrib, t_flags *flags, t_sorted_odj *sort);
static void check_and_open_dirs(t_lattrib **lattrib, t_flags *flags, t_sorted_odj *sort);
static void total_blocks(t_flags *flags, t_lattrib **lattrib, t_sorted_odj *sort);

void mx_flag_l(t_flags *flags, t_sorted_odj *sort) {
    mx_alphabet_sort3(flags->all_obj, flags->count_obj);
    mx_file_dir_sort(sort, flags);
    t_lattrib **lattrib = NULL;

    check_and_print_files(lattrib, flags, sort);
    check_and_open_dirs(lattrib, flags, sort);
}

static void check_and_open_dirs(t_lattrib **lattrib, t_flags *flags, t_sorted_odj *sort) {
    DIR *d;
    struct dirent *dir;
    int i = 0;
    sort->len_of_files_array = 0;

    for (int j = 0; j < sort->len_of_dirs_array; j++) {
        d = opendir(sort->dirs[j]);
        while((dir = readdir(d)) != NULL)
            if (dir->d_name[0] != '.') { // case without '-a' and '-A'
                sort->files[i] = mx_strdup(dir->d_name);
                sort->len_of_files_array++;
                i++;
            }
        mx_alphabet_sort3(sort->files, sort->len_of_files_array);
        check_and_print_files(lattrib, flags, sort);
        closedir(d);
    }
}

static void check_and_print_files(t_lattrib **lattrib, t_flags *flags, t_sorted_odj *sort) {
    struct stat sb;
    lattrib = (t_lattrib **)malloc(sizeof(t_lattrib *) * sort->len_of_files_array);
    if (sort->len_of_files_array != 0) {
        for (int i = 0; i < sort->len_of_files_array; i++) {
            lattrib[i] = malloc(sizeof(t_lattrib));
            lattrib[i]->name = mx_strdup(sort->files[i]);
            lstat(lattrib[i]->name, &sb);
            get_attributes(lattrib, sb, i);
            mx_get_acl_xattr(lattrib, i);
        }
        if (sort->len_of_dirs_array != 0)
            total_blocks(flags, lattrib, sort);
        mx_check_what_to_print(flags, lattrib, sort);
        mx_cleaner(flags, lattrib);
    }
}

static void get_attributes(t_lattrib **lattrib, struct stat sb, int i) {
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

static void total_blocks(t_flags *flags, t_lattrib **lattrib, t_sorted_odj *sort) {
    int bl_sum = 0;
    for (int i = 0; i < sort->len_of_files_array; i++) {
        bl_sum += lattrib[i]->bl;
    }
    mx_printstr("total ");
    mx_printint(bl_sum);
    mx_printchar('\n');
}
