#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t readLock, writeLock;  // Semaphores for readers and writers
int readerCount = 0;        // Count of active readers

void* reader(void* arg) {
    sem_wait(&readLock);    // Lock for reader count
    readerCount++;
    if (readerCount == 1)
        sem_wait(&writeLock);  // First reader locks the writer
    sem_post(&readLock);    // Release lock for reader count

    // Reading section
    printf("Reader is reading\n");

    sem_wait(&readLock);    // Lock for reader count
    readerCount--;
    if (readerCount == 0)
        sem_post(&writeLock);  // Last reader unlocks the writer
    sem_post(&readLock);    // Release lock for reader count

    return NULL;
}

void* writer(void* arg) {
    sem_wait(&writeLock);   // Only one writer can access at a time

    // Writing section
    printf("Writer is writing\n");

    sem_post(&writeLock);   // Release lock for writers
    return NULL;
}

int main() {
    pthread_t readers[3], writers[3];
    sem_init(&readLock, 0, 1);  // Initialize semaphore for readers
    sem_init(&writeLock, 0, 1); // Initialize semaphore for writers

    // Create reader and writer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&readLock);
    sem_destroy(&writeLock);

    return 0;
}
