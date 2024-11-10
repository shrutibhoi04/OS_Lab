#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty, full, mutex;
int buffer[5] = {-1, -1, -1, -1, -1}; // Shared buffer
int in = 0, out = 0; // Buffer indices

void* producer(void* arg) {
    sem_wait(&empty); // Wait for empty space
    sem_wait(&mutex); // Lock critical section

    buffer[in] = rand() % 100; // Produce an item
    printf("Produced: %d | Buffer: ", buffer[in]);
    in = (in + 1) % 5;

    for(int i = 0; i < 5; i++)
        printf("%d ", buffer[i]);
    printf("\n");

    sem_post(&mutex); // Unlock critical section
    sem_post(&full);  // Signal full slot
    return NULL;
}

void* consumer(void* arg) {
    int val;
    do {
        sem_wait(&full); // Wait for full slot
        sem_wait(&mutex); // Lock critical section

        printf("Consumed: %d | Buffer: ", buffer[out]);
        buffer[out] = -1; // Consume item
        out = (out + 1) % 5;

        for(int i = 0; i < 5; i++)
            printf("%d ", buffer[i]);
        printf("\n");

        sem_post(&mutex); // Unlock critical section
        sem_post(&empty); // Signal empty slot
        sem_getvalue(&empty, &val); // Get empty count
    } while(val != 5); // Stop when buffer is empty

    return NULL;
}

int main() {
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t producers[8], consumer_thread;

    for(int i = 0; i < 8; i++) 
        pthread_create(&producers[i], NULL, producer, NULL);
    
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    for(int i = 0; i < 8; i++) 
        pthread_join(producers[i], NULL);
    
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    
    return 0;
}
