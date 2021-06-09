#include "../include/epycheat.h"

struct data_t {
    JavaVM *jvm;
    JNIEnv *env;
	HWND hWnd;
	HMODULE hModule;
	void* hook;
	int close;
	int display;
} data;

int HandleJvm(void)
{
    HMODULE jvmHandle = GetModuleHandleA("jvm.dll");

	if (!jvmHandle) {
        std::cout << "[-] Failed to get JVM Handle" << std::endl;
        return 0;
    }	
	if (data.jvm->GetEnv((void**)&data.env, JNI_VERSION_1_6) == JNI_EDETACHED)
		data.jvm->AttachCurrentThread((void**)&data.env, NULL);
	
    std::cout << "[+] Handle Successful!" << std::endl;
    return 1;
}

int AttachJvm(void)
{
    jsize count;
    jint res;

	if (JNI_GetCreatedJavaVMs(&data.jvm, 1, &count) != JNI_OK || count == 0) {
		std::cout << "[-] Failed to get the JVM" << std::endl;
		return 0;
	}
	res = data.jvm->GetEnv((void **)&data.env, JNI_VERSION_1_6);
	if (res == JNI_EDETACHED)
		res = data.jvm->AttachCurrentThread((void **)&data.env, nullptr);
	if (res != JNI_OK) {
		std::cout << "[-] Failed to attach to thread" << std::endl;
		return 0;
	}
	std::cout << "[+] Attached to JVM" << std::endl;
    return 1;
}

void AttachConsole(void)
{
	AllocConsole();
	SetConsoleTitleA("EPYCheat");
	FILE* fOut;
	freopen_s(&fOut, "conout$", "w", stdout);
}

void DetachConsole(void)
{
	data.close = 1;
	MH_RemoveHook(data.hook);
	MH_Uninitialize();
	data.jvm->DetachCurrentThread();
	FreeConsole();
	fclose(stdout);
	std::this_thread::sleep_for (std::chrono::seconds(1));
	FreeLibraryAndExitThread(data.hModule, NULL);
}

jobject getMc()
{
	jclass mc_class = data.env->FindClass("net/minecraft/client/Minecraft");
	jmethodID find_entry = data.env->GetStaticMethodID(mc_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
	jobject instance = data.env->CallStaticObjectMethod(mc_class, find_entry);

	return instance;
}

jobject getPlayer() {
	jmethodID get_player = data.env->GetMethodID(data.env->FindClass("net/minecraft/client/Minecraft"), "getSession", "Lnet/minecraft/util/Session;");
	jobject obj = data.env->CallObjectMethod(getMc(), get_player, "V");

	return obj;
}

void sendMessage(const char *message) {
	jclass mc_class = data.env->FindClass("net/minecraft/client/entity/EntityClientPlayerMP");
	jmethodID constructor = data.env->GetMethodID(mc_class, "<init>", "(Lnet/minecraft/client/Minecraft;Lnet/minecraft/world/World;Lnet/minecraft/util/Session;Lnet/minecraft/client/network/NetHandlerPlayClient;Lnet/minecraft/stats/StatFileWriter;)V");
	jfieldID fid = data.env->GetFieldID(data.env->GetObjectClass(getMc()), "thePlayer", "Lnet/minecraft/client/entity/EntityClientPlayerMP;");
	jobject obj = data.env->GetObjectField(getMc(), fid);
	jmethodID get_name = data.env->GetMethodID(mc_class, "sendChatMessage", "(Ljava/lang/String;)V");

	data.env->CallVoidMethod(obj, get_name, data.env->NewStringUTF(message));
}

void SetupOrtho(void)
{
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	glPushMatrix( );
	GLint viewport [ 4 ];
	glGetIntegerv( GL_VIEWPORT, viewport );
	glViewport( 0, 0, viewport [ 2 ], viewport [ 3 ] );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glOrtho( 0, viewport [ 2 ], viewport [ 3 ], 0, -1, 1 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glDisable( GL_DEPTH_TEST );
}

const GLubyte red[3] = { 255, 0, 0 };

void Draw( GLfloat x, GLfloat y, GLfloat sidelength, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha )
{
	glEnable( GL_BLEND );
	glColor4ub( r, g, b, alpha );

	GLfloat halfside = sidelength / 2;

	glBegin( GL_QUADS );
	glVertex2d( x + halfside, y + halfside );
	glVertex2d( x + halfside, y - halfside );
	glVertex2d( x - halfside, y - halfside );
	glVertex2d( x - halfside, y + halfside );
	glEnd( );
}

void RestoreGL(void)
{
	glPopMatrix( );
	glPopAttrib( );
}

void Process(void)
{
	std::cout << "[+] Injection Successful!" << std::endl;

	while (true) {
		if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
			DetachConsole();
			break;
		}
		if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			data.display = !data.display;
			sendMessage("TEST");
		}
            
	}
}

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

int Hook()
{
	data.hook = GetProcAddress(GetModuleHandleA((LPCSTR)"opengl32.dll"), "wglSwapBuffers");
	MH_Initialize();
	MH_CreateHook(data.hook, hwglSwapBuffers, reinterpret_cast<void**>(&owglSwapBuffers));
	MH_EnableHook(data.hook);
	return 1;
}

void Inject()
{
	AttachConsole();

    if (!AttachJvm() || !HandleJvm() || !Hook())
        return;

    Process();
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved, HWND hWnd) {
	if (fdwReason == DLL_PROCESS_ATTACH && data.close == 0) {
		data.hWnd = hWnd;
		data.hModule = hinstDLL;
		
		DisableThreadLibraryCalls(hinstDLL);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Inject, nullptr, 0, nullptr));
	}	
	return TRUE;
}