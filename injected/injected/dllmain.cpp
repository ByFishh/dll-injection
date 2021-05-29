//#include "function.h"
#include "pch.h"
#include <Windows.h>
#include <jni.h>
#include <iostream>
#include <string>
#include <thread>

jobject mc;
jobject thePlayer;
jobject theWorld;

using namespace std;
jobject getClassLoader(JNIEnv* env)
{
	std::cout << "get cl 1" << std::endl;
	jclass launch = env->FindClass("Lnet/minecraft/launchwrapper/Launch;");
	std::cout << "get cl 2" << std::endl;
	cout << launch << endl;
	std::cout << "get cl 3" << std::endl;
	jfieldID sfid = env->GetStaticFieldID(launch, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
	std::cout << "get cl 4" << std::endl;
	cout << sfid << endl;
	std::cout << "get cl 5" << std::endl;
	jobject classLoader = env->GetStaticObjectField(launch, sfid);
	std::cout << "get cl 6" << std::endl;
	cout << classLoader << endl;
	std::cout << "get cl 7" << std::endl;

	return classLoader;
}

jclass getObject(JNIEnv* env, const char* className)
{
	std::cout << "get obj 1" << std::endl;
	jstring name = env->NewStringUTF(className);
	std::cout << "get obj 2" << std::endl;
	jobject classLoader = getClassLoader(env);
	std::cout << "get obj 3" << std::endl;
	jmethodID mid = env->GetMethodID(env->GetObjectClass(classLoader), "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	std::cout << "get obj 4" << std::endl;
	cout << mid << endl;
	std::cout << "get obj 5" << std::endl;
	return (jclass)env->CallObjectMethod(classLoader, mid, name);
	std::cout << "get obj 6" << std::endl;
	env->DeleteLocalRef(name);
	std::cout << "get obj 7" << std::endl;
}

jobject getMC(JNIEnv* env)
{
	std::cout << "get mc 1" << std::endl;
	std::cout << env << std::endl;
	jclass mcClass = getObject(env, "()Lnet/minecraft/client/Minecraft;");
	std::cout << "get mc 2" << std::endl;
	cout << "MCClass: " << mcClass << endl;
	std::cout << "get mc 3" << std::endl;
	jmethodID smid = env->GetStaticMethodID(mcClass, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
	std::cout << "get mc 4" << std::endl;
	cout << "SMID: " << smid << endl;
	std::cout << "get mc 5" << std::endl;
	return env->CallStaticObjectMethod(mcClass, smid);
	std::cout << "get mc 6" << std::endl;
}

int getDW(JNIEnv* env)
{
	cout << "Minecraft instance: " << endl;
	jfieldID fid = env->GetFieldID(env->GetObjectClass(mc), "displayWidth", "I");
	return env->GetIntField(mc, fid);
}

int getDH(JNIEnv* env)
{
	cout << "Minecraft instance: " << endl;
	jfieldID fid = env->GetFieldID(env->GetObjectClass(mc), "displayHeight", "I");
	return env->GetIntField(mc, fid);
}

jobject getPlayer(JNIEnv* env)
{
	jfieldID fid = env->GetFieldID(env->GetObjectClass(mc), "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
	return env->GetObjectField(mc, fid);
}

jobject getWorld(JNIEnv* env)
{
	jfieldID fid = env->GetFieldID(env->GetObjectClass(mc), "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
	return env->GetObjectField(mc, fid);
}

void postPreInit(JNIEnv* env)
{
	std::cout << "This worksdfg" << std::endl;
	mc = getMC(env);
	std::cout << "This works" << std::endl;
	mc = env->NewGlobalRef(mc);
	std::cout << "This works 2" << std::endl;
	thePlayer = getPlayer(env);
	std::cout << "This works 3" << std::endl;
	thePlayer = env->NewGlobalRef(thePlayer);
	std::cout << "This works 4" << std::endl;
	theWorld = getWorld(env);
	std::cout << "This works 5" << std::endl;
	theWorld = env->NewGlobalRef(theWorld);
	std::cout << "This works 6" << std::endl;
}

float getRY(JNIEnv* env)
{
	jfieldID fid = env->GetFieldID(env->GetObjectClass(thePlayer), "rotationYaw", "F");
	return env->GetFloatField(thePlayer, fid);
}

void setRY(JNIEnv* env, float value)
{
	jfieldID fid = env->GetFieldID(env->GetObjectClass(thePlayer), "rotationYaw", "F");
	return env->SetFloatField(thePlayer, fid, value);
}

void cleanup(JNIEnv* env)
{
	env->DeleteGlobalRef(mc);
	env->DeleteGlobalRef(thePlayer);
	env->DeleteGlobalRef(theWorld);
}


//
//
//

typedef jint(*hJNI_GetCreatedJavaVMs)(JavaVM** vmBuf, jsize bufLen, jsize* nVMs);

hJNI_GetCreatedJavaVMs oJNI_GetCreatedJavaVMs;

HMODULE jvmHandle;
FARPROC func_JNI_GetCreatedJavaVMs;
JavaVM* jvm;
JNIEnv* jenv;

DWORD WINAPI update(LPVOID lpParam)
{
    JNIEnv* env = static_cast<JNIEnv*>(lpParam);

    cout << getDW(env) << endl;

    return 0;
}

void start(JNIEnv* env)
{
    HANDLE updateT;
}

void init()
{
    jvmHandle = GetModuleHandleA("jvm.dll");
    func_JNI_GetCreatedJavaVMs = GetProcAddress(jvmHandle, "JNI_GetCreatedJavaVMs");
    oJNI_GetCreatedJavaVMs = (hJNI_GetCreatedJavaVMs)func_JNI_GetCreatedJavaVMs;
    jint returnOF = oJNI_GetCreatedJavaVMs(&jvm, 1, NULL);

    jint returnOf1 = jvm->AttachCurrentThread((void**)&jenv, NULL);
	
    if (jenv != nullptr)
    {
        postPreInit(jenv);
        start(jenv);
        cleanup(jenv);
    }
    if (jenv->ExceptionCheck())
    {
        jenv->ExceptionDescribe();
    }
    jvm->DetachCurrentThread();
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        init();
        //case DLL_PROCESS_DETACH:
        //case DLL_THREAD_ATTACH:
        //case DLL_THREAD_DETACH:
    }
}