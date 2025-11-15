#ifndef DEQUEUEIMPLEMENTATION_H
#define DEQUEUEIMPLEMENTATION_H

typedef struct DequeNode DequeNode;

struct DequeNode {
    int value;
    DequeNode *prev;
    DequeNode *next;
};

typedef struct {
    DequeNode *front;
    DequeNode *back;
    int size;
} Deque;

Deque *initDeque();
void pushFront(Deque *deque, int value);
void pushBack(Deque *deque, int value);
int popFront(Deque *deque);
int popBack(Deque *deque);
int peekFront(Deque *deque);
int peekBack(Deque *deque);
int isEmptyDeque(Deque *deque);
Deque* fillDequeInteractive(int maxSize);
void showDeque(Deque *deque);
void freeDeque(Deque *deque);

#endif //DEQUEUEIMPLEMENTATION_H
