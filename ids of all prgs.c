/*Explanation:

The program opens the /proc directory which contains information about running processes in the Linux operating system.
It reads the entries in the directory and checks if each entry is a directory and has a numeric name (process ID).
For each process ID, it reads the status file in the corresponding directory to obtain the program ID.
It then prints the program ID.
Note that the program ID is stored in the status file as Pid: followed by the process ID. Therefore, we read the first line of the file and print the characters starting from the 6th position to obtain the program ID.*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void) {
    DIR *dir;
    struct dirent *entry;
    char path[20], pid[10];

    dir = opendir("/proc");
    if (!dir) {
        perror("Unable to open /proc");
        exit(EXIT_FAILURE);
    }

    printf("Running program IDs:\n");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0) {
            sprintf(path, "/proc/%s/status", entry->d_name);
            FILE *fp = fopen(path, "r");
            if (fp != NULL) {
                if (fgets(pid, 10, fp) != NULL) {
                    printf("%s\n", pid + 6);
                }
                fclose(fp);
            }
        }
    }

    closedir(dir);
    return 0;
}
