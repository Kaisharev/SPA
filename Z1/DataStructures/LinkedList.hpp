#pragma once
#include <iostream>

#include "../Entry/DiaryEntry.hpp"

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node (T value) : data (value), next (nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList () : head (nullptr), tail (nullptr) {}

    ~LinkedList () {
        while (head != nullptr) {
            pop_front ();
        }
    }

    void InsertFront (T value) {
        Node<T>* new_node = new Node<T> (value);
        new_node->next = head;

        head = new_node;

        if (tail == nullptr) tail = new_node;
    }

    void InsertBack (T value) {
        Node<T>* new_node = new Node<T> (value);
        if (head == nullptr) {
            head = tail = new_node;
            return;
        }

        tail->next = new_node;
        tail = new_node;
    }

    void InsertAt (int index, T value) {
        Node<T>* temp = head;
        Node<T>* new_node = new Node<T> (value);

        for (int i = 0; temp != nullptr && i < index - 1; i++) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            throw std::invalid_argument ("Uneseni indeks ne postoji u listi!");
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }

    void RemoveFront () {
        if (head == nullptr) {
            return;
        }

        Node<T>* temp = head;
        head = temp->next;

        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
    }

    void RemoveBack () {
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }
        Node<T>* temp = head;

        while (temp->next != tail) {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = nullptr;
    }

    void RemoveAt (int index) {
        if (head == nullptr || index < 0) {
            throw std::invalid_argument ("Lista je prazna ili ste unijeli negativan indeks!");
        }
        if (index == 0) {
            RemoveFront ();
            return;
        }

        Node<T>* temp = head;

        for (int i = 0; temp != nullptr && i < index - 1; ++i) {
            temp = temp->next;
        }

        if (temp == nullptr || temp->next == nullptr) {
            throw std::out_of_range ("Indeks van opsega!");
        }
        Node<T>* node_to_delete = temp->next;
        if (node_to_delete == tail) {
            tail = temp;
        }
        temp->next = node_to_delete->next;
        delete node_to_delete;
    }

    bool IsEmpty () const {
        return head == nullptr;
    }

    T GetFirstElement () const {
        if (!IsEmpty ()) {
            return head->data;
        }

        std::cerr << "Greska: Pokusaj citanja iz prazne liste!" << std::endl;
        exit (1);
    }

    void AddSorted (T value) {
        Node<T>* newNode = new Node<T> (value);

        if (IsEmpty () || value < head->data) {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr) {
                tail = head;
            }
            return;
        }

        Node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data < value) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;

        if (newNode->next == nullptr) {
            tail = newNode;
        }
    }
};
