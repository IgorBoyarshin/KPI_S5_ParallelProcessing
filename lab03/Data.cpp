// ------------------------------------------------------------------ //
// --------------------------- Data.cpp ----------------------------- //
// ------------------------------------------------------------------ //

#include "Data.h"

// Data::Data(unsigned int N) : _N(N) {}

unsigned int Data::getN() const {
    return _N;
}

vector Data::inputVector() const {
    vector v(_N);

    std::cout << "Input Vector(space-separated):" << std::endl;
    for (unsigned int i = 0; i < _N; i++) {
        std::cin >> v[i];
    }

    return v;
}

void Data::outputVector(const vector& v) const {
    for (unsigned int i = 0; i < _N; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

matrix Data::inputMatrix() const {
    std::cout << "Input Matrix(space-separated, multiple lines):" << std::endl;

    matrix m(_N);
    for (unsigned int row = 0; row < _N; row++) {
        for (unsigned int column = 0; column < _N; column++) {
            std::cin >> m[row * _N + column];
        }
    }

    return m;
}

void Data::outputMatrix(const matrix& m) const {
    for (unsigned int row = 0; row < _N; row++) {
        for (unsigned int column = 0; column < _N; column++) {
            std::cout << m[row * _N + column] << " ";
        }
        std::cout << std::endl;
    }
}

vector Data::fillVectorOnes() const {
    return vector(_N, 1);
}

matrix Data::fillMatrixOnes() const {
    return matrix(_N, 1);
}

// ------------------------------------------------------------------ //

unsigned int Data::func1 (
        const vector& A, const vector& B, const vector& C,
        const matrix& MA, const matrix& ME) const {
    return (
        findMax(
            addVectors(B, C)
        )
        +
        findMin(
            addVectors(
                A,
                mulVectorMatrix(
                    B, mulMatrices(MA, ME)
                )
            )
        )
    );
}

matrix Data::func2(
        const matrix& MA, const matrix& MB, const matrix& MZ
        ) const {
    return (
        addMatrices(
            mulMatrices(
                MA,
                mulMatrices(MA, MZ)
            ),
            transposeMatrix(MB)
        )
    );
}

vector Data::func3(
        const vector& P, const vector& S,
        const matrix& MO, const matrix& MR, const matrix& MS
        ) const {
    return (
        addVectors(
            mulMatrixVector(MO, P),
            mulMatrixVector(
                mulMatrices(MR, MS),
                S
            )
        )
    );
}

// ------------------------------------------------------------------ //

vector Data::addVectors(const vector& v1, const vector& v2) const {
    vector v(_N);
    for (unsigned int i = 0; i < _N; i++) {
        v[i] = v1[i] + v2[i];
    }

    return v;
}

matrix Data::addMatrices(const matrix& m1, const matrix& m2) const {
    matrix m(_N);
    for (unsigned int row = 0; row < _N; row++) {
        for (unsigned int column = 0; column < _N; column++) {
            const unsigned int index = row * _N + column;
            m[index] = m1[index] + m2[index];
        }
    }

    return m;
}

vector Data::mulVectorMatrix(const vector& v, const matrix& m) const {
    vector result(_N);
    for (unsigned int column = 0; column < _N; column++) {
        result[column] = 0;
        for (unsigned int row = 0; row < _N; row++) {
            result[column] += v[row] * m[row * _N + column];
        }
    }

    return result;
}

vector Data::mulMatrixVector(const matrix& m, const vector& v) const {
    vector result(_N);
    for (unsigned int row = 0; row < _N; row++) {
        result[row] = 0;
        for (unsigned int column = 0; column < _N; column++) {
            result[row] += m[row * _N + column] * v[column];
        }
    }

    return result;
}

matrix Data::mulMatrices(const matrix& m1, const matrix& m2) const {
    matrix m(_N);
    for (unsigned int row = 0; row < _N; row++) {
        for (unsigned int column = 0; column < _N; column++) {
            m[row * _N + column] = 0;
            for (unsigned int i = 0; i < _N; i++) {
                m[row * _N + column] += m1[row * _N + i] * m2[i * _N + column];
            }
        }
    }

    return m;
}

matrix Data::transposeMatrix(const matrix& m) const {
    matrix result(_N);
    for (unsigned int row = 0; row < _N; row++) {
        for (unsigned int column = 0; column < _N; column++) {
            result[column * _N + row] = m[row * _N + column];
        }
    }

    return result;
}

unsigned int Data::findMin(const vector& v) const {
    return findMinOrMax(v, true);
}

unsigned int Data::findMax(const vector& v) const {
    return findMinOrMax(v, false);
}

unsigned int Data::findMinOrMax(const vector& v, bool findMinElement) const {
    unsigned int current = v[0];
    for (unsigned int i = 1; i < _N; i++) {
        const unsigned int element = v[i];
        if (findMinElement ?
                (element < current) : (element > current)) {
            current = element;
        }
    }

    return current;
}
