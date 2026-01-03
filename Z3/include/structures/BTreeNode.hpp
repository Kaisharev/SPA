#pragma once
#include "..\models\Flight.hpp"
#include "Vector.hpp"
class BTreeNode {
    public:
        Vector<Flight> keys;
        Vector<BTreeNode*> children;
        bool leaf;
        int t;  // Minimalni stepen

        BTreeNode (int _t, bool _leaf) : t (_t), leaf (_leaf) {}

        void printNode () {
            std::cout << "(";
            for (int i = 0; i < keys.GetSize (); i++) {
                std::cout << "[" << keys[i].GetDuration () << "]";
            }
            std::cout << ")";
        }
};