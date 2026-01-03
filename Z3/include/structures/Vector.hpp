#pragma once
#include <stdexcept>
template <typename T>

class Vector {
    private:
        T* vector;
        int size;
        int capacity;

        void resize () {
            this->capacity *= 2;
            T* temp = new T[capacity];
            for (int i = 0; i < this->size; i++) {
                temp[i] = this->vector[i];
            }
            delete[] this->vector;
            this->vector = temp;
        }

    public:
        Vector () {
            size = 0;
            capacity = 1;
            vector = new T[1];
        }
        ~Vector () {
            delete[] vector;
        }

        Vector (std::initializer_list<T> list) {
            size = static_cast<int> (list.size ());
            capacity = size > 0 ? size : 1;
            vector = new T[capacity];
            int i = 0;
            for (const T& v : list) {
                vector[i++] = v;
            }
        }

        Vector (const Vector<T>& other) {
            delete[] this->vector;
            size = other.size;
            capacity = other.capacity;
            this->vector = new T[size];
            for (int i = 0; i < size; i++) {
                this->vector[i] = other.vector[i];
            }
        }
        T& operator[] (int index) {
            return vector[index];
        }
        const T& operator[] (int index) const {
            return vector[index];
        }

        Vector<T>& operator= (const Vector<T>& other) {
            delete[] this->vector;
            if (this == &other) return *this;
            size = other.size;
            capacity = other.capacity;
            this->vector = new T[size];
            for (int i = 0; i < size; i++) {
                this->vector[i] = other.vector[i];
            }
            return *this;
        }

        void PushBack (const T& element) {
            if (size >= capacity) resize ();
            vector[size++] = element;
        }
        void Insert (int index, const T& element) {
            if (index < 0 || index > size) throw std::out_of_range ("Insert index out of range");
            if (size >= capacity) resize ();

            for (int i = size; i > index; --i) {
                vector[i] = vector[i - 1];
            }
            vector[index] = element;
            ++size;
        }

        void PopBack () {
            if (size > 0) size--;
        }
        const T& At (int index) const {
            return vector[index];
        }

        T& Front () {
            return vector[0];
        }
        const T& Front () const {
            return vector[0];
        }

        T& Back () {
            if (size == 0) throw std::out_of_range ("Vektor je prazan");

            return vector[size - 1];
        }
        const T& Back () const {
            if (size == 0) throw std::out_of_range ("Vektor je prazan");

            return vector[size - 1];
        }

        int GetSize () const {
            return this->size;
        }
        int GetCapacity () const {
            return this->capacity;
        }

        bool IsEmpty () const {
            if (size == 0) return true;
            return false;
        }
        T* begin () {
            return vector;
        }
        T* end () {
            return vector + size;
        }
        const T* begin () const {
            return vector;
        }
        const T* end () const {
            return vector + size;
        }

        void Erase (int index) {
            if (index < 0 || index >= size) throw std::out_of_range ("erase index out of range");

            for (int i = index; i < size - 1; ++i) {
                vector[i] = vector[i + 1];
            }
            --size;
        }
};
