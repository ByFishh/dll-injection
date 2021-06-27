#include "../include/epycheat.h"

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