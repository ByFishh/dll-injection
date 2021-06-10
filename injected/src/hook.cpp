#include "../include/epycheat.h"

typedef BOOL(__stdcall * twglSwapBuffers) (_In_ HDC hDc);
twglSwapBuffers owglSwapBuffers;

BOOL __stdcall hwglSwapBuffers(_In_ HDC hDc)
{
	if (data.display == 1) {
		SetupOrtho();
		Draw(500, 500, 200, 255, 255, 255, 50);
		RestoreGL();
	}
    return owglSwapBuffers(hDc);
}

int Hook(void)
{
	data.hook = GetProcAddress(GetModuleHandleA((LPCSTR)"opengl32.dll"), "wglSwapBuffers");
	MH_Initialize();
	MH_CreateHook(data.hook, hwglSwapBuffers, reinterpret_cast<void**>(&owglSwapBuffers));
	MH_EnableHook(data.hook);
	return 1;
}
