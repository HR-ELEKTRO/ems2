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

int counter = 0;

// Function that will add 1 to the counter for 100000 times
void *adder(void *arg) {
    for (int i = 0; i < 100000; i++) {
        counter++;
    }
    return NULL;
}

void *main_thread(void *arg) {
    PRINTF("This program will increment a global counter with two");
    PRINTF(" threads.\nThis causes a synchronization issue, so ");
    PRINTF("the final value of the counter is not predictable.\n");

    // Create two threads to run the function adder
    pthread_t t1, t2;
    check( pthread_create(&t1, NULL, adder, NULL) );
    check( pthread_create(&t2, NULL, adder, NULL) );

    // Wait for the threads to finish
    check( pthread_join(t1, NULL) );
    check( pthread_join(t2, NULL) );

    PRINTF("Expected value of the counter: 200000.\n");
    PRINTF("Final value of the counter: %d\n", counter);

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
