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

void inject_class()
{
    /*
    bool is1_8 = (settings->version == Version::FORGE_1_8 || settings->version == Version::VANILLA_1_8 || settings->version == Version::LUNAR_1_8);
    std::string type = is1_8 ? "(Ljava/lang/String;FFIZ)I" : "(Ljava/lang/String;IIIZ)I";
    
    jclass FontRenderer_clazz = cheat::g_Hack->FindClass(Mapper::getMapping("net/minecraft/client/gui/FontRenderer").data());
    jmethodID renderText_mid = cheat::g_Hack->env()->GetMethodID(FontRenderer_clazz, Mapper::getMapping("drawString").data(), type.data());
    jstring txtToRender = cheat::g_Hack->env()->NewStringUTF(txt.data());
    
    if (is1_8)
        cheat::g_Hack->env()->CallIntMethod(Minecraft::get().GetFontRendererObj(Minecraft::get().GetTheMinecraftObj()), renderText_mid, txtToRender, (float)x, (float)y, color, shadow);
    else
        cheat::g_Hack->env()->CallIntMethod(Minecraft::get().GetFontRendererObj(Minecraft::get().GetTheMinecraftObj()), renderText_mid, txtToRender, x, y, color, shadow);
    */

   jclass cls2 = data.env->FindClass("net/minecraft/client/Minecraft");  // try to find the class
        if(cls2 == nullptr) {
            std::cerr << "ERROR: class not found !";
        }
        else {                                  // if class found, continue
            std::cout << "Class MyTest found" << std::endl;
            jmethodID mid = data.env->GetStaticMethodID(cls2, "caca", "()V");  // find method
            if(mid == nullptr)
                std::cerr << "ERROR: method void mymain() not found !" << std::endl;
            else {
                data.env->CallStaticVoidMethod(cls2, mid);                      // call method
                std::cout << std::endl;
            }
    }

    /*if (data.env != nullptr)
	{
		auto class_loader = data.env->FindClass("java/lang/ClassLoader");
		auto get_system_loader =
			data.env->GetStaticMethodID(class_loader, "getSystemClassLoader",
				"()Ljava/lang/ClassLoader;");
		auto system_loader =
			data.env->CallStaticObjectMethod(class_loader, get_system_loader);



        jclass classs = data.env->FindClass("mdr");

        jobject obj = AllocObject(classs);

        

		data.env->DefineClass("net/minecraft/hey", system_loader, obj, sizeof(obj));
		return;
	}*/
}

void inject()
{
	AllocConsole();
	FILE* fIn;
	FILE* fOut;
	freopen_s(&fIn, "conin$", "r", stdin);
	freopen_s(&fOut, "conout$", "w", stdout);
	freopen_s(&fOut, "conout$", "w", stderr);

	std::cout << "[+] Injection Successful!" << std::endl;

    if (attach_jvm() == 84 || handle_jvm() == 84)
        return;
    inject_class();

    std::cout << "[+] Injection dxrtrfcgtfy!" << std::endl;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)inject, nullptr, 0, nullptr);
	return TRUE;
}