#include <sys/time.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    struct timeval start;
    struct timeval end;

    long final = 0;
    long diff = 0;

    struct iovec iov[1024];
    char buf[1024][25] = { 0, };

    for(int i = 0; i < 10; i++) {
        gettimeofday(&start, NULL);
        int fd = open("hello.txt", O_RDONLY);

        if(fd == -1) return -1;

        for(int j = 0; j < 1024; j++) {
            iov[j].iov_base = buf[j];
            iov[j].iov_len = 24;
        }

        ssize_t n = readv(fd, iov, 1024);
        if(n < 0) {
            return -1;
        }

        close(fd);

        gettimeofday(&end, NULL);
        diff = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
        final = final + diff;
        printf("[%d] elapsed time: %lds\n", i, diff);
    }

    printf("[avg] elapsed time: %f\n", (double) (final / 10));

    return 0;
}