/**
 * This program is based on the work from the Institute of Applied Information Processing and Communications (IAIK)
 * available here: https://github.com/IAIK/flush_flush
 */

#include <stdio.h>
#include <string.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define PROBES_RANGE 1000
#define PROBES 1000000

size_t array[5*1024];
size_t hit_histogram[PROBES_RANGE];
size_t miss_histogram[PROBES_RANGE];

inline int probe(void *adrs) {
    volatile unsigned long time;

    asm __volatile__ (
    "  mfence             \n"
    "  lfence             \n"
    "  rdtsc              \n"
    "  lfence             \n"
    "  movl %%eax, %%esi  \n"
    "  movl (%1), %%eax   \n"
    "  lfence             \n"
    "  rdtsc              \n"
    "  subl %%esi, %%eax  \n"
    "  clflush 0(%1)      \n"
    : "=a" (time)
    : "c" (adrs)
    :  "%esi", "%edx");
    return time;
}

inline int probe_no_flush(void *adrs) {
    volatile unsigned long time;

    asm __volatile__ (
    "  mfence             \n"
    "  lfence             \n"
    "  rdtsc              \n"
    "  lfence             \n"
    "  movl %%eax, %%esi  \n"
    "  movl (%1), %%eax   \n"
    "  lfence             \n"
    "  rdtsc              \n"
    "  subl %%esi, %%eax  \n"
    : "=a" (time)
    : "c" (adrs)
    :  "%esi", "%edx");
    return time;
}

void flush(void *adrs) {
    asm __volatile__ (
    "  clflush 0(%0)\n"
    :
    : "c" (adrs)
    : "eax");
}

void maccess(void *adrs) {
    asm __volatile__ (
    "  mov (%0), %%eax\n"
    :
    : "c" (adrs)
    : "eax");
}

int main(int argc, char **argv) {
    // Set set value of array to a bunch of -1
    memset(array, -1, 5 * 1024 * sizeof(size_t));

    /**
     * First, we access the data from the cache
     */

    // Access the array to load it in the cache
    maccess(array + 2 * 1024);

    for (int i = 0; i < PROBES; ++i) {
        // Probe an address in the middle of the array
        size_t d = probe_no_flush(array + 2 * 1024);
        hit_histogram[MIN(PROBES_RANGE - 1, d)]++;
    }

    /**
     * Then, we access the data from the main memory
     */

    // Clear the CPU cache using clflush
    flush(array + 1024);

    for (int i = 0; i < PROBES; ++i) {
        size_t d = probe(array + 2 * 1024);
        miss_histogram[MIN(PROBES_RANGE - 1, d)]++;
    }

    size_t hit_max = 0;
    size_t hit_max_i = 0;
    size_t miss_min_i = 0;

    printf("Cycles,Hits,Misses\n");

    for (size_t i = 0; i < PROBES_RANGE; ++i) {
        printf("%zu,%zu,%zu\n", i, hit_histogram[i], miss_histogram[i]);

        if (hit_max < hit_histogram[i]) {
            hit_max = hit_histogram[i];
            hit_max_i = i;
        }

        if (miss_histogram[i] > 3 && miss_min_i == 0)
            miss_min_i = i;
    }

    size_t min = -1UL;
    size_t min_i = 0;
    for (int i = hit_max_i; i < miss_min_i; ++i) {
        if (min > (hit_histogram[i] + miss_histogram[i])) {
            min = hit_histogram[i] + miss_histogram[i];
            min_i = i;
        }
    }

    fprintf(stderr, "The lower the threshold, the lower the number of false positives.\n");
    fprintf(stderr, "Suggested cache hit/miss threshold: %zu\n", min_i);

    return 0;
}
