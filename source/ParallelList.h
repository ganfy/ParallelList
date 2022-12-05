#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <mutex>
#include <thread>
#include <random>
using namespace std;

template<class T>
struct Node
{
    Node(T x)
    {
        value = x;
        next = 0;
    }
    Node() { next = 0; }
    T value;
    Node<T>* next;
    mutex m;
};

template<class T>
struct LLP
{
    Node<T>* head;
    Node<T>* tail;
    size_t size;

    LLP()
    {
        head = new Node<T>();
        size = 0;
        tail = new Node<T>();
        head->next = tail;
    }

    bool add(T x);
    bool delet(T x);
    //bool find(T v, Node<T>*& pos);
    //bool contains(T x);
    void print();
    

};


template<class T>
bool LLP<T>::add(T x) {
    Node<T>* newNode = new Node<T>(x);

    if (newNode == nullptr) {
        return false;
    }

    //solo es necesario bloquear la cola porque los nodos se añaden al final
    std::lock_guard<std::mutex> lock(tail->m); //lock_guard para tener el nodo mientras se realiza la inserción 
    tail->next = newNode;
    tail = newNode;
    size++;

    return true;
}

template<class T>
bool LLP<T>::delet(T x) {
    if (size == 0) return false;

    //bloqueamos la cabeza
    lock_guard<mutex> lock1(head->m);
    Node<T>* prev = head;
    Node<T>* curr = head->next;

    //si el nodo a borrar es la cabeza
    if (prev->value == x) {
        head = curr;
        size--;
        return true;
    }

    //se busca el nodo a borrar mientras se bloquea el nodo que se visita
    while (curr != tail) {
        lock_guard<mutex> lock2(curr->m);
        if (curr->value == x) {
            prev->next = curr->next;
            if (curr == tail) {
                tail = prev;
            }
            size--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}


template<class T>
void LLP<T>::print()
{
    Node<T>* p = head->next;
    while (p) {
        cout << p->value << "->";
        p = p->next;
    }
    cout << endl;
}


int get_random(int low, int high) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(low, high);
    return distribution(gen);
}

template<class T>
struct add {
    LLP<T>* list_;
    int min_, max_;

    add(LLP<T>* list, int min, int max) : list_(list), min_(min), max_(max) {}

    void operator()(int n) {
        for (int i = 0; i < n; i++) {
            int value = get_random(min_, max_);
            list_->add(value);
        }
    }
};

template<class T>
struct dlt {
    LLP<T>* list_;
    int min_, max_;

    dlt(LLP<T>* list, int min, int max) : list_(list), min_(min), max_(max) {}

    void operator()(int n) {
        for (int i = 0; i < n; i++) {
            int number = get_random(min_, max_);
            list_->delet(number);
        }
    }
};
