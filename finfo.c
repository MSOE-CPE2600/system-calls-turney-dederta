/* Name: Ashlyn Dedert
 * Assignment: Lab 9 - System Calls
 * Section: CPE 2600 111
 */
/*
 * File: finfo.c
 * Date: 10/29/2025
 * Description: Displays various process information using standard libraries.
 * Compile with: gcc -o finfo finfo.c or make
 * Run with: ./finfo
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

// helper function to get file type as string
const char* getFileType(mode_t mode)
{
    if (S_ISREG(mode)) return "regular file";
    if (S_ISDIR(mode)) return "directory";
    if (S_ISCHR(mode)) return "character device";
    if (S_ISBLK(mode)) return "block device";
    if (S_ISFIFO(mode)) return "FIFO";
    if (S_ISLNK(mode)) return "symbolic link";
    if (S_ISSOCK(mode)) return "socket";
    return "unknown";
}

// helper function to format permission strings like rxwr-xr--
void permsToString(mode_t mode, char out[11])
{
    out[0] = S_ISDIR(mode) ? 'd' : S_ISLNK(mode) ? 'l' : '-';
    out[1] = (mode & S_IRUSR) ? 'r' : '-';
    out[2] = (mode & S_IWUSR) ? 'w' : '-';
    out[3] = (mode & S_IXUSR) ? 'x' : '-';
    out[4] = (mode & S_IRGRP) ? 'r' : '-';
    out[5] = (mode & S_IWGRP) ? 'w' : '-';
    out[6] = (mode & S_IXGRP) ? 'x' : '-';
    out[7] = (mode & S_IROTH) ? 'r' : '-';
    out[8] = (mode & S_IWOTH) ? 'w' : '-';
    out[9] = (mode & S_IXOTH) ? 'x' : '-';
    out[10] = '\0';
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char* filePath = argv[1];
    struct stat fileStat;

    // use lstat to show symlink info when applicable
    if (lstat(filePath, &fileStat) == -1) {
        perror("Error getting file information");
        return 1;
    }

    // 1. File type
    const char *fileType = getFileType(fileStat.st_mode);

    // 2. permissions
    char permStr[11];
    permsToString(fileStat.st_mode, permStr);

    // 3. Owner - UID number
    uid_t ownerUID = fileStat.st_uid;

    // 4. Size in bytes
    off_t fileSize = fileStat.st_size;

    // 5. Last modification time
    char timeBuf[256];
    struct tm lt;
    localtime_r(&fileStat.st_mtime, &lt);
    strncpy(timeBuf, asctime(&lt), sizeof(timeBuf));
    // remove trailing newline from asctime             
    timeBuf[strcspn(timeBuf, "\n")] = '\0';

    // Print results
    printf("File: %s\n", filePath);
    printf("Type: %s\n", fileType);
    printf("Permissions: %s\n", permStr);
    printf("Owner UID: %d\n", ownerUID);
    printf("Size: %ld bytes\n", (long)fileSize);
    printf("Last Modified: %s\n", timeBuf);

    return 0;
}