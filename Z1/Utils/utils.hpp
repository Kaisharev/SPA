#pragma once
#include <cstdlib>
void clear_screen ();
template <typename T>
void swap_items (T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}