#pragma once

#include <string>

#include "..\models\Flight.hpp"
#include "BTreeNode.hpp"
#include "Vector.hpp"

class BTree {
    private:
        BTreeNode* root;
        int t;

        void SplitChild (BTreeNode* parent, int index, BTreeNode* fullChild);
        void InsertNonFull (BTreeNode* node, const Flight& flight);
        void DestroyTree (BTreeNode* node);

        void SearchRange (BTreeNode* node, double low, double high);
        void CollectFlights (BTreeNode* node, Vector<Flight>& flights);
        void FindFlightNumberRecursive (BTreeNode* node, const std::string& flightNumber, Vector<Flight>& results);

        void DeleteRecursive (BTreeNode* node, const std::string& flightNum);
        void DeleteFromLeaf (BTreeNode* node, int idx);
        void DeleteFromNonLeaf (BTreeNode* node, int idx, const std::string& flightNum);
        Flight GetPredecessor (BTreeNode* node, int idx);
        Flight GetSuccessor (BTreeNode* node, int idx);
        void Fill (BTreeNode* node, int idx);
        void BorrowFromPrev (BTreeNode* node, int idx);
        void BorrowFromNext (BTreeNode* node, int idx);
        void Merge (BTreeNode* node, int idx);

        bool ValidateNode (BTreeNode* node, int& errorCount, double& minKey, double& maxKey, int depth);

    public:
        BTree (int minDegree);
        ~BTree ();

        void Insert (const Flight& flight);
        void DeleteFlight (const std::string& flightNum);
        bool IsEmpty () const;

        void SearchRange (double low, double high);
        Vector<Flight> GetAllFlights ();
        Vector<Flight> FindByFlightNumber (const std::string& flightNumber);

        void PrintHierarchical ();
        bool ValidateTree ();
        void PrintStats ();
};