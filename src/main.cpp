#include "epycheat.h"

void test()
{
    HMODULE jvmHandle;
    JavaVM *jvm = NULL;
    JNIEnv *env;

    jsize count;
	if (JNI_GetCreatedJavaVMs(&jvm, 1, &count) != JNI_OK || count == 0) {
		std::cout << "Failed to get the JVM" << std::endl;
		return;
	}
	jint res = jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
	if (res == JNI_EDETACHED)
		res = jvm->AttachCurrentThread((void **)&env, nullptr);
	if (res != JNI_OK) {
		std::cout << "Failed to attach to thread" << std::endl;
		return;
	}
	std::cout << "Attached to JVM" << std::endl;





    jvmHandle = GetModuleHandleA("jvm.dll");
	if (!jvmHandle)
		std::cout << "[-] Failed to get JVM Handle" << std::endl;
 
	if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) == JNI_EDETACHED)
	{
		jvm->AttachCurrentThread((void**)&env, NULL);
	}
 
	if (env != nullptr)
	{
		auto class_loader = env->FindClass("java/lang/ClassLoader");
 
		auto get_system_loader =
			env->GetStaticMethodID(class_loader, "getSystemClassLoader",
				"()Ljava/lang/ClassLoader;");

		auto system_loader =
			env->CallStaticObjectMethod(class_loader, get_system_loader);

		//jenv->DefineClass("net/minecraft/hey", system_loader, customclass, sizeof(customclass));
 
		return;
	}
}


void inject()
{
	AllocConsole();
	FILE* fIn;
	FILE* fOut;
	freopen_s(&fIn, "conin$", "r", stdin);
	freopen_s(&fOut, "conout$", "w", stdout);
	freopen_s(&fOut, "conout$", "w", stderr);

	std::cout << "Injection Successful!" << std::endl;

    test();

    std::cout << "Injection dxrtrfcgtfy!" << std::endl;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)inject, nullptr, 0, nullptr);
	return TRUE;
}