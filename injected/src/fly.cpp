#include "../include/epycheat.h"

void sendGroundPacket()
{
    jclass packetPositionClass = data.env->FindClass("net/minecraft/network/play/client/C03PacketPlayer");
    
}

void sendPlayerPacket(jobject Packet)
{
    jclass playerClass = data.env->FindClass("net/minecraft/client/entity/EntityClientPlayerMP");
    jclass playerHandler = data.env->FindClass("net/minecraft/client/network/NetHandlerPlayClient");
    jfieldID fieldQueue = data.env->GetFieldID(playerClass, "sendQueue", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
    jobject queueObject = data.env->GetObjectField(getPlayer(), fieldQueue);
    if (fieldQueue == nullptr) {
        std::cout << "[!] Queue object not found !" << std::endl;
        return;
    }
    jmethodID addToSendQueue = data.env->GetMethodID(playerHandler, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");
    if (addToSendQueue == nullptr) {
        std::cout << "[!] Method addToQueue not found !" << std::endl;
        return;
    }
    data.env->CallVoidMethod(queueObject, addToSendQueue, Packet);
    return;
}

void modifyFlyState()
{
    jclass playerClass = data.env->FindClass("net/minecraft/client/entity/EntityClientPlayerMP");
    jclass playerParentEntity = data.env->FindClass("net/minecraft/entity/player/EntityPlayer");
    jclass pCapabilities = data.env->FindClass("net/minecraft/entity/player/PlayerCapabilities");
    jfieldID fieldID = data.env->GetFieldID(playerParentEntity, "capabilities", "Lnet/minecraft/entity/player/PlayerCapabilities;");
    if (fieldID == nullptr) {
        std::cout << "[!] Error: Flying module is null !" << std::endl;
        return;
    }
    jobject getCapabilities = data.env->GetObjectField(getPlayer(), fieldID);
    if (getCapabilities == nullptr) {
        std::cout << "[!] Error: Flying modulesss is null !" << std::endl;
        return;
    }
    jfieldID allowFly = data.env->GetFieldID(pCapabilities, "allowFlying", "Z");
    if (allowFly == nullptr) {
        std::cout << "[!] Error: Flying module don't find !" << std::endl;
        return;
    }
    jboolean getFlyStatus = data.env->GetBooleanField(getCapabilities, allowFly);
    if (!getFlyStatus) {
        data.env->SetBooleanField(getCapabilities, allowFly, JNI_TRUE);
        sendMessage("Je Fly Mais tkt c une illusion!");
        flyEnabled = 1;
        return;
    } else {
        data.env->SetBooleanField(getCapabilities, allowFly, JNI_FALSE);
        sendMessage("Je ne Fly Plus !");
        flyEnabled = 0;
        return;
    }
}   