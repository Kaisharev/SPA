#pragma once
#include <iostream>

#include "LinkedList.hpp"

template <typename T>
class Stack {
    private:
        LinkedList<T> list;

    public:
        void Push (T value) {
            list.InsertFront (value);
        }
        void Pop () {
            if (IsEmpty ()) {
                throw std::runtime_error ("Stek je prazan!");
            }
            list.RemoveFront ();
        }
        T Peek () const {
            if (IsEmpty ()) {
                throw std::runtime_error ("Stek je prazan!");
            }
            return list.GetFirstElement ();
        };
        bool IsEmpty () const {
            return list.IsEmpty ();
        }
        int GetSize () const {
            return list.GetSize ();
        };
        void clear () {
            while (!IsEmpty ()) {
                Pop ();
            }
        };
};