#include <windows.h>

DEFINE_GUID(IID_IQueue, 0xad284350, 0x8942, 0x49d7, 0xbb, 0x1c, 0xeb, 0x86, 0x25, 0xda, 0x50, 0xaa);

// {AD284350-8942-49D7-BB1C-EB8625DA50AA}
class IQueue : public IUnknown {

public:
	virtual HRESULT STDMETHODCALLTYPE dequeue() = 0;
	virtual HRESULT STDMETHODCALLTYPE enqueue(int x) = 0;
	virtual HRESULT STDMETHODCALLTYPE peek(int* res) = 0;
	virtual int 	STDMETHODCALLTYPE size() = 0;
	virtual BOOL	STDMETHODCALLTYPE isEmpty() = 0;
	virtual BOOL	STDMETHODCALLTYPE isFull() = 0;
	virtual HRESULT	STDMETHODCALLTYPE showQueue() = 0;
};
