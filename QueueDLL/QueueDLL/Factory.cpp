#include "Factory.h"
#include "Queue.h"

#define SIZE_ 10
extern volatile ULONG UCFactory = 0; // usage count

Factory::Factory() {
	m_ref = 0;
};

Factory::~Factory() {};

HRESULT STDMETHODCALLTYPE Factory::QueryInterface(REFIID iid, void** ptr) {
	if (ptr == NULL) return E_POINTER;
	*ptr = NULL;
	if (iid == IID_IUnknown)* ptr = this;
	else if (iid == IID_IClassFactory)* ptr = this;
	if (*ptr != NULL) { AddRef(); return S_OK; }
	return E_NOINTERFACE;
};

ULONG STDMETHODCALLTYPE Factory::AddRef() {
	InterlockedIncrement(&m_ref);
	return m_ref;
}

ULONG STDMETHODCALLTYPE Factory::Release() {
	ULONG res = InterlockedDecrement(&m_ref);
	if (res == 0) delete this;
	return res;
}

HRESULT STDMETHODCALLTYPE Factory::LockServer(BOOL v) {
	if (v) InterlockedIncrement(&UCFactory);
	else InterlockedDecrement(&UCFactory);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Factory::CreateInstance(IUnknown* outer, REFIID iid, void** ptr) {
	if (ptr == NULL) return E_POINTER;
	*ptr = NULL;
	if (iid != IID_IUnknown && iid != IID_IQueue) return E_NOINTERFACE;

	Queue* obj = new Queue(SIZE_);
	if (obj == NULL) return E_OUTOFMEMORY;

	HRESULT res = obj->QueryInterface(iid, ptr);
	if (FAILED(res)) { delete obj; *ptr = NULL; }
	return res;
}