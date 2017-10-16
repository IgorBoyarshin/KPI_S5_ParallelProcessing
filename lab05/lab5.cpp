// ------------------------------------------------------------------ //
// ----------------------------- Lab5 ------------------------------- //
// ------------------------------------------------------------------ //
/*
 * Main Program(Lab5)
 *
 * Parallel and distributed Computing
 * Lab work #3 "Threads in OpenMP library"
 *
 * Functions:
 * F1: d = MAX(B + C) + MIN(A + B * (MA * ME))
 * F2: MK = MA * (MA * MZ) + TRANS(MB)
 * F3: T = MO * P + (MR * MS) * S
 *
 * Author: Igor Boyarshin, IO-52
 * Date: 15.10.17
 */

#include <omp.h>

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <memory> // smart pointers

#include "Data.h"


// ------------------------------------------------------------------ //

void thread1_func (const Data& data,
        unsigned int N, unsigned int outputThreshold) {
    // #pragma omp critical(data_input)
    // {
        int id = omp_get_thread_num();
        std::cout << id << std::endl;
        std::cout << ":> Starting Thread 1..." << std::endl;
        const vector A = data.fillVectorOnes();
        const vector B = data.fillVectorOnes();
        const vector C = data.fillVectorOnes();
        const matrix MA = data.fillMatrixOnes();
        const matrix ME = data.fillMatrixOnes();
    // }

    const unsigned int d = data.func1(A, B, C, MA, ME);

    if (N < outputThreshold) {
        #pragma omp critical(data_output)
        {
            std::cout << std::endl;
            std::cout << "Result of Func1: d = " << std::endl;
            std::cout << d << std::endl;
            std::cout << std::endl;
        }
    }

    std::cout << ":> Finished Thread 1" << std::endl;
}

void thread2_func (const Data& data,
        unsigned int N, unsigned int outputThreshold) {
    // #pragma omp critical(data_input)
    // {
        int id = omp_get_thread_num();
        std::cout << id << std::endl;
        std::cout << ":> Starting Thread 2..." << std::endl;
        const matrix MA = data.fillMatrixOnes();
        const matrix MB = data.fillMatrixOnes();
        const matrix MZ = data.fillMatrixOnes();
    // }

    const matrix& MK = data.func2(MA, MB, MZ);

    if (N < outputThreshold) {
        #pragma omp critical(data_output)
        {
            std::cout << std::endl;
            std::cout << "Result of Func2: MK = " << std::endl;
            data.outputMatrix(MK);
            std::cout << std::endl;
        }
    }

    std::cout << ":> Finished Thread 2" << std::endl;
}

void thread3_func (const Data& data,
        unsigned int N, unsigned int outputThreshold) {
    // #pragma omp critical(data_input)
    // {
        std::cout << ":> Starting Thread 3..." << std::endl;
        const vector P = data.fillVectorOnes();
        const vector S = data.fillVectorOnes();
        const matrix MO = data.fillMatrixOnes();
        const matrix MR = data.fillMatrixOnes();
        const matrix MS = data.fillMatrixOnes();
    // }

    const vector& T = data.func3(P, S, MO, MR, MS);

    if (N < outputThreshold) {
        #pragma omp critical(data_output)
        {
            std::cout << std::endl;
            std::cout << "Result of Func3: T = " << std::endl;
            data.outputVector(T);
            std::cout << std::endl;
        }
    }

    std::cout << ":> Finished Thread 3" << std::endl;
}

// ------------------------------------------------------------------ //

int main() {
    std::cout << ":> Main program started!" << std::endl;

    unsigned int N;
    std::cout << "Input N: ";
    std::cin >> N;
    const unsigned int OUTPUT_THRESHOLD = 7;
    const Data data(N);

    omp_set_num_threads(3);

    #pragma omp parallel sections
    {
        #pragma omp section
        thread1_func(data, N, OUTPUT_THRESHOLD);

        #pragma omp section
        thread2_func(data, N, OUTPUT_THRESHOLD);

        #pragma omp section
        thread3_func(data, N, OUTPUT_THRESHOLD);
    }

    return 0;
}
