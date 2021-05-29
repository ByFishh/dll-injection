#pragma once
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
	jclass launch = env->FindClass("net/minecraft/launchwrapper/Launch");
	cout << launch << endl;
	jfieldID sfid = env->GetStaticFieldID(launch, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
	cout << sfid << endl;
	jobject classLoader = env->GetStaticObjectField(launch, sfid);
	cout << classLoader << endl;

	return classLoader;
}

jclass getObject(JNIEnv* env, const char* className)
{
	jstring name = env->NewStringUTF(className);
	jobject classLoader = getClassLoader(env);
	jmethodID mid = env->GetMethodID(env->GetObjectClass(classLoader), "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	cout << mid << endl;
	return (jclass)env->CallObjectMethod(classLoader, mid, name);
	env->DeleteLocalRef(name);
}

jobject getMC(JNIEnv* env)
{
	jclass mcClass = getObject(env, "net.minecraft.client.Minecraft");
	cout << "MCClass: " << mcClass << endl;
	jmethodID smid = env->GetStaticMethodID(mcClass, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
	cout << "SMID: " << smid << endl;
	return env->CallStaticObjectMethod(mcClass, smid);
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
	std::cout << "This works" << std::endl;
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