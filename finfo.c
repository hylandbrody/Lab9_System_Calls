/*
 * Name: Brody Hyland
 * Date: 11/6/2026
 * description: This program retrieves and displays information about a specific process,
 *      including its process ID, priority, and scheduling policy.
 */

// finfo.c

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char* argv[])
{
    // Check that a filename was provided
    if (argc != 2)
    {
        printf("Usage: ./finfo filename\n");
        return 1;
    }

    // Get information about the file
    struct stat file_info;

    if (stat(argv[1], &file_info) == -1)
    {
        perror("stat");
        return 1;
    }

    printf("File information for %s\n", argv[1]);

    // Determine the file type
    if (S_ISREG(file_info.st_mode))
    {
        printf("The file type is regular file\n");
    }
    else if (S_ISDIR(file_info.st_mode))
    {
        printf("The file type is directory\n");
    }
    else if (S_ISCHR(file_info.st_mode))
    {
        printf("The file type is character device\n");
    }
    else if (S_ISBLK(file_info.st_mode))
    {
        printf("The file type is block device\n");
    }
    else if (S_ISFIFO(file_info.st_mode))
    {
        printf("The file type is FIFO\n");
    }
    else if (S_ISLNK(file_info.st_mode))
    {
        printf("The file type is symbolic link\n");
    }
    else if (S_ISSOCK(file_info.st_mode))
    {
        printf("The file type is socket\n");
    }
    else
    {
        printf("The file type is unknown\n");
    }

    // Display the file permissions
    printf("The file permissions are ");

    if (file_info.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");

    if (file_info.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");

    if (file_info.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");

    if (file_info.st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");

    if (file_info.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");

    if (file_info.st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");

    if (file_info.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");

    if (file_info.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");

    if (file_info.st_mode & S_IXOTH)
        printf("x");
    else
        printf("-");

    printf("\n");

    // Display the owner user ID
    printf("The owner UID is %u\n", (unsigned int)file_info.st_uid);

    // Display the file size in bytes
    printf("The file size is %lld bytes\n",
           (long long)file_info.st_size);

    // Get and display the modification date and time
    struct tm *modification_time = localtime(&file_info.st_mtime);

    if (modification_time == NULL)
    {
        perror("localtime");
        return 1;
    }

    char date_time[100];

    if (strftime(date_time, sizeof(date_time),
                 "%Y-%m-%d %H:%M:%S", modification_time) == 0)
    {
        printf("Could not format modification time\n");
        return 1;
    }

    printf("The modification date and time is %s\n", date_time);

    return 0;
}