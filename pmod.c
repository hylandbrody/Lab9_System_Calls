/*
 * Name: Brody Hyland
 * date: 11/6/2026
 * description: This program retrieves and displays various system information,
 *      including the current time, hostname, operating system details, hardware
 *      type, number of CPUs, and memory statistics.
 */

// pmod.c

#define _POSIX_C_SOURCE 199309L
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int main(void)
{
    // Reduce the process priority by increasing its nice value
    errno = 0;

    int priority = nice(10);

    if (priority == -1 && errno != 0)
    {
        perror("nice");
        return 1;
    }

    printf("The new process priority is %d\n", priority);

    // Sleep for 1,837,272,638 nanoseconds
    struct timespec sleep_time;

    sleep_time.tv_sec = 1;
    sleep_time.tv_nsec = 837272638;

    // Continue sleeping if interrupted
    while (nanosleep(&sleep_time, &sleep_time) == -1)
    {
        if (errno != EINTR)
        {
            perror("nanosleep");
            return 1;
        }
    }

    // Print goodbye message
    printf("Goodbye!\n");

    return 0;
}