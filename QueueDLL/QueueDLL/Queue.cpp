#include <windows.h>
#include <stdio.h>
#include "Queue.h"

extern volatile ULONG UCQueue = 0; // Queue usage count

Queue::Queue(int size) {

	InterlockedIncrement(&UCQueue);
	m_ref = 0;

	// queue initialization
	arr = new int[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;

	printf("Licznik referencji: %d\n", UCQueue);
}

Queue::~Queue() {
	InterlockedDecrement(&UCQueue);
	delete[] arr;
}

HRESULT Queue::dequeue() {

	if (isEmpty()) {
		printf("Brak elementow w kolejce\n");
		return E_FAIL;
	}

	printf("Usuniety element %d\n", arr[front]);
	front = (front + 1) % capacity;
	count--;

	return S_OK;
}

HRESULT Queue::enqueue(int item) {

	if (isFull()) {
		printf("Za du¿o elementow w kolejce\n");
		return E_FAIL;
	}

	printf("Wstawiony element %d\n", item);

	rear = (rear + 1) % capacity;
	arr[rear] = item;
	count++;
	return S_OK;
}

HRESULT Queue::peek(int* res)
{
	if (isEmpty())
	{
		printf("Brak elementow w kolejce\n");
		return E_FAIL;
	}
	*res = arr[front];
	return S_OK;
}

int Queue::size() {
	return count;
}


BOOL Queue::isEmpty() {
	return (size() == 0);
}


BOOL Queue::isFull() {
	return (size() == capacity);
}

HRESULT STDMETHODCALLTYPE Queue::showQueue() {
	printf("Queue: ");
	for (int i = 0; i < count; i++) {
		printf("%d ", arr[i]);
	}printf("\n");
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Queue::QueryInterface(REFIID iid, void** ptr) {
	if (ptr == NULL) return E_POINTER;
	*ptr = NULL;
	if (iid == IID_IUnknown)* ptr = this;
	else if (iid == IID_IQueue)* ptr = this;
	if (*ptr != NULL) { AddRef(); return S_OK; }
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE Queue::AddRef() {
	InterlockedIncrement(&m_ref);
	return m_ref;
}

ULONG STDMETHODCALLTYPE Queue::Release() {
	ULONG res = InterlockedDecrement(&m_ref);
	if (res == NULL) delete this;
	return m_ref;
}
