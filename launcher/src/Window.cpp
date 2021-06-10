#include "Window.h"

#define HOME_BUTTON 1
#define STORE_BUTTON 2
#define LIBRARY_BUTTON 3
#define TUTORIAL_BUTTON 4
#define DOWNLOADS_BUTTON 5
#define SETTINGS_BUTTON 6
#define ACCOUNT_BUTTON 70
#define PROFILE_BUTTON 71
#define SIGNOUT_BUTTON 72
#define EXIT_BUTTON 73

Window* window = nullptr;

Window::Window(void)
{
}

void MenuBase(HWND hwnd)
{
    /*HMENU hmenu = CreateMenu();
    HMENU hstore = CreateMenu();
    HMENU hlibrary = CreateMenu();
    HMENU htutorial = CreateMenu();
    HMENU hdownloads = CreateMenu();
    HMENU hsettings = CreateMenu();
    HMENU haccount = CreateMenu();
 
    AppendMenu(haccount, MF_STRING, PROFILE_BUTTON, L"Profile");
    AppendMenu(haccount, MF_STRING, SIGNOUT_BUTTON, L"Sign Out");
    AppendMenu(haccount, MF_STRING, EXIT_BUTTON, L"Exit");
    AppendMenu(hmenu, MF_STRING, HOME_BUTTON, L"Home");
    AppendMenu(hmenu, MF_STRING, HOME_BUTTON, L"Store");
    AppendMenu(hmenu, MF_STRING, HOME_BUTTON, L"Library");
    AppendMenu(hmenu, MF_STRING, HOME_BUTTON, L"Tutorial");
    AppendMenu(hmenu, MF_STRING, HOME_BUTTON, L"Downloads");
    AppendMenu(hmenu, MF_STRING, HOME_BUTTON, L"Settings");
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)haccount, L"Account");
    SetMenu(hwnd, hmenu);*/
    CreateWindowW(L"Button", L"Home", WS_VISIBLE | WS_CHILD, 50, 105, 100, 25, hwnd, (HMENU)HOME_BUTTON, NULL, NULL);
    CreateWindowW(L"Button", L"Store", WS_VISIBLE | WS_CHILD, 50, 140, 100, 25, hwnd, (HMENU)STORE_BUTTON, NULL, NULL);
    CreateWindowW(L"Button", L"Library", WS_VISIBLE | WS_CHILD, 50, 175, 100, 25, hwnd, (HMENU)LIBRARY_BUTTON, NULL, NULL);
    CreateWindowW(L"Button", L"Tutorial", WS_VISIBLE | WS_CHILD, 50, 205, 100, 25, hwnd, (HMENU)TUTORIAL_BUTTON, NULL, NULL);
    CreateWindowW(L"Button", L"Downloads", WS_VISIBLE | WS_CHILD, 50, 390, 100, 25, hwnd, (HMENU)DOWNLOADS_BUTTON, NULL, NULL);
    CreateWindowW(L"Button", L"Settings", WS_VISIBLE | WS_CHILD, 50, 425, 100, 25, hwnd, (HMENU)SETTINGS_BUTTON, NULL, NULL);
    CreateWindowW(L"Button", L"Account", WS_VISIBLE | WS_CHILD, 50, 460, 100, 25, hwnd, (HMENU)ACCOUNT_BUTTON, NULL, NULL);
}

int CommmandButton_MenuBase(WPARAM wparam, HWND hwnd)
{
    if (wparam == HOME_BUTTON) {
        MessageBeep(MB_OK);
        return (1);
    }
    if (wparam == SIGNOUT_BUTTON || wparam == EXIT_BUTTON) {
        MessageBeep(MB_ICONERROR);
        return (0);
    }
    if (wparam == ACCOUNT_BUTTON) {
        if (!window->open_account) {
            window->b_profile = CreateWindowW(L"Button", L"Profile", WS_VISIBLE | WS_CHILD, 165, 435, 100, 25, hwnd, (HMENU)PROFILE_BUTTON, NULL, NULL);
            window->b_log_out = CreateWindowW(L"Button", L"Log Out", WS_VISIBLE | WS_CHILD, 165, 460, 100, 25, hwnd, (HMENU)SIGNOUT_BUTTON, NULL, NULL);
            window->b_exit = CreateWindowW(L"Button", L"Exit", WS_VISIBLE | WS_CHILD, 165, 485, 100, 25, hwnd, (HMENU)EXIT_BUTTON, NULL, NULL);
        } else {
            DestroyWindow(window->b_profile);
            DestroyWindow(window->b_log_out);
            DestroyWindow(window->b_exit);
        }
        window->open_account = (window->open_account + 1) % 2;
        return (1);
    }
    return (1);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
        case WM_COMMAND: {
            if (!CommmandButton_MenuBase(wparam, hwnd)) {
                window->onDestroy();
                ::PostQuitMessage(0);
            }
            break;
        }
        case WM_CREATE: {
            window->onCreate();
            MenuBase(hwnd);
            break;
        }
        case WM_DESTROY: {
            window->onDestroy();
            ::PostQuitMessage(0);
            break;
        }
        default:
            return ::DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return NULL;
}

bool Window::init(void)
{
    WNDCLASSEX wc;

    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc;
    if (!::RegisterClassEx(&wc))
        return false;
    if (!window)
        window = this;
    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"EpyCheat Launcher", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1050, 580, NULL, NULL, NULL, NULL);
    if (!m_hwnd)
        return false;
    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);
    m_is_run = true;
    window->open_account = 0;
    return true;
}

bool Window::broadcast(void)
{
    MSG msg;

    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    window->onUpdate();
    Sleep(0);
    return true;
}

bool Window::release(void)
{
    if (!::DestroyWindow(m_hwnd))
        return false;
    return true;
}

bool Window::isRun(void)
{
    return (m_is_run);
}

void Window::onCreate(void)
{
}

void Window::onUpdate(void)
{
}

void Window::onDestroy(void)
{
    m_is_run = false;
}

Window::~Window(void)
{
}