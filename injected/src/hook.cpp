#include "../include/epycheat.h"

typedef BOOL(__stdcall * twglSwapBuffers) (_In_ HDC hDc);
twglSwapBuffers owglSwapBuffers;

BOOL __stdcall hwglSwapBuffers(_In_ HDC hDc)
{
	if (data.display == 1) {
		//3D
		//PlayerEsp3D(); Marche pas dans le hook
		//2D
		SetupOrtho();
		DrawRect(10, 10, 220, 10, 214, 62, 32, 250);
		DrawRect(10, 20, 220, 300, 68, 65, 61, 140);
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
