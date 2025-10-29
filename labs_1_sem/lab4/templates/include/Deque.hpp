#pragma once
#include <cstddef>
#include <stdexcept>

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
    size_t currentSize;

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
        this->clearDeque();
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
            throw std::runtime_error("Cannot pop from empty deque");
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
            throw std::runtime_error("Cannot pop from empty deque");
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
        if (this->isEmpty()) {
            throw std::runtime_error("Deque is empty");
        }
        return this->top->value;
    }
    
    const T& peekFirst() const {
        if (this->isEmpty()) {
            throw std::runtime_error("Deque is empty");
        }
        return this->top->value;
    }
    
    T& peekLast() {
        if (this->isEmpty()) {
            throw std::runtime_error("Deque is empty");
        }
        return this->bottom->value;
    }
    
    const T& peekLast() const {
        if (this->isEmpty()) {
            throw std::runtime_error("Deque is empty");
        }
        return this->bottom->value;
    }
    
    bool isEmpty() const {
        return this->currentSize == 0;
    }
    
    size_t size() const {
        return this->currentSize;
    }
    
    void clearDeque() {
        while (!this->isEmpty()) {
            this->popFront();
        }
    }
};