// ------------------------------------------------------------------ //
// ---------------------------- Data.h ------------------------------ //
// ------------------------------------------------------------------ //

#ifndef DATA_H
#define DATA_H

#include <iostream>

#include "vector.h"
#include "matrix.h"


class Data {
    public:
        Data(unsigned int N) : _N(N) {}

        unsigned int getN() const;

        vector inputVector() const;
        void outputVector(const vector& v) const;
        matrix inputMatrix() const;
        void outputMatrix(const matrix& m) const;

        vector fillVectorOnes() const;
        matrix fillMatrixOnes() const;

        unsigned int func1(
                const vector& A, const vector& B, const vector& C,
                const matrix& MA, const matrix& ME) const;

        matrix func2(
                const matrix& MA, const matrix& MB, const matrix& MZ
                ) const;

        vector func3(
                const vector& P, const vector& S,
                const matrix& MO, const matrix& MR, const matrix& MS
                ) const;

    private:
        vector addVectors(const vector& v1, const vector& v2) const;
        matrix addMatrices(const matrix& m1, const matrix& m2) const;
        vector mulVectorMatrix(const vector& v, const matrix& m) const;
        vector mulMatrixVector(const matrix& m, const vector& v) const;

        matrix mulMatrices(const matrix& m1, const matrix& m2) const;
        matrix transposeMatrix(const matrix& m) const;

        unsigned int findMin(const vector& v) const;
        unsigned int findMax(const vector& v) const;
        unsigned int findMinOrMax(const vector& v, bool findMinElement) const;


    private:
        const unsigned int _N;
};

#endif
