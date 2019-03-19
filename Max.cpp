#include <stdio.h>
#include <pthread.h>
#include <time.h>
#define MAX 16
#define MAX_THREAD 4

int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220};
int part = 0;
int max =0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* sum_array(void* arg)
{
    int thread_part = part++;

    for (int i = thread_part * (MAX / MAX_THREAD); i < (thread_part + 1) * (MAX / MAX_THREAD); i++)
        if (a[i] > max)
        {
            pthread_mutex_lock(&mutex);
            if (a[i] > max)
            {
                max = a[i];
            }
            pthread_mutex_unlock(&mutex);
        }
}

int main()
{
    clock_t time;
    time = clock();

    pthread_t threads[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; i++)
        pthread_create(&threads[i], NULL, sum_array, (void*)NULL);

    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL);

    printf("Max is %d ", max);
    pthread_mutex_destroy(&mutex);
    
    time = clock() - time;
    printf("%f", (double)time/CLOCKS_PER_SEC);
    return 0;
}
