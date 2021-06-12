#include "../include/epycheat.h"

data_t data;
int flyEnabled;

jobject GetMc()
{
	jclass mc_class = data.env->FindClass("net/minecraft/client/Minecraft");
	jmethodID find_entry = data.env->GetStaticMethodID(mc_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
	jobject instance = data.env->CallStaticObjectMethod(mc_class, find_entry);

	return instance;
}

jobject GetPlayer()
{
	jclass mc_class = data.env->FindClass("net/minecraft/client/entity/EntityClientPlayerMP");
	jmethodID constructor = data.env->GetMethodID(mc_class, "<init>", "(Lnet/minecraft/client/Minecraft;Lnet/minecraft/world/World;Lnet/minecraft/util/Session;Lnet/minecraft/client/network/NetHandlerPlayClient;Lnet/minecraft/stats/StatFileWriter;)V");
	jfieldID fid = data.env->GetFieldID(data.env->GetObjectClass(GetMc()), "thePlayer", "Lnet/minecraft/client/entity/EntityClientPlayerMP;");
	jobject obj = data.env->GetObjectField(GetMc(), fid);

	return obj;
}

jobject GetWorld()
{
    jfieldID worldfid = data.env->GetFieldID(data.env->GetObjectClass(GetMc()), "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
	jobject obj = data.env->GetObjectField(GetMc(), worldfid);
	return obj;
}

jobjectArray GetNearbyEntity()
{
	jfieldID fid = data.env->GetFieldID(data.env->GetObjectClass(GetWorld()), "loadedEntityList", "Ljava/util/List;");
	jclass list_cls = data.env->FindClass("java/util/List");
	jmethodID to_array_md = data.env->GetMethodID(list_cls, "toArray", "()[Ljava/lang/Object;");
	jobject obj_player_entities = data.env->GetObjectField(GetWorld(), fid);
	jobjectArray array_entity_list = reinterpret_cast<jobjectArray>(data.env->CallObjectMethod(obj_player_entities, to_array_md));

	return array_entity_list;
}

void SendChatMessage(const char *message)
{
	jclass mc_class = data.env->FindClass("net/minecraft/client/entity/EntityClientPlayerMP");
	jmethodID get_name = data.env->GetMethodID(mc_class, "sendChatMessage", "(Ljava/lang/String;)V");
	data.env->CallVoidMethod(GetPlayer(), get_name, data.env->NewStringUTF(message));
}

const GLubyte red[3] = { 255, 0, 0 };

void DrawHUD(void)
{
	glEnable( GL_BLEND );
	glColor4ub( 68, 65, 61, 140);

	glBegin(GL_QUADS);
	glVertex2d(4, 4);
	glVertex2d(4+140, 4);
	glVertex2d(4+140, 4+60);
	glVertex2d(4, 4+60);

	glEnd();
}

void Process(void)
{
	std::cout << "[+] Injection Successful!" << std::endl;
	data.display = 0;
	while (true) {
		if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
			DetachConsole();
			break;
		}
		if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			data.display = !data.display;
			PlayerEsp3D();
			//ModifyFlyState();
			//SendChatMessage("swfd");
			//PlayerEsp2D();
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