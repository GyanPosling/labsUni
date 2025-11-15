#ifndef QUEUEIMPLEMENTATION_H
#define QUEUEIMPLEMENTATION_H

typedef struct Node Node;

struct Node {
    int value;
    Node *prev;
    Node *next;
};

typedef struct {
    Node *top;
    Node *bottom;
    int size;
} Queue;

Queue *initQueue();
void push(Queue *queue, int value);
int pop(Queue *queue);
int peek(Queue *queue);
int peekLast(Queue *queue);
int isEmpty(Queue *queue);
Queue *fillQueue(int size);
Queue* fillQueueInteractive(int maxSize);
void showQueue(Queue *queue);
void freeQueue(Queue *queue);

#endif