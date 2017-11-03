// ------------------------------------------------------------------ //
// --------------------------- vector.h ----------------------------- //
// ------------------------------------------------------------------ //

#ifndef VECTOR_H
#define VECTOR_H

#include <cstring>
#include <algorithm>

struct vector {
    public:
        vector(unsigned int size) :
            _elements(new unsigned int[size]), _size(size) {
            std::fill(_elements, _elements + _size, 0);
        }

        vector(unsigned int size, unsigned int value) :
            _elements(new unsigned int[size]), _size(size) {
            std::fill(_elements, _elements + _size, value);
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
