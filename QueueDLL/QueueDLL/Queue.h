#include <windows.h>
#include "IQueue.h"


// {D3FB9EA7-7627-4461-9FD6-A156E9D578D4}
class Queue : public IQueue {

	int* arr;		// array to store queue elements
	int capacity;	// maximum capacity of the queue
	int front;		// front points to the front element in the queue (if any)
	int rear;		// rear points to the last element in the queue
	int count;		// current size of the queue

public:
	Queue(int size);
	~Queue();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** rv);
	virtual ULONG	STDMETHODCALLTYPE AddRef();
	virtual ULONG	STDMETHODCALLTYPE Release();

	virtual HRESULT STDMETHODCALLTYPE dequeue();		  // Utility function to dequeue the front element
	virtual HRESULT STDMETHODCALLTYPE enqueue(int x);	  // Utility function to add an item to the queue

	virtual HRESULT STDMETHODCALLTYPE peek(int* res);	  // Utility function to return the front element of the queue
	virtual int 	STDMETHODCALLTYPE size();
	virtual BOOL	STDMETHODCALLTYPE isEmpty();
	virtual BOOL	STDMETHODCALLTYPE isFull();
	virtual HRESULT	STDMETHODCALLTYPE showQueue();

private:
	volatile ULONG m_ref;

};