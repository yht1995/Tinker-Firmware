#include "RingBuffer.h"

RingBuffer::RingBuffer(int capacity)
{
	this->_capacity = capacity;
	this->head = 0;
	this->tail = 0;
	this->buffer = new uint8_t[capacity];
	this->count = 0;
}

RingBuffer::~RingBuffer()
{
	delete [] this->buffer;
}

bool RingBuffer::isEmpty()
{
	return head == tail;
}

int RingBuffer::remain()
{
	return this->_capacity - this->count;
}

void RingBuffer::push_back(uint8_t d)
{
	tail = (tail + 1) % _capacity;
	this->buffer[tail] = d;
	this->count++;
}

int RingBuffer::pop_front()
{
	if (!isEmpty()) {
		head = (head + 1) % _capacity;
		this->count--;
		return buffer[head];
	}
	return -1;
}
