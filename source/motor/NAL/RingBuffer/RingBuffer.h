#ifndef _RING_BUFFER_H__
#define _RING_BUFFER_H__

#include <stdint.h>
#include <stdbool.h>

class RingBuffer {
public:
	RingBuffer(int capacity);
    ~RingBuffer();
	void push_back(uint8_t d);
	int pop_front(void);
    bool isEmpty();
	int remain();
private:
    int _capacity;
    int head;
    int tail;
	int count;
	uint8_t *buffer;
};
#endif
