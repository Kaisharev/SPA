#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class PriorityQueue {
    private:
        T* heap;
        int capacity;
        int size;

        int Parent (int i) const {
            return (i - 1) / 2;
        }
        int LeftChild (int i) const {
            return 2 * i + 1;
        }
        int RightChild (int i) const {
            return 2 * i + 2;
        }

        void Resize () {
            int newCapacity = capacity * 2;
            T* newHeap = new T[newCapacity];

            for (int i = 0; i < size; i++) {
                newHeap[i] = heap[i];
            }

            delete[] heap;
            heap = newHeap;
            capacity = newCapacity;
        }

        void HeapifyUp (int index) {
            while (index > 0 && *heap[Parent (index)] < *heap[index]) {
                T temp = heap[index];
                heap[index] = heap[Parent (index)];
                heap[Parent (index)] = temp;

                index = Parent (index);
            }
        }

        void HeapifyDown (int index) {
            int maxIndex = index;
            int left = LeftChild (index);
            int right = RightChild (index);

            // Pronađi najveći element
            if (left < size && *heap[left] > *heap[maxIndex]) {
                maxIndex = left;
            }

            if (right < size && *heap[right] > *heap[maxIndex]) {
                maxIndex = right;
            }

            if (index != maxIndex) {
                T temp = heap[index];
                heap[index] = heap[maxIndex];
                heap[maxIndex] = temp;

                HeapifyDown (maxIndex);
            }
        }

    public:
        PriorityQueue (int initialCapacity = 10) : capacity (initialCapacity), size (0) {
            heap = new T[capacity];
        }

        ~PriorityQueue () {
            delete[] heap;
        }

        PriorityQueue (const PriorityQueue& other) : capacity (other.capacity), size (other.size) {
            heap = new T[capacity];
            for (int i = 0; i < size; i++) {
                heap[i] = other.heap[i];
            }
        }

        PriorityQueue& operator= (const PriorityQueue& other) {
            if (this != &other) {
                delete[] heap;

                capacity = other.capacity;
                size = other.size;
                heap = new T[capacity];

                for (int i = 0; i < size; i++) {
                    heap[i] = other.heap[i];
                }
            }
            return *this;
        }

        void Insert (T value) {
            if (size == capacity) {
                Resize ();
            }

            heap[size] = value;
            HeapifyUp (size);
            size++;
        }

        T ExtractMax () {
            if (IsEmpty ()) {
                throw std::runtime_error ("Prioritetni red je prazan!");
            }

            T maxValue = heap[0];

            size--;
            heap[0] = heap[size];

            if (size > 0) {
                HeapifyDown (0);
            }

            return maxValue;
        }

        T PeekMax () const {
            if (IsEmpty ()) {
                throw std::runtime_error ("Prioritetni red je prazan!");
            }

            return heap[0];
        }

        bool IsEmpty () const {
            return size == 0;
        }

        int GetSize () const {
            return size;
        }

        void Clear () {
            size = 0;
        }
};