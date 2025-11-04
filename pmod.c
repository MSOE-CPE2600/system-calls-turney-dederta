/* Name: Ashlyn Dedert
 * Assignment: Lab 9 - System Calls
 * Section: CPE 2600 111
 */
/*
 * File: pmod.c
 * Date: 10/29/2025
 * Description: Modifies process niceness and sleeps using nanosleep.
 * Compile with: gcc -o pmod pmod.c or make
 * Run with: ./pmod
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    // decrease niceness by 10 (increase priority)
    int ret = nice(-10);
    if (ret == -1)
    {
        perror("Error changing niceness");
        // not fatal
    }

    // sleep for 1,837,272,638 nanoseconds
    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 837272638;
    nanosleep(&ts, NULL);

    // goodbye message
    printf("Goodbye World!\n");

    return 0;
}