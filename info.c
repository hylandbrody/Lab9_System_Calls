/*
 * Name: Brody Hyland
 * Date: 11/3/2026
 * description: This program retrieves and displays various system information, 
 *      including the current time, hostname, operating system details, hardware
 *      type, number of CPUs, and memory statistics. 
 */

// info.c

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>

int main(void)
{
    // Get current time of day in nanoseconds
    struct timespec current_time;

    if (clock_gettime(CLOCK_REALTIME, &current_time) == -1)
    {
        perror("clock_gettime");
        return 1;
    }

    printf("The current time is %lld.%09ld seconds\n",
           (long long)current_time.tv_sec,
           current_time.tv_nsec);

    // Get system network name
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == -1)
    {
        perror("gethostname");
        return 1;
    }

    hostname[sizeof(hostname) - 1] = '\0';

    if (hostname[0] != '\0')
    {
        printf("The system hostname is %s\n", hostname);
    }

    // Get operating system name and version
    struct utsname buffer;

    if (uname(&buffer) == -1)
    {
        perror("uname");
        return 1;
    }

    if (buffer.sysname[0] != '\0')
    {
        printf("The operating system is %s\n", buffer.sysname);
    }

    if (buffer.release[0] != '\0')
    {
        printf("The operating system release is %s\n",
               buffer.release);
    }

    if (buffer.version[0] != '\0')
    {
        printf("The operating system version is %s\n",
               buffer.version);
    }

    // Get system hardware type
    if (buffer.machine[0] != '\0')
    {
        printf("The system hardware type is %s\n",
               buffer.machine);
    }

    // Get number of CPUs
    long cpus = sysconf(_SC_NPROCESSORS_ONLN);

    if (cpus == -1)
    {
        perror("sysconf CPUs");
        return 1;
    }

    printf("The number of CPUs is %ld\n", cpus);

    // Get total amount of physical memory in bytes
    long physical_pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);

    if (physical_pages == -1 || page_size == -1)
    {
        perror("sysconf memory");
        return 1;
    }

    unsigned long long total_memory =
        (unsigned long long)physical_pages *
        (unsigned long long)page_size;

    printf("The total amount of physical memory is %llu bytes\n",
           total_memory);

    // Get amount of free physical memory in bytes
    long available_pages = sysconf(_SC_AVPHYS_PAGES);

    if (available_pages == -1)
    {
        perror("sysconf available memory");
        return 1;
    }

    unsigned long long free_memory =
        (unsigned long long)available_pages *
        (unsigned long long)page_size;

    printf("The amount of free physical memory is %llu bytes\n",
           free_memory);

    return 0;
}