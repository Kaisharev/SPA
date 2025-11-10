#pragma once
#include <csignal>
#include <cstdlib>
#include <iostream>

#include "../Diary/Diary.hpp"
void clear_screen ();
template <typename T>
void swap_items (T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
void signalHandler (int signum);
extern const int MAX_ENTRIES;