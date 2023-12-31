#include <sys/time.h>
#include <stdio.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    struct timeval start;
    struct timeval end;

    long diff = 0;
    long final = 0;

    char buf[1024][25] = { 0, };
    ssize_t n;

    for(int i = 0; i < 10; i++) {
        gettimeofday(&start, NULL);

        int fd = open("hello.txt", O_RDONLY);
        if(fd == -1) {
            printf("error\n");
            return fd;
        }

        for(int j = 0; j < 1024; j++) {
            ssize_t n = read(fd, buf[j], 24);
            if(n == -1) {
                printf("error\n");
                return n;
            }
        }

        if(close(fd)) {
            printf("close error\n");
            return -1;
        }

        gettimeofday(&end, NULL);

        diff = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
        final = final + diff;

        printf("[%d] elapsed time: %lus\n", i + 1, diff);
    }

    printf("[avg] elapsed time: %fs\n", (double)(final / 10.0f));

    return 0;
}