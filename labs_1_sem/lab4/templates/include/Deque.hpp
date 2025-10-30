#pragma once
#include <cstddef>
#include <algorithm>

using namespace std;

template<typename T>
struct DequeNode {
    T value;
    DequeNode* prev;
    DequeNode* next;
};

template<typename T>
class Deque {
private:
    DequeNode<T>* top;
    DequeNode<T>* bottom;
    int currentSize;

public:
    Deque() {
        this->top = nullptr;
        this->bottom = nullptr;
        this->currentSize = 0;
    }
    
    Deque(const Deque& other) {
        this->top = nullptr;
        this->bottom = nullptr;
        this->currentSize = 0;
        DequeNode<T>* current = other.top;
        while (current != nullptr) {
            this->pushBack(current->value);
            current = current->next;
        }
    }
    
    Deque& operator=(const Deque& other) {
        if (this != &other) {
            this->clearDeque();
            DequeNode<T>* current = other.top;
            while (current != nullptr) {
                this->pushBack(current->value);
                current = current->next;
            }
        }
        return *this;
    }
    
    ~Deque() {
        while (!this->isEmpty()) {
            this->popFront();
        }
    }
    
    void pushFront(const T& value) {
        DequeNode<T>* newNode = new DequeNode<T>{value, nullptr, this->top};
        
        if (this->isEmpty()) {
            this->top = newNode;
            this->bottom = newNode;
        } else {
            this->top->prev = newNode;
            this->top = newNode;
        }
        this->currentSize++;
    }
    
    void pushBack(const T& value) {
        DequeNode<T>* newNode = new DequeNode<T>{value, this->bottom, nullptr};
        
        if (this->isEmpty()) {
            this->top = newNode;
            this->bottom = newNode;
        } else {
            this->bottom->next = newNode;
            this->bottom = newNode;
        }
        this->currentSize++;
    }
    
    void popFront() {
        if (this->isEmpty()) {
            return;
        }
        
        DequeNode<T>* temp = this->top;
        this->top = this->top->next;
        
        if (this->top != nullptr) {
            this->top->prev = nullptr;
        } else {
            this->bottom = nullptr;
        }
        
        delete temp;
        this->currentSize--;
    }
    
    void popBack() {
        if (this->isEmpty()) {
            return;
        }
        
        DequeNode<T>* temp = this->bottom;
        this->bottom = this->bottom->prev;
        
        if (this->bottom != nullptr) {
            this->bottom->next = nullptr;
        } else {
            this->top = nullptr;
        }
        
        delete temp;
        this->currentSize--;
    }
    
    T& peekFirst() {
        return this->top->value;
    }
    
    const T& peekFirst() const {
        return this->top->value;
    }
    
    T& peekLast() {
        return this->bottom->value;
    }
    
    const T& peekLast() const {
        return this->bottom->value;
    }
    
    bool isEmpty() const {
        return this->currentSize == 0;
    }
    
    int size() const {
        return this->currentSize;
    }
    
    void clearDeque() {
        while (!this->isEmpty()) {
            this->popFront();
        }
    }
    
    DequeNode<T>* find(const T& value) const {
        DequeNode<T>* current = this->top;
        while (current != nullptr) {
            if (current->value == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
    void sort() {
        if (this->isEmpty() || this->top->next == nullptr) return;
        
        short swapped;
        do {
            swapped = 0;
            DequeNode<T>* current = this->top;
            while (current->next != nullptr) {
                if (current->next->value < current->value) {
                    swap(current->value, current->next->value);
                    swapped = 1;
                }
                current = current->next;
            }
        } while (swapped);
    }
};