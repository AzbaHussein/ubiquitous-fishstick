#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/sysinfo.h>

// Function for the first thread to print "Hello" every 5 seconds
void* print_hello(void* arg) {
    while (1) {
        printf("Hello\n");
        sleep(5);
    }
    return NULL;
}

// Function for the second thread to calculate and print the used system memory every 10 seconds
void* print_memory_usage(void* arg) {
    while (1) {
        struct sysinfo sys_info;
        if (sysinfo(&sys_info) != 0) {
            fprintf(stderr, "Error getting system memory usage\n");
            exit(EXIT_FAILURE);
        }
        printf("Used memory: %ld\n", (sys_info.totalram - sys_info.freeram) * sys_info.mem_unit);
        sleep(10);
    }
    return NULL;
}

// Function for the third thread to change the runtime priority of the other two threads every 15 seconds
void* change_thread_priority(void* arg) {
    pthread_t* threads = (pthread_t*)arg;
    int priority = 1;
    while (1) {
        // Change the runtime priority of the first thread
        if (pthread_setschedprio(threads[0], priority) != 0) {
            fprintf(stderr, "Error changing thread priority\n");
            exit(EXIT_FAILURE);
        }
        printf("Changed thread 1 priority to %d\n", priority);
        
        // Change the runtime priority of the second thread
        if (pthread_setschedprio(threads[1], priority) != 0) {
            fprintf(stderr, "Error changing thread priority\n");
            exit(EXIT_FAILURE);
        }
        printf("Changed thread 2 priority to %d\n", priority);
        
        // Update priority for the next iteration
        priority = (priority + 1) % 3;
        
        // Sleep for 15 seconds before changing priority again
        sleep(15);
    }
    return NULL;
}

int main() {
    // Create the three threads
    pthread_t threads[3];
    pthread_create(&threads[0], NULL, print_hello, NULL);
    pthread_create(&threads[1], NULL, print_memory_usage, NULL);
    pthread_create(&threads[2], NULL, change_thread_priority, threads);
    
    // Wait for the threads to finish (which they won't)
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    
    return 0;
}
