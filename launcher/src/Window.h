#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	bool init();
	bool broadcast();
	bool release();
	bool isRun();
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	~Window();
	int menu_created;
	int open_account;
	HWND b_profile;
	HWND b_log_out;
	HWND b_exit;
protected:
	HWND m_hwnd;
	bool m_is_run;
};