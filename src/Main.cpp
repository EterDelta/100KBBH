#include <glad/gl.h>
#include <windows.h>
#include <chrono>
#include "1KBBH/Game.h"

LRESULT CALLBACK windowProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
    }
    return DefWindowProc(windowHandle, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, PTSTR cmdLine, int cmdShow) {
    WNDCLASSEX windowClass;

    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = windowProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = instance;
    windowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = "100KBBH";
    windowClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    RegisterClassEx(&windowClass);

    HWND windowHandle = CreateWindowEx(0, "100KBBH", "100KBBH", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 512, 512, nullptr, nullptr, instance, nullptr);

    PIXELFORMATDESCRIPTOR formatDescriptor;
    ZeroMemory(&formatDescriptor, sizeof(formatDescriptor));
    formatDescriptor.nSize = sizeof(formatDescriptor);
    formatDescriptor.nVersion = 1;
    formatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    formatDescriptor.iPixelType = PFD_TYPE_RGBA;
    formatDescriptor.cColorBits = 24;
    formatDescriptor.cDepthBits = 16;
    formatDescriptor.iLayerType = PFD_MAIN_PLANE;

    HDC deviceContext = GetDC(windowHandle);
    int format = ChoosePixelFormat(deviceContext, &formatDescriptor);
    SetPixelFormat(deviceContext, format, &formatDescriptor);

    HGLRC renderContext = wglCreateContext(deviceContext);
    wglMakeCurrent(deviceContext, renderContext);

    gladLoaderLoadGL();

    ShowWindow(windowHandle, cmdShow);

    Game& game = Game::getInstance();
    game.init();

    MSG msg;
    auto prevFrameTime = std::chrono::system_clock::now();
    auto frameTime = std::chrono::system_clock::now();
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        frameTime = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedFrameTime = frameTime - prevFrameTime;
        float deltaTime = elapsedFrameTime.count();

        if (GetForegroundWindow() == windowHandle) {
            for (int i = 0; i < 256; i++) {
                game.inputs[i] = GetAsyncKeyState(i);
            }
        } else {
            for (int i = 0; i < 256; i++) {
                game.inputs[i] = false;
            }
        }
        game.update(deltaTime);
        game.draw();

        prevFrameTime = frameTime;

        SwapBuffers(deviceContext);
    }

    gladLoaderUnloadGL();

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(renderContext);
    ReleaseDC(windowHandle, deviceContext);

    DestroyWindow(windowHandle);

    return msg.wParam;
}
