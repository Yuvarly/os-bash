/*#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    printf(argv[1]);
    printf("\n");
    printf(argv[2]);

    DIR *d;
    d = opendir("/home/yura/");

    struct dirent *dir;

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name[0] != '.')
            {
                if(dir->d_type == 4)
                {
                    DIR *temp = opendir("/home/yura/" + d);
                }
                printf("%s, %d\n", dir->d_name, dir->d_type);
            }

        }
    closedir(d);
    }


    return 0;
}*/


#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void listFilesRecursively(char *path);

char **c;

int main(int argc, char **argv)
{
    // Directory path to list files
    char path[100];
    c = argv;

    /*printf("%s", c[1]);
    printf("\n");
    printf(argv[2]);
    printf("\n");*/

    listFilesRecursively(c[1]);

    return 0;
}


/**
 * Lists all files and sub-directories recursively
 * considering path as base path.
 */
void listFilesRecursively(char *basePath)
{
    char path[1000];
    char temp[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            if(dp->d_name[0] != '.')
            {
                //printf("%s\n", dp->d_name);

                if (strcmp(dp->d_name, c[2]) == 0)
                {
                    strcpy(temp, basePath);
                    strcat(temp, "/");
                    strcat(temp, dp->d_name);

                    struct stat buf;
                    lstat(temp, &buf);
                    int size = buf.st_size;

                    printf("%s, %s, %d bytes\n", basePath, dp->d_name, size);
                    return;
                }

                // Construct new path from our base path
                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp->d_name);

                listFilesRecursively(path);

            }

        }
    }

    closedir(dir);
}
