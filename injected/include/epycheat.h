#pragma once

#include <Windows.h>
#include <iostream>
#include "jni.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <commdlg.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "minhook.h"

#ifndef _EPYCHEAT_H
#define _EPYCHEAT_H

extern int flyEnabled;

struct data_t {
    JavaVM *jvm;
    JNIEnv *env;
	HWND hWnd;
	HMODULE hModule;
	void* hook;
	int close;
	int display;
	GLint *viewport;
	GLfloat *modelView;
	GLfloat *projection;
};

extern data_t data;

int HandleJvm(void);
int AttachJvm(void);
void AttachConsole(void);
void DetachConsole(void);

void SetupOrtho(void);
void RestoreGL(void);
GLint* Get_Viewport(void);
GLfloat* Get_ModelView(void);
GLfloat* Get_Projection(void);

void DrawSquare( GLfloat x, GLfloat y, GLfloat sidelength, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha );
void DrawRect( GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha );
void DrawLine(int x0, int y0, int z0, int x1, int y1, int z1);

int Hook(void);

jobject GetMc(void);
void ModifyFlyState(void);
jobject GetPlayer(void);
void SendChatMessage(const char *message);
void SetPlayerOnGround(void);
void DrawHUD(void);
jobject GetWorld();
jobjectArray GetNearbyEntity();

void PlayerEsp2D(void);
void PlayerEsp3D(void);


#endif