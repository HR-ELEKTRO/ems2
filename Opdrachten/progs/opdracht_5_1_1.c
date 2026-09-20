/*
 * Copyright (c) 2026, Hogeschool Rotterdam.
 */

// Needed for PRINTF()
#include <fsl_debug_console.h>

// Needed for BOARD_InitHardware()
#include <app.h>

// Needed for vTaskStartScheduler()
#include <FreeRTOS.h>
#include <task.h>

// Needed for pthread functions
#include <FreeRTOS_POSIX/pthread.h>
// Needed for usleep()
#include <FreeRTOS_POSIX/unistd.h>
// Needed for redefinition of errno
#include <FreeRTOS_POSIX/errno.h>

// Function to check the return value of pthread functions
// and print an error message if needed
void check(int error) {
    if (error != 0) {
        PRINTF("Error: %s\n", strerror(error));
        while (1);
    }
}

// Function that will be executed by the thread
void *my_thread_function(void *arg) {
    PRINTF("Start counting...\n");
    for (int i = 0; i < 10; i++) {
        sleep(1); // sleep for 1 second
        PRINTF("Still counting %d...\n", i + 1);
    }
    PRINTF("Finished counting!\n");
    return NULL;
}

void *main_thread(void *arg) {
    PRINTF("This program will count from 1 to 10 in a separate thread.\n");

    // Create a thread to run my_thread_function
    pthread_t my_thread_handle;
    check( pthread_create(&my_thread_handle, NULL, &my_thread_function, NULL) );

    // Wait for the thread to finish
    check( pthread_join(my_thread_handle, NULL) );

    return NULL;
}

int main() {
    // Init board hardware
    BOARD_InitHardware();
    
    pthread_attr_t main_thread_attr;
    check( pthread_attr_init(&main_thread_attr) );
    check( pthread_attr_setdetachstate(&main_thread_attr, PTHREAD_CREATE_DETACHED) );
    check( pthread_attr_setstacksize(&main_thread_attr, 1024) );

    struct sched_param main_thread_shed_param;
    check( pthread_attr_getschedparam(&main_thread_attr, &main_thread_shed_param) );
    // The main thread must have the highest priority because this thread will start
    // the other threads and we want to study the interaction between those other threads
    main_thread_shed_param.sched_priority = sched_get_priority_max(SCHED_OTHER);
    check( pthread_attr_setschedparam(&main_thread_attr, &main_thread_shed_param) );

    pthread_t main_thread_handle;
    check( pthread_create(&main_thread_handle, &main_thread_attr, main_thread, NULL) );

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();
    // We should never get here as control is now taken by the scheduler
    
    check( pthread_attr_destroy(&main_thread_attr) );

    return EXIT_SUCCESS;
}
