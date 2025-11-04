/* Name: Ashlyn Dedert
 * Assignment: Lab 9 - System Calls
 * Section: CPE 2600 111
 */
/*
 * File: info.c
 * Date: 10/29/2025
 * Description: Displays various system information using standard libraries.
 * Compile with: gcc -o info info.c or make
 * Run with: ./info
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

int main(int argc, char* argv[])
{
    // Current time in ns since Jan 1, 1970 (<time.h>)
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) != -1) {
        long currentTime = ts.tv_sec * 1e9 + ts.tv_nsec;
        printf("Current time: %ld ns\n", currentTime);
    }

    // System network name (hostname) (<unistd.h>)
    char hostname[1024];
    if (gethostname(hostname, sizeof(hostname)) != -1 && hostname[0] != '\0') {
        printf("System network name: %s\n", hostname);
    } 

    // OS and hardware information (<sys/utsname.h>)
    struct utsname sysinfo;
    if (uname(&sysinfo) != -1) {
        if (sysinfo.sysname[0] != '\0') {
            printf("OS name: %s\n", sysinfo.sysname);
        }
        if (sysinfo.release[0] != '\0') {
            printf("OS release: %s\n", sysinfo.release);
        }
        if (sysinfo.version[0] != '\0') {
            printf("OS version: %s\n", sysinfo.version);
        }
        if (sysinfo.machine[0] != '\0') {
            printf("Machine: %s\n", sysinfo.machine);
        }
    }

    // CPU count (<sys/sysinfo.h>)
    int cpus = get_nprocs(); // number of active CPUs
    if (cpus != -1) {
        printf("Number of CPUs: %d\n", cpus);
    }

    // Memory information (<unistd.h>)
    long pages = sysconf(_SC_PHYS_PAGES);
    long available_pages = sysconf(_SC_AVPHYS_PAGES);
    long page_size = sysconf(_SC_PAGESIZE);

    if (pages != -1 && available_pages != -1 && page_size != -1) {
        long total_memory = pages * page_size;
        long available_memory = available_pages * page_size;
        printf("Total memory: %ld bytes\n", total_memory);
        printf("Available memory: %ld bytes\n", available_memory);
    }
    

    return 0;
}