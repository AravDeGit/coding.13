/*
1. The timer is accurate to a microsecond. The operation has to take more time than the timer needs to run for it to be accurate.
2.
5.We can ensure this by setting the Optimisation flag to zero while running the compiler.
6.To make sure that the thread is not transferred to seperate cores, we can pin the thread to a certain core. This way the thread
is always found in the same core. This is important when measuring time because if the thread is transferred within CPUs, there
might be TLB misses in each CPU or the TLB might have to be loaded into memory which beats the whole point of a cache.
7. If the array has not been intialized, it might take much longer as it might demand new pages or rellocations of memory to fit 
into the TLB. To avoid this we can intialize the page before recording time. This way whatever happens while allocating the memory
would not be accounted for.
*/
#include <stdio.h>
#include <Windows.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_pages> <number_of_trials>\n", argv[0]);
        return 1;
    }

    int number_of_pages = atoi(argv[1]);
    int number_of_trials = atoi(argv[2]);
    int page_size = 4096;  
    int *array = malloc(number_of_pages * page_size);  

    if (!array) {
        perror("Failed to allocate memory");
        return 1;
    }

    struct timeval start, end;
    double total_time = 0.0;

    for (int trial = 0; trial < number_of_trials; trial++) {
        
         gettimeofday(&start, NULL);
        // Access each page once
        for (int i = 0; i < number_of_pages * (page_size / sizeof(int)); i += page_size / sizeof(int)) {
            array[i] += 1;  
        }
        gettimeofday(&end, NULL);
        double trial_time = (end.tv_sec - start.tv_sec); // microseconds
        total_time += trial_time;
    }

    double avg_time_per_access = total_time / (number_of_trials * number_of_pages);

    printf("Pages: %d, Trials: %d, Avg time per page access: %.3f microseconds\n", number_of_pages, number_of_trials, avg_time_per_access);

    free(array);
    return 0;
}