// #include "../include/Deque.hpp"
// #include <stdexcept>

// template<typename T>
// Deque<T>::Deque() {
//     this->top = nullptr;
//     this->bottom = nullptr;
//     this->currentSize = 0;
// }

// template<typename T>
// Deque<T>::Deque(const Deque& other) {
//     this->top = nullptr;
//     this->bottom = nullptr;
//     this->currentSize = 0;
//     DequeNode<T>* current = other.top;
//     while (current != nullptr) {
//         this->pushBack(current->value);
//         current = current->next;
//     }
// }

// template<typename T>
// Deque<T>& Deque<T>::operator=(const Deque& other) {
//     if (this != &other) {
//         this->clearDeque();
//         DequeNode<T>* current = other.top;
//         while (current != nullptr) {
//             this->pushBack(current->value);
//             current = current->next;
//         }
//     }
//     return *this;
// }

// template<typename T>
// Deque<T>::~Deque() {
//     this->clearDeque();
// }

// template<typename T>
// void Deque<T>::pushFront(const T& value) {
//     DequeNode<T>* newNode = new DequeNode<T>{value, nullptr, this->top};
    
//     if (this->isEmpty()) {
//         this->top = newNode;
//         this->bottom = newNode;
//     } else {
//         this->top->prev = newNode;
//         this->top = newNode;
//     }
//     this->currentSize++;
// }

// template<typename T>
// void Deque<T>::pushBack(const T& value) {
//     DequeNode<T>* newNode = new DequeNode<T>{value, this->bottom, nullptr};
    
//     if (this->isEmpty()) {
//         this->top = newNode;
//         this->bottom = newNode;
//     } else {
//         this->bottom->next = newNode;
//         this->bottom = newNode;
//     }
//     this->currentSize++;
// }

// template<typename T>
// void Deque<T>::popFront() {
//     if (this->isEmpty()) {
//         throw std::runtime_error("Cannot pop from empty deque");
//     }
    
//     DequeNode<T>* temp = this->top;
//     this->top = this->top->next;
    
//     if (this->top != nullptr) {
//         this->top->prev = nullptr;
//     } else {
//         this->bottom = nullptr;
//     }
    
//     delete temp;
//     this->currentSize--;
// }

// template<typename T>
// void Deque<T>::popBack() {
//     if (this->isEmpty()) {
//         throw std::runtime_error("Cannot pop from empty deque");
//     }
    
//     DequeNode<T>* temp = this->bottom;
//     this->bottom = this->bottom->prev;
    
//     if (this->bottom != nullptr) {
//         this->bottom->next = nullptr;
//     } else {
//         this->top = nullptr;
//     }
    
//     delete temp;
//     this->currentSize--;
// }

// template<typename T>
// T& Deque<T>::peekFirst() {
//     if (this->isEmpty()) {
//         throw std::runtime_error("Deque is empty");
//     }
//     return this->top->value;
// }

// template<typename T>
// const T& Deque<T>::peekFirst() const {
//     if (this->isEmpty()) {
//         throw std::runtime_error("Deque is empty");
//     }
//     return this->top->value;
// }

// template<typename T>
// T& Deque<T>::peekLast() {
//     if (this->isEmpty()) {
//         throw std::runtime_error("Deque is empty");
//     }
//     return this->bottom->value;
// }

// template<typename T>
// const T& Deque<T>::peekLast() const {
//     if (this->isEmpty()) {
//         throw std::runtime_error("Deque is empty");
//     }
//     return this->bottom->value;
// }

// template<typename T>
// bool Deque<T>::isEmpty() const {
//     return this->currentSize == 0;
// }

// template<typename T>
// size_t Deque<T>::size() const {
//     return this->currentSize;
// }

// template<typename T>
// void Deque<T>::clearDeque() {
//     while (!this->isEmpty()) {
//         this->popFront();
//     }
// }