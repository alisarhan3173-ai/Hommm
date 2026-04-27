#include <stdio.h>
#include <string.h>

#define SIZE 5   // حجم صغير لإظهار Overflow

typedef struct {
    char buffer[SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

/* Initialize Buffer */
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

/* Check Full */
int isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

/* Check Empty */
int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

/* Write to Buffer */
void writeBuffer(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("[OVERFLOW] Cannot insert '%c' -> Buffer is full.\n", data);
        return;
    }

    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count++;
}

/* Read from Buffer */
char readBuffer(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("[UNDERFLOW] Cannot read -> Buffer is empty.\n");
        return '\0';
    }

    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;

    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb);

    char name[50];

    printf("Enter your name: ");
    scanf("%49s", name);

    strcat(name, "CE-ESY");

    printf("\nFinal String After Appending: %s\n", name);

    printf("\n=== Writing To Circular Buffer ===\n");
    for (int i = 0; i < strlen(name); i++) {
        writeBuffer(&cb, name[i]);
    }

    printf("\n=== Reading From Circular Buffer ===\n");
    while (!isEmpty(&cb)) {
        printf("%c", readBuffer(&cb));
    }

    printf("\n");

    if (isEmpty(&cb)) {
        printf("\nBuffer is now empty.\n");
    }

    printf("\n=== Testing Underflow ===\n");
    readBuffer(&cb);

    return 0;
}
