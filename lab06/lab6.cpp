// ------------------------------------------------------------------ //
// ----------------------------- Lab6 ------------------------------- //
// ------------------------------------------------------------------ //
/*
 * Main Program(Lab6)
 *
 * Parallel and distributed Computing
 * Lab work #6 "Threads in MPI library"
 *
 * Functions:
 * F1: d = MAX(B + C) + MIN(A + B * (MA * ME))
 * F2: MK = MA * (MA * MZ) + TRANS(MB)
 * F3: T = MO * P + (MR * MS) * S
 *
 * Author: Igor Boyarshin, IO-52
 * Date: 02.11.17
 */


#include <stdio.h>
#include <iostream>
#include <mpi.h>

#include "Data.h"


// ------------------------------------------------------------------ //

void thread1_func (const Data& data,
        unsigned int N, unsigned int outputThreshold) {

    std::cout << ":> Starting Thread 1..." << std::endl;
    const vector A = data.fillVectorOnes();
    const vector B = data.fillVectorOnes();
    const vector C = data.fillVectorOnes();
    const matrix MA = data.fillMatrixOnes();
    const matrix ME = data.fillMatrixOnes();

    const unsigned int d = data.func1(A, B, C, MA, ME);

    if (N < outputThreshold) {
        std::cout << std::endl;
        std::cout << "Result of Func1: d = " << std::endl;
        std::cout << d << std::endl;
        std::cout << std::endl;
    }

    std::cout << ":> Finished Thread 1" << std::endl;
}

void thread2_func (const Data& data,
        unsigned int N, unsigned int outputThreshold) {

    std::cout << ":> Starting Thread 2..." << std::endl;
    const matrix MA = data.fillMatrixOnes();
    const matrix MB = data.fillMatrixOnes();
    const matrix MZ = data.fillMatrixOnes();

    const matrix& MK = data.func2(MA, MB, MZ);

    if (N < outputThreshold) {
        std::cout << std::endl;
        std::cout << "Result of Func2: MK = " << std::endl;
        data.outputMatrix(MK);
        std::cout << std::endl;
    }

    std::cout << ":> Finished Thread 2" << std::endl;
}

void thread3_func (const Data& data,
        unsigned int N, unsigned int outputThreshold) {

    std::cout << ":> Starting Thread 3..." << std::endl;
    const vector P = data.fillVectorOnes();
    const vector S = data.fillVectorOnes();
    const matrix MO = data.fillMatrixOnes();
    const matrix MR = data.fillMatrixOnes();
    const matrix MS = data.fillMatrixOnes();

    const vector& T = data.func3(P, S, MO, MR, MS);

    if (N < outputThreshold) {
        std::cout << std::endl;
        std::cout << "Result of Func3: T = " << std::endl;
        data.outputVector(T);
        std::cout << std::endl;
    }

    std::cout << ":> Finished Thread 3" << std::endl;
}

// ------------------------------------------------------------------ //

int main(int argc, char **argv) {
    // std::cout << ":> Main program started!" << std::endl;

    unsigned int N = 3000;
    const unsigned int OUTPUT_THRESHOLD = 7;
    const Data data(N);

    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    switch (rank) {
        case 0:
            thread1_func(data, N, OUTPUT_THRESHOLD);
            break;
        case 1:
            thread2_func(data, N, OUTPUT_THRESHOLD);
            break;
        case 2:
            thread3_func(data, N, OUTPUT_THRESHOLD);
            break;
        case 3:
            thread3_func(data, N, OUTPUT_THRESHOLD);
            break;
        default:
            std::cout << ":> Thread " << rank << " will be doing nothing" << std::endl;
    }

    MPI_Finalize();

    return 0;
}
