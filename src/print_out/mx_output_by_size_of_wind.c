#include "yksuls.h"

static void one_line_output(char **array, int len_of_array, int max_len);
static void multiple_line_output(char **array, int len_of_array, int max_len, struct winsize window);

void mx_output_by_size_of_wind(char **array, int len_of_array) {
    int length_of_line = 0;
    struct winsize window;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
    //window.ws_col = 68;
    int max_len = mx_the_biggest_name(array, len_of_array) + 4;
    if (max_len % 8 != 0) {
        while (max_len % 8 != 0) {
            max_len++;
        }
    }
    if (max_len >= window.ws_col) {
        window.ws_col = max_len + 1;
    }
    if (max_len * len_of_array <= window.ws_col) {
        one_line_output(array, len_of_array, max_len);
    } else {
        multiple_line_output(array, len_of_array, max_len, window);
    }
}

static void one_line_output(char **array, int len_of_array, int max_len) {
    int temp = 0;
    for (int i = 0; i < len_of_array; i++) {
        temp = max_len - mx_strlen(array[i]);
        mx_printstr(array[i]);
        if (temp != 0) {
            for (int j = 0; j < temp; ++j) {
                mx_printchar(' ');
            }
        }
    }
    mx_printchar('\n');
}

static void multiple_line_output(char **array, int len_of_array, int max_len, struct winsize window) {
    int number_of_col = len_of_array / 2 + 1;
    int number_objs_in_col = 0;
    int temp = 0;
    int k = 0;
    while (true) {
        if (number_of_col * max_len <= window.ws_col) {
            break;
        }
        else {
            if (number_of_col % 2 != 0) {
                number_of_col = number_of_col / 2 + 1;
            }
            else {
                number_of_col = number_of_col / 2;
            }
        }
    }
    if (len_of_array % number_of_col != 0) {
        number_objs_in_col = len_of_array / number_of_col + 1;
    }
    else {
        number_objs_in_col = len_of_array / number_of_col;
    }
    for (int i = 0; i < number_objs_in_col; i++) {
        temp = max_len - mx_strlen(array[i]);
        mx_printstr(array[i]);
        if (temp != 0) {
            for (int j = 0; j < temp; ++j) {
                mx_printchar(' ');
            }
        }
         k = i;
        while (k + number_objs_in_col <= len_of_array - 1) {
            k += number_objs_in_col;
            temp = max_len - mx_strlen(array[k]);
            mx_printstr(array[k]);
            if (temp != 0) {
                for (int j = 0; j < temp; ++j) {
                    mx_printchar(' ');
                }
            }
        }
        mx_printchar('\n');
    }
}
