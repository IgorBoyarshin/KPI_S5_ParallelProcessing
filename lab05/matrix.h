// ------------------------------------------------------------------ //
// --------------------------- matrix.h ----------------------------- //
// ------------------------------------------------------------------ //

#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <cstring>

struct matrix {
    public:
        matrix(unsigned int size) :
            _elements(new unsigned int[size * size]), _size(size) {
            std::fill(_elements, _elements + _size * _size, 0);
        }

        matrix(unsigned int size, unsigned int value) :
            _elements(new unsigned int[size * size]), _size(size) {
            std::fill(_elements, _elements + _size * _size, value);
        }

    private:
        unsigned int* const _elements;

    public:
        const unsigned int _size;

        unsigned int& operator[](unsigned int index) {
            return _elements[index];
        }

        const unsigned int& operator[](unsigned int index) const {
            return _elements[index];
        }
};

#endif
