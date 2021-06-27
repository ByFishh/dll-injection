#include "../include/epycheat.h"

double GetX(jobject entity)
{
    jclass entityClass = data.env->FindClass("net/minecraft/entity/Entity");
    jfieldID fid = data.env->GetFieldID(entityClass, "posX", "D");

    return data.env->GetDoubleField(entity, fid);
}

double GetY(jobject entity)
{
    jclass entityClass = data.env->FindClass("net/minecraft/entity/Entity");
    jfieldID fid = data.env->GetFieldID(entityClass, "posY", "D");

    return data.env->GetDoubleField(entity, fid);
}

double GetZ(jobject entity)
{
    jclass entityClass = data.env->FindClass("net/minecraft/entity/Entity");
    jfieldID fid = data.env->GetFieldID(entityClass, "posZ", "D");

    return data.env->GetDoubleField(entity, fid);
}

jobject GetBoundingBox(jobject entity)
{
    jclass entityClass = data.env->FindClass("net/minecraft/entity/Entity");
    jfieldID fid = data.env->GetFieldID(entityClass, "boundingBox", "Lnet/minecraft/util/AxisAlignedBB;");
    return data.env->GetObjectField(entity, fid);
}

void GetBCoord(jobject box)
{
    jclass entityClass = data.env->FindClass("net/minecraft/util/AxisAlignedBB");
    jfieldID fidminX = data.env->GetFieldID(entityClass, "minX", "D");
    double minX = data.env->GetDoubleField(box, fidminX);
    jfieldID fidminY = data.env->GetFieldID(entityClass, "minY", "D");
    double minY = data.env->GetDoubleField(box, fidminY);
    jfieldID fidminZ = data.env->GetFieldID(entityClass, "minZ", "D");
    double minZ = data.env->GetDoubleField(box, fidminZ);

    jfieldID fidmaxX = data.env->GetFieldID(entityClass, "maxX", "D");
    double maxX = data.env->GetDoubleField(box, fidmaxX);
    jfieldID fidmaxY = data.env->GetFieldID(entityClass, "maxY", "D");
    double maxY = data.env->GetDoubleField(box, fidmaxY);
    jfieldID fidmaxZ = data.env->GetFieldID(entityClass, "maxZ", "D");
    double maxZ = data.env->GetDoubleField(box, fidmaxZ);

    std::cout << "minX: " << minX << " minY: " << minY << " minZ: " << minZ << std::endl;
    std::cout << "maxX: " << maxX << " maxY: " << maxY << " maxZ: " << maxZ << std::endl;
    std::cout << std::endl;
}

void DrawBoundingBox(jobject entity)
{
    DrawLine(0, 0, 0, 0, 0, 0);
}

void PlayerEsp2D(void)
{
    
}

void PlayerEsp3D(void)
{
    jobjectArray entity_list = GetNearbyEntity();
    size_t len = data.env->GetArrayLength(entity_list);
    
    for (int i = 0; i != len; i++) {
        jobject player = data.env->GetObjectArrayElement(entity_list, i);
        DrawBoundingBox(player);
    }
}

void BlockEsp(void)
{
    
}