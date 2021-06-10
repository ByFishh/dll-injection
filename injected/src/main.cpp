#include "../include/epycheat.h"

data_t data;

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

const GLubyte red[3] = { 255, 0, 0 };

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
			sendMessage("/time set 0");
		}
	}
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