#include <windows.h>

class Factory : public IClassFactory {

public:
	Factory();
	~Factory();

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** rv);
	virtual ULONG	STDMETHODCALLTYPE AddRef();
	virtual ULONG	STDMETHODCALLTYPE Release();
	virtual HRESULT	STDMETHODCALLTYPE LockServer(BOOL v);
	virtual HRESULT	STDMETHODCALLTYPE CreateInstance(IUnknown* outer, REFIID iid, void** rv);

private:
	volatile ULONG m_ref; // references counter
};