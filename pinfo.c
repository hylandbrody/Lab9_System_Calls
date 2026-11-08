/*
 * Name: Brody Hyland
 * Date: 11/6/2026
 * description: This program retrieves and displays information about a specific process,
 *      including its process ID, priority, and scheduling policy. 
 */

// pinfo.c

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sched.h>

int main(int argc, char* argv[])
{
    // Get the process ID
    pid_t process_id;

    if (argc == 1)
    {
        process_id = getpid();
    }
    else if (argc == 2)
    {
        process_id = (pid_t)atoi(argv[1]);
    }
    else
    {
        printf("Usage: ./pinfo [PID]\n");
        return 1;
    }

    // Get the process priority
    errno = 0;
    int priority = getpriority(PRIO_PROCESS, process_id);

    if (priority == -1 && errno != 0)
    {
        perror("getpriority");
        return 1;
    }

    printf("The process ID is %d\n", process_id);
    printf("The process priority is %d\n", priority);

    // Get the process scheduling policy
    int policy = sched_getscheduler(process_id);

    if (policy == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }

    // Display the scheduling policy
    if (policy == SCHED_OTHER)
    {
        printf("The scheduling policy is SCHED_OTHER\n");
    }
    else if (policy == SCHED_FIFO)
    {
        printf("The scheduling policy is SCHED_FIFO\n");
    }
    else if (policy == SCHED_RR)
    {
        printf("The scheduling policy is SCHED_RR\n");
    }
    else if (policy == SCHED_BATCH)
    {
        printf("The scheduling policy is SCHED_BATCH\n");
    }
    else if (policy == SCHED_IDLE)
    {
        printf("The scheduling policy is SCHED_IDLE\n");
    }
    else
    {
        printf("The scheduling policy is unknown\n");
    }

    return 0;
}