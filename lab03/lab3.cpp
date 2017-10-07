// ------------------------------------------------------------------ //
// ----------------------------- Lab3 ------------------------------- //
// ------------------------------------------------------------------ //
/*
 * Main Program(Lab3)
 *
 * Parallel and distributed Computing
 * Lab work #3 "Threads in WinAPI library"
 *
 * Functions:
 * F1: d = MAX(B + C) + MIN(A + B * (MA * ME))
 * F2: MK = MA * (MA * MZ) + TRANS(MB)
 * F3: T = MO * P + (MR * MS) * S
 *
 * Author: Igor Boyarshin, IO-52
 * Date: 23.09.17
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <memory> // smart pointers

#include "Data.h"


struct thread_parameters {
    const Data& data;
    const unsigned int OUTPUT_THRESHOLD;
    pthread_mutex_t& mutex;

    thread_parameters(
            const Data& _data,
            unsigned int outputThreshold,
            pthread_mutex_t& _mutex
            ) : data(_data), OUTPUT_THRESHOLD(outputThreshold), mutex(_mutex) {};
};

// ------------------------------------------------------------------ //

void* thread1_func (void* parameters) {
    nice(0); // Change niceness
    const thread_parameters* p = (thread_parameters*) parameters;
    const Data& data = p->data;
    const unsigned int N = p->data.getN();
    const unsigned int OUTPUT_THRESHOLD = p->OUTPUT_THRESHOLD;
    pthread_mutex_t& mutex = p->mutex;

    pthread_mutex_lock(&mutex);
        std::cout << ":> Starting Thread 1..." << std::endl;
        const vector A = data.fillVectorOnes();
        const vector B = data.fillVectorOnes();
        const vector C = data.fillVectorOnes();
        const matrix MA = data.fillMatrixOnes();
        const matrix ME = data.fillMatrixOnes();
    pthread_mutex_unlock(&mutex);

    sleep(1);
    const unsigned int d = data.func1(A, B, C, MA, ME);

    if (N < OUTPUT_THRESHOLD) {
        pthread_mutex_lock(&mutex);
            std::cout << std::endl;
            std::cout << "Result of Func1: d = " << std::endl;
            std::cout << d << std::endl;
            std::cout << std::endl;
        pthread_mutex_unlock(&mutex);
    }

    std::cout << ":> Finished Thread 1" << std::endl;

    return NULL;
}

void* thread2_func (void* parameters) {
    nice(0); // Change niceness
    const thread_parameters* p = (thread_parameters*) parameters;
    const Data& data = p->data;
    const unsigned int N = p->data.getN();
    const unsigned int OUTPUT_THRESHOLD = p->OUTPUT_THRESHOLD;
    pthread_mutex_t& mutex = p->mutex;

    pthread_mutex_lock(&mutex);
        std::cout << ":> Starting Thread 2..." << std::endl;
        const matrix MA = data.fillMatrixOnes();
        const matrix MB = data.fillMatrixOnes();
        const matrix MZ = data.fillMatrixOnes();
    pthread_mutex_unlock(&mutex);

    sleep(1);
    const matrix& MK = data.func2(MA, MB, MZ);

    if (N < OUTPUT_THRESHOLD) {
        pthread_mutex_lock(&mutex);
            std::cout << std::endl;
            std::cout << "Result of Func2: MK = " << std::endl;
            data.outputMatrix(MK);
            std::cout << std::endl;
        pthread_mutex_unlock(&mutex);
    }

    std::cout << ":> Finished Thread 2" << std::endl;

    return NULL;
}

void* thread3_func (void* parameters) {
    nice(0); // Change niceness
    const thread_parameters* p = (thread_parameters*) parameters;
    const Data& data = p->data;
    const unsigned int N = p->data.getN();
    const unsigned int OUTPUT_THRESHOLD = p->OUTPUT_THRESHOLD;
    pthread_mutex_t& mutex = p->mutex;

    pthread_mutex_lock(&mutex);
        std::cout << ":> Starting Thread 3..." << std::endl;
        const vector P = data.fillVectorOnes();
        const vector S = data.fillVectorOnes();
        const matrix MO = data.fillMatrixOnes();
        const matrix MR = data.fillMatrixOnes();
        const matrix MS = data.fillMatrixOnes();
    pthread_mutex_unlock(&mutex);

    sleep(1);
    const vector& T = data.func3(P, S, MO, MR, MS);

    if (N < OUTPUT_THRESHOLD) {
        pthread_mutex_lock(&mutex);
            std::cout << std::endl;
            std::cout << "Result of Func3: T = " << std::endl;
            data.outputVector(T);
            std::cout << std::endl;
        pthread_mutex_unlock(&mutex);
    }

    std::cout << ":> Finished Thread 3" << std::endl;

    return NULL;
}

// ------------------------------------------------------------------ //

int main() {
    std::cout << ":> Main program started!" << std::endl;
    const unsigned int OUTPUT_THRESHOLD = 7;
    const Data data(3);

    pthread_t thread1_id;
    pthread_t thread2_id;
    pthread_t thread3_id;

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    thread_parameters thread_params(data, OUTPUT_THRESHOLD, mutex);

    pthread_create(&thread1_id, NULL, thread1_func, &thread_params);
    pthread_create(&thread2_id, NULL, thread2_func, &thread_params);
    pthread_create(&thread3_id, NULL, thread3_func, &thread_params);

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);
    pthread_join(thread3_id, NULL);

    return 0;
}
