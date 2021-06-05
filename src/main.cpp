#include "epycheat.h"

struct data_t {
    JavaVM *jvm;
    JNIEnv *env;
} data;

int handle_jvm(void)
{
    HMODULE jvmHandle = GetModuleHandleA("jvm.dll");

	if (!jvmHandle) {
        std::cout << "[-] Failed to get JVM Handle" << std::endl;
        return 84;
    }	
	if (data.jvm->GetEnv((void**)&data.env, JNI_VERSION_1_6) == JNI_EDETACHED)
		data.jvm->AttachCurrentThread((void**)&data.env, NULL);
    std::cout << "[+] Handle Successful!" << std::endl;
    return 0;
}

int attach_jvm(void)
{
    jsize count;
    jint res;

	if (JNI_GetCreatedJavaVMs(&data.jvm, 1, &count) != JNI_OK || count == 0) {
		std::cout << "[-] Failed to get the JVM" << std::endl;
		return 84;
	}
	res = data.jvm->GetEnv((void **)&data.env, JNI_VERSION_1_6);
	if (res == JNI_EDETACHED)
		res = data.jvm->AttachCurrentThread((void **)&data.env, nullptr);
	if (res != JNI_OK) {
		std::cout << "[-] Failed to attach to thread" << std::endl;
		return 84;
	}
	std::cout << "[+] Attached to JVM" << std::endl;
    return 0;
}

jobject getMc()
{
	jclass mc_class = data.env->FindClass("net/minecraft/client/Minecraft");
	jmethodID find_entry = data.env->GetStaticMethodID(mc_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
	jobject instance = data.env->CallStaticObjectMethod(mc_class, find_entry);

	return instance;
}

jobject get_player( ) {
	jfieldID get_player = data.env->GetFieldID( data.env->GetObjectClass(getMc()), "thePlayer", "Lnet/minecraft/client/Minecraft;");
	return data.env->GetObjectField( getMc( ), get_player);
}

std::string name( ) {
	std::cout << "1.1" << std::endl;
	jclass mc_class = data.env->FindClass("net/minecraft/client/entity/EntityClientPlayerMP");
	if (mc_class == nullptr)
		std::cout << "mc_class" << std::endl;
	std::cout << "1.2" << std::endl;
	jmethodID get_name = data.env->GetMethodID(mc_class, "sendChatMessage", "(Ljava/lang/String;)V");
	if (get_name == nullptr)
		std::cout << "get_name" << std::endl;
	std::cout << "1.3" << std::endl;
	jstring test = data.env->NewStringUTF("SALUT");
	if (test == nullptr)
		std::cout << "test" << std::endl;
	std::cout << "1.4" << std::endl;
	data.env->CallVoidMethod(data.env->GetObjectClass(mc_class), get_name, data.env->NewStringUTF("dxfg"));
	std::cout << "1.6" << std::endl;

	return nullptr;
}

void process()
{
    jobject mc = getMc();
	std::cout << "1" << std::endl;
	std::string pseudo = name();
	std::cout << "2" << std::endl;

	//std::cout << pseudo << std::endl;
}

void inject()
{
	AllocConsole();
	FILE* fIn;
	FILE* fOut;
	freopen_s(&fIn, "conin$", "r", stdin);
	freopen_s(&fOut, "conout$", "w", stdout);
	freopen_s(&fOut, "conout$", "w", stderr);

    if (attach_jvm() == 84 || handle_jvm() == 84)
        return;
    process();

    std::cout << "[+] Injection Successful!" << std::endl;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)inject, nullptr, 0, nullptr);
	return TRUE;
}