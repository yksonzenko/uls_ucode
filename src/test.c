#include <dirent.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(void)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%-8s\t", dir->d_name);
        }
        printf("\n");
        closedir(d);
    }
    // int i;
    // for(i = 1; i<20; i++)
    // printf("%8d %8d %8d %8d\n", i, i*i, i*i*i, i*i*i*i);
    return(0);
}

// int main (int argc, char **argv)
// {
//     struct winsize w;
//     ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

//     printf ("lines %d\n", w.ws_row);
//     printf ("columns %d\n", w.ws_col);
//     return 0;  // make sure your main returns int
// }
