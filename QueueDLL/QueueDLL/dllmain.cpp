#include <windows.h>
#include "Factory.h"
#include "Queue.h"

// dllmain.cpp : Defines the entry point for the DLL application.

volatile ULONG usageCount = 0;

// operating system calls this function to get the Factory class objects with CLS_ID 
HRESULT __stdcall DllGetClassObject(REFCLSID cls, REFIID iid, void** ptr) {
	if (ptr == NULL) return E_INVALIDARG;
	*ptr = NULL;
	if (cls != CLSID_Queue) return CLASS_E_CLASSNOTAVAILABLE;
	if (iid != IID_IUnknown && iid != IID_IClassFactory) return E_NOINTERFACE;
	Factory* factory = new Factory();
	if (factory == NULL) return E_OUTOFMEMORY;
	HRESULT rv = factory->QueryInterface(iid, ptr);
	if (FAILED(rv)) { delete factory; *ptr = NULL; };
	return rv;
};

// if can be deleted from memory
HRESULT __stdcall DllCanUnloadNow() {
	return usageCount > 0 ? S_FALSE : S_OK;
};

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

