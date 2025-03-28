#include <iostream>
#include <cstring>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

struct dataTable {
    int table [2];
};

int main() {
    const char* shm = "/shared memory";
    const char* semaphore = "/semaphore1";
    int shm_fd = shm_open(shm, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    ftruncate(shm_fd, sizeof(dataTable));
    dataTable *sharedData = (dataTable*)mmap(NULL, sizeof(dataTable), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (sharedData == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }


    sem_t *sem = sem_open(semaphore, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 2; ++i) {
        if (sem_wait(sem) == -1) {
            perror("sem_wait");
            exit(EXIT_FAILURE);
        }

        std::cout << "Consumer is consuming data: " << sharedData->table[i] << std::endl;
        sleep(1);

        if (sem_post(sem) == -1) {
            perror("sem_post");
            exit(EXIT_FAILURE);
        }
    }
    if (sem_close(sem) == -1) {
        perror("sem_close");
        exit(EXIT_FAILURE);
    }

    munmap(sharedData, sizeof(dataTable));
    close(shm_fd);
    return 0;
}