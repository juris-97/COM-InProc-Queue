#include <stdio.h>
#include <windows.h>
#include "IQueue.h"


int main()
{
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	IQueue* iQueue;
	HRESULT res;

	CLSID CLSID_Queue;
	CLSIDFromProgID(L"COM.Queue.1", &CLSID_Queue);

	res = CoCreateInstance(CLSID_Queue, NULL, CLSCTX_INPROC_SERVER, IID_IQueue, (void**)& iQueue);

	if (!FAILED(res)) {
		iQueue->enqueue(1);
		iQueue->enqueue(2);
		iQueue->enqueue(3);

		iQueue->showQueue();
		iQueue->dequeue();

		int res;
		iQueue->peek(&res);
		printf("First element in Queue: %d\n", res);

		printf("Queue size: %d\n\n", iQueue->size());
		iQueue->Release();
	}

	CoUninitialize();
	return 0;
}

