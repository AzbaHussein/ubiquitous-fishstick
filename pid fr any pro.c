#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024

int get_process_id(char* process_name) {
    char command[MAX_COMMAND_LENGTH];
    FILE* fp;
    char line[MAX_COMMAND_LENGTH];
    int pid;
    char name[MAX_COMMAND_LENGTH];
    
    // Build the system command to list all running processes
    sprintf(command, "ps -e | grep -m1 '%s' | awk '{print $1}'", process_name);
    
    // Open a pipe to run the command
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Error opening pipe");
        return -1;
    }
    
    // Read the output of the command line by line
    while (fgets(line, MAX_COMMAND_LENGTH, fp) != NULL) {
        // Extract the process ID and process name from the line
        sscanf(line, "%d %s", &pid, name);
        
        // Check if the process name matches the given process name
        if (strcmp(name, process_name) == 0) {
            // Close the pipe and return the process ID
            pclose(fp);
            return pid;
        }
    }
    
    // Close the pipe and return an error code if the process was not found
    pclose(fp);
    return -1;
}

int main() {
    char process_name[MAX_COMMAND_LENGTH];
    int pid;
    
    printf("Enter the process name: ");
    scanf("%s", process_name);
    
    pid = get_process_id(process_name);
    if (pid == -1) {
        printf("Process not found\n");
    } else {
        printf("Process ID of %s is %d\n", process_name, pid);
    }
    
    return 0;
}
