#include "../include/epycheat.h"

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
	jmethodID get_player = data.env->GetMethodID(data.env->FindClass("net/minecraft/client/Minecraft"), "getSession", "Lnet/minecraft/util/Session;");
	jobject obj = data.env->CallObjectMethod(getMc(), get_player, "V");
	return obj;
}

void name() {
	jclass mc_class = data.env->FindClass("net/minecraft/client/entity/EntityClientPlayerMP");
	jclass mc_class_origin = data.env->FindClass("net/minecraft/client/Minecraft");

	jmethodID constructor = data.env->GetMethodID(mc_class, "<init>", "(Lnet/minecraft/client/Minecraft;Lnet/minecraft/world/World;Lnet/minecraft/util/Session;Lnet/minecraft/client/network/NetHandlerPlayClient;Lnet/minecraft/stats/StatFileWriter;)V");

	jfieldID fid = data.env->GetFieldID(mc_class_origin, "thePlayer", "Lnet/minecraft/client/entity/EntityClientPlayerMP;");
	jobject obj = data.env->GetObjectField(getMc(), fid);
	jmethodID get_name = data.env->GetMethodID(mc_class, "sendChatMessage", "(Ljava/lang/String;)V");
	data.env->CallVoidMethod(obj, get_name, data.env->NewStringUTF("Bonjour à tous les amis !"));
	data.env->CallVoidMethod(obj, get_name, data.env->NewStringUTF("Pierrick Nique"));
	while (1)
		data.env->CallVoidMethod(obj, get_name, data.env->NewStringUTF("Injection complete !"));
	return;
}

void process()
{
    jobject mc = getMc();
	name();
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