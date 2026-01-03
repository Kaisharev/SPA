#include "../../include/structures/BTree.hpp"

#include <iomanip>
#include <iostream>
#include <queue>

BTree::BTree (int minDegree) : root (nullptr), t (minDegree) {
    if (t < 3) {
        std::cerr << "Upozorenje: t mora biti >= 3. Postavljam t=3.\n";
        t = 3;
    }
}

BTree::~BTree () {
    if (root != nullptr) {
        DestroyTree (root);
    }
}

void BTree::DestroyTree (BTreeNode* node) {
    if (node == nullptr) return;

    if (!node->leaf) {
        for (int i = 0; i < node->children.GetSize (); i++) {
            DestroyTree (node->children[i]);
        }
    }

    delete node;
}

void BTree::Insert (const Flight& flight) {
    if (root == nullptr) {
        root = new BTreeNode (t, true);
        root->keys.PushBack (flight);
        return;
    }

    if (root->keys.GetSize () == (2 * t - 1)) {
        BTreeNode* newRoot = new BTreeNode (t, false);
        newRoot->children.PushBack (root);
        SplitChild (newRoot, 0, root);
        root = newRoot;
    }

    InsertNonFull (root, flight);
}

void BTree::SplitChild (BTreeNode* parent, int index, BTreeNode* fullChild) {
    int maxKeys = 2 * t - 1;

    if (fullChild->keys.GetSize () != maxKeys) {
        std::cerr << "Split pozvan na čvoru koji nije pun! size=" << fullChild->keys.GetSize () << " (očekivano " << maxKeys << ")\n";
    }

    BTreeNode* newNode = new BTreeNode (t, fullChild->leaf);

    for (int j = 0; j < t - 1; j++) {
        newNode->keys.PushBack (fullChild->keys[t + j]);
    }

    if (!fullChild->leaf) {
        for (int j = 0; j < t; j++) {
            newNode->children.PushBack (fullChild->children[t + j]);
        }
    }

    Flight midKey = fullChild->keys[t - 1];

    while (fullChild->keys.GetSize () > t - 1) {
        fullChild->keys.PopBack ();
    }

    if (!fullChild->leaf) {
        while (fullChild->children.GetSize () > t) {
            fullChild->children.PopBack ();
        }
    }

    parent->children.Insert (index + 1, newNode);
    parent->keys.Insert (index, midKey);
}

void BTree::InsertNonFull (BTreeNode* node, const Flight& flight) {
    if (node->keys.GetSize () >= 2 * t - 1) {
        std::cerr << "GREŠKA: InsertNonFull pozvan na punom čvoru! size=" << node->keys.GetSize () << "\n";
        return;
    }

    if (node->leaf) {
        int pos = 0;
        while (pos < node->keys.GetSize () && flight.GetDuration () > node->keys[pos].GetDuration ()) {
            pos++;
        }
        node->keys.Insert (pos, flight);
    } else {
        int idx = node->keys.GetSize () - 1;
        while (idx >= 0 && flight.GetDuration () < node->keys[idx].GetDuration ()) {
            idx--;
        }
        idx++;

        if (node->children[idx]->keys.GetSize () == (2 * t - 1)) {
            SplitChild (node, idx, node->children[idx]);

            if (flight.GetDuration () > node->keys[idx].GetDuration ()) {
                idx++;
            }
        }

        InsertNonFull (node->children[idx], flight);
    }
}

void BTree::DeleteFlight (const std::string& flightNum) {
    if (root == nullptr) {
        std::cout << "Stablo je prazno.\n";
        return;
    }

    DeleteRecursive (root, flightNum);

    if (root->keys.GetSize () == 0) {
        BTreeNode* oldRoot = root;

        if (root->leaf) {
            root = nullptr;
        } else {
            if (root->children.GetSize () > 0) {
                root = root->children[0];
            } else {
                std::cerr << "KRITIČNA GREŠKA: Root nije list ali nema djece!\n";
                root = nullptr;
            }
        }

        delete oldRoot;
    }

    std::cout << "Let " << flightNum << " obrisan.\n";
}

void BTree::DeleteRecursive (BTreeNode* node, const std::string& flightNum) {
    if (!node) return;

    int i = 0;

    for (i = 0; i < node->keys.GetSize (); i++) {
        if (node->keys[i].GetFlightNumber () == flightNum) {
            if (node->leaf) {
                DeleteFromLeaf (node, i);
            } else {
                DeleteFromNonLeaf (node, i, flightNum);
            }
            return;
        }
    }

    if (!node->leaf) {
        for (int j = 0; j < node->children.GetSize (); j++) {
            if (node->children[j]->keys.GetSize () < t) {
                Fill (node, j);
                for (int k = 0; k < node->keys.GetSize (); k++) {
                    if (node->keys[k].GetFlightNumber () == flightNum) {
                        if (node->leaf) {
                            DeleteFromLeaf (node, k);
                        } else {
                            DeleteFromNonLeaf (node, k, flightNum);
                        }
                        return;
                    }
                }
            }

            if (j < node->children.GetSize ()) {
                DeleteRecursive (node->children[j], flightNum);
            }
        }
    }
}

void BTree::DeleteFromLeaf (BTreeNode* node, int idx) {
    node->keys.Erase (idx);
}

void BTree::DeleteFromNonLeaf (BTreeNode* node, int idx, const std::string& flightNum) {
    Flight key = node->keys[idx];

    if (node->children[idx]->keys.GetSize () >= t) {
        Flight pred = GetPredecessor (node, idx);
        node->keys[idx] = pred;
        DeleteRecursive (node->children[idx], pred.GetFlightNumber ());
    } else if (node->children[idx + 1]->keys.GetSize () >= t) {
        Flight succ = GetSuccessor (node, idx);
        node->keys[idx] = succ;
        DeleteRecursive (node->children[idx + 1], succ.GetFlightNumber ());
    } else {
        Merge (node, idx);
        DeleteRecursive (node->children[idx], flightNum);
    }
}

Flight BTree::GetPredecessor (BTreeNode* node, int idx) {
    BTreeNode* curr = node->children[idx];
    while (!curr->leaf) {
        curr = curr->children[curr->children.GetSize () - 1];
    }
    return curr->keys[curr->keys.GetSize () - 1];
}

Flight BTree::GetSuccessor (BTreeNode* node, int idx) {
    BTreeNode* curr = node->children[idx + 1];
    while (!curr->leaf) {
        curr = curr->children[0];
    }
    return curr->keys[0];
}

void BTree::Fill (BTreeNode* node, int idx) {
    if (idx != 0 && node->children[idx - 1]->keys.GetSize () >= t) {
        BorrowFromPrev (node, idx);
    } else if (idx != node->children.GetSize () - 1 && node->children[idx + 1]->keys.GetSize () >= t) {
        BorrowFromNext (node, idx);
    } else {
        if (idx != node->children.GetSize () - 1) {
            Merge (node, idx);
        } else {
            Merge (node, idx - 1);
        }
    }
}

void BTree::BorrowFromPrev (BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx - 1];

    for (int i = child->keys.GetSize () - 1; i >= 0; i--) {
        child->keys.Insert (i + 1, child->keys[i]);
    }
    child->keys[0] = node->keys[idx - 1];

    if (!child->leaf) {
        for (int i = child->children.GetSize () - 1; i >= 0; i--) {
            child->children.Insert (i + 1, child->children[i]);
        }
        child->children[0] = sibling->children[sibling->children.GetSize () - 1];
        sibling->children.PopBack ();
    }

    node->keys[idx - 1] = sibling->keys[sibling->keys.GetSize () - 1];
    sibling->keys.PopBack ();
}

void BTree::BorrowFromNext (BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx + 1];

    child->keys.PushBack (node->keys[idx]);

    if (!child->leaf) {
        child->children.PushBack (sibling->children[0]);
        sibling->children.Erase (0);
    }

    node->keys[idx] = sibling->keys[0];
    sibling->keys.Erase (0);
}

void BTree::Merge (BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx + 1];

    child->keys.PushBack (node->keys[idx]);

    for (int i = 0; i < sibling->keys.GetSize (); i++) {
        child->keys.PushBack (sibling->keys[i]);
    }

    if (!child->leaf) {
        for (int i = 0; i < sibling->children.GetSize (); i++) {
            child->children.PushBack (sibling->children[i]);
        }
    }

    node->keys.Erase (idx);

    node->children.Erase (idx + 1);

    delete sibling;
}

void BTree::SearchRange (double low, double high) {
    if (root == nullptr) {
        std::cout << "Stablo je prazno.\n";
        return;
    }

    std::cout << "\n=== Letovi u opsegu [" << low << ", " << high << "] ===\n";
    SearchRange (root, low, high);
    std::cout << "==========================================\n\n";
}

void BTree::SearchRange (BTreeNode* node, double low, double high) {
    if (!node) return;

    int i = 0;

    for (i = 0; i < node->keys.GetSize (); i++) {
        double d = node->keys[i].GetDuration ();

        if (!node->leaf && node->children.GetSize () > i && d >= low) {
            SearchRange (node->children[i], low, high);
        }

        if (d >= low && d <= high) {
            node->keys[i].PrintFlight ();
        }

        if (d > high) {
            return;
        }
    }

    if (!node->leaf && node->children.GetSize () > i) {
        SearchRange (node->children[i], low, high);
    }
}

Vector<Flight> BTree::GetAllFlights () {
    Vector<Flight> flights;
    if (root != nullptr) {
        CollectFlights (root, flights);
    }
    return flights;
}

void BTree::CollectFlights (BTreeNode* node, Vector<Flight>& flights) {
    if (!node) return;

    int i;
    for (i = 0; i < node->keys.GetSize (); i++) {
        if (!node->leaf && node->children.GetSize () > i) {
            CollectFlights (node->children[i], flights);
        }
        flights.PushBack (node->keys[i]);
    }

    if (!node->leaf && node->children.GetSize () > i) {
        CollectFlights (node->children[i], flights);
    }
}

Vector<Flight> BTree::FindByFlightNumber (const std::string& flightNumber) {
    Vector<Flight> results;
    if (root != nullptr) {
        FindFlightNumberRecursive (root, flightNumber, results);
    }
    return results;
}

void BTree::FindFlightNumberRecursive (BTreeNode* node, const std::string& flightNumber, Vector<Flight>& results) {
    if (!node) return;

    int i;
    for (i = 0; i < node->keys.GetSize (); i++) {
        if (!node->leaf && node->children.GetSize () > i) {
            FindFlightNumberRecursive (node->children[i], flightNumber, results);
        }
        if (node->keys[i].GetFlightNumber () == flightNumber) {
            results.PushBack (node->keys[i]);
        }
    }

    if (!node->leaf && node->children.GetSize () > i) {
        FindFlightNumberRecursive (node->children[i], flightNumber, results);
    }
}

bool BTree::IsEmpty () const {
    return root == nullptr;
}

bool BTree::ValidateTree () {
    if (!root) {
        std::cout << "Stablo je prazno (validno).\n";
        return true;
    }

    int errorCount = 0;
    double minKey = -1e9;
    double maxKey = 1e9;

    bool valid = ValidateNode (root, errorCount, minKey, maxKey, 0);

    if (valid && errorCount == 0) {
        std::cout << "Validacija: Stablo je pravilno!\n";
        return true;
    } else {
        std::cout << "Validacija: Pronađeno " << errorCount << " greška/grešaka.\n";
        return false;
    }
}

bool BTree::ValidateNode (BTreeNode* node, int& errorCount, double& minKey, double& maxKey, int depth) {
    if (!node) return true;

    bool valid = true;
    int maxKeys = 2 * t - 1;
    int minKeys = (node == root) ? 1 : (t - 1);

    if (node->keys.GetSize () > maxKeys) {
        std::cerr << "[Nivo " << depth << "] Čvor ima " << node->keys.GetSize () << " ključeva (max=" << maxKeys << ")\n";
        errorCount++;
        valid = false;
    }

    if (node->keys.GetSize () < minKeys) {
        std::cerr << "[Nivo " << depth << "] Čvor ima " << node->keys.GetSize () << " ključeva (minimum=" << minKeys << ")\n";
        errorCount++;
        valid = false;
    }

    for (int i = 1; i < node->keys.GetSize (); i++) {
        if (node->keys[i].GetDuration () < node->keys[i - 1].GetDuration ()) {
            std::cerr << "[Nivo " << depth << "] Ključevi nisu sortirani!\n";
            errorCount++;
            valid = false;
            break;
        }
    }

    if (!node->leaf) {
        if (node->children.GetSize () != node->keys.GetSize () + 1) {
            std::cerr << "[Nivo " << depth << "] Čvor ima " << node->keys.GetSize () << " ključeva ali ima "
                      << node->children.GetSize () << " djece "
                      << "(treba imati" << (node->keys.GetSize () + 1) << ")\n";
            errorCount++;
            valid = false;
        }

        for (int i = 0; i < node->children.GetSize (); i++) {
            double childMin = (i > 0) ? node->keys[i - 1].GetDuration () : minKey;
            double childMax = (i < node->keys.GetSize ()) ? node->keys[i].GetDuration () : maxKey;

            if (!ValidateNode (node->children[i], errorCount, childMin, childMax, depth + 1)) {
                valid = false;
            }
        }
    }

    return valid;
}

void BTree::PrintHierarchical () {
    if (!root) {
        std::cout << "B-stablo je prazno.\n";
        return;
    }

    std::cout << "\n=== Hijerarhijski prikaz B-stabla ===\n";

    std::queue<BTreeNode*> q;
    std::queue<int> levelQueue;
    q.push (root);
    levelQueue.push (0);

    Vector<Vector<BTreeNode*>> levels;

    while (!q.empty ()) {
        BTreeNode* current = q.front ();
        int lvl = levelQueue.front ();
        q.pop ();
        levelQueue.pop ();

        while (levels.GetSize () <= lvl) {
            levels.PushBack (Vector<BTreeNode*> ());
        }
        levels[lvl].PushBack (current);

        if (!current->leaf) {
            for (int i = 0; i < current->children.GetSize (); i++) {
                q.push (current->children[i]);
                levelQueue.push (lvl + 1);
            }
        }
    }

    for (int i = 0; i < levels.GetSize (); i++) {
        std::cout << "Nivo " << i << ": ";

        for (int j = 0; j < levels[i].GetSize (); j++) {
            BTreeNode* n = levels[i][j];
            std::cout << "[";

            for (int k = 0; k < n->keys.GetSize (); k++) {
                std::cout << static_cast<int> (n->keys[k].GetDuration ());
                if (k < n->keys.GetSize () - 1) std::cout << ",";
            }

            std::cout << "]";
            if (j < levels[i].GetSize () - 1) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "=====================================\n\n";
}

void BTree::PrintStats () {
    if (!root) {
        std::cout << "Stablo je prazno.\n";
        return;
    }

    Vector<Flight> allFlights = GetAllFlights ();

    std::cout << "\n=== Statistika B-stabla ===\n";
    std::cout << "Ukupan broj letova: " << allFlights.GetSize () << "\n";
    std::cout << "Parametar t: " << t << "\n";
    std::cout << "Max ključeva po čvoru: " << (2 * t - 1) << "\n";
    std::cout << "Min ključeva po čvoru: " << (t - 1) << " (osim root)\n";

    int depth = 0;
    BTreeNode* curr = root;
    while (!curr->leaf) {
        depth++;
        curr = curr->children[0];
    }
    std::cout << "Dubina stabla: " << depth << "\n";
    std::cout << "===========================\n\n";
}