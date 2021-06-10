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

struct data_t {
    JavaVM *jvm;
    JNIEnv *env;
	HWND hWnd;
	HMODULE hModule;
	void* hook;
	int close;
	int display;
};

extern data_t data;

int HandleJvm(void);
int AttachJvm(void);
void AttachConsole(void);
void DetachConsole(void);

void SetupOrtho(void);
void RestoreGL(void);

void Draw( GLfloat x, GLfloat y, GLfloat sidelength, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha );

int Hook(void);

#endif