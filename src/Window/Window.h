#ifndef __Window_Window_h__
#define __Window_Window_h__

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

class Window
{
public:
    Window(const size_t width = 0u, const size_t height = 0u);
   ~Window();

    bool IsRunning() const;

    void BeginFrame();
    void EndFrame();

private:
    GLFWwindow* handle;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
};

#endif