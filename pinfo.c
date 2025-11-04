/* Name: Ashlyn Dedert
 * Assignment: Lab 9 - System Calls
 * Section: CPE 2600 111
 */
/*
 * File: pinfo.c
 * Date: 10/29/2025
 * Description: Displays various process information using standard libraries.
 * Compile with: gcc -o pinfo pinfo.c or make
 * Run with: ./pinfo
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/resource.h>
#include <sched.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int policy;
    int priority;

    // if no PID use current process
    if (argc == 1) {
        pid = getpid();
    } else if (argc == 2) {
        pid = (pid_t)atoi(argv[1]);
        if (pid <= 0) {
            fprintf(stderr, "Invalid PID: %s\n", argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
        return 1;
    }

    // Get scheduling policy
    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("Error getting scheduling policy");
        return 1;
    }

    // Get priority
    priority = getpriority(PRIO_PROCESS, pid);

    // convert policy to string
    const char *policyName;
    switch (policy) {
        case SCHED_OTHER:
            policyName = "SCHED_OTHER";
            break;
        case SCHED_FIFO:
            policyName = "SCHED_FIFO";
            break;
        case SCHED_RR:
            policyName = "SCHED_RR";
            break;
        case SCHED_BATCH:
            policyName = "SCHED_BATCH";
            break;
        case SCHED_IDLE:
            policyName = "SCHED_IDLE";
            break;
        case SCHED_DEADLINE:
            policyName = "SCHED_DEADLINE";
            break;
        default:
            policyName = "UNKNOWN";
            break;      
    }

    // Print results
    printf("Process ID: %d\n", pid);
    printf("Scheduling Policy: %s\n", policyName);
    printf("Priority: %d\n", priority);

    return 0;
}