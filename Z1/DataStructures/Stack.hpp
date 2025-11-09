#pragma once
#include <iostream>

#include "LinkedList.hpp"

template <typename T>
class Stack {
    private:
        LinkedList<T> list;

    public:
        void push (T value) {
            list.InsertFront (value);
        }
        void pop () {
            if (IsEmpty ()) {
                throw std::runtime_error ("Stek je prazan!");
            }
            list.RemoveFront ();
        }
        T peek () const {
            if (IsEmpty ()) {
                throw std::runtime_error ("Stek je prazan!");
            }
            return list.GetFirstElement ();
        };
        bool IsEmpty () const {
            return list.IsEmpty ();
        }
        int getSize () const {
            return list.GetSize ();
        };
        void clear () {

        };
};