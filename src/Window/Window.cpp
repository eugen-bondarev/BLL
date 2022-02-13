#include "Window.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <stdexcept>

static void ImGuiInit(GLFWwindow* handle)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(handle, true);
    ImGui_ImplOpenGL3_Init();
}

static void ImGuiShutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

static void ImGuiBeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

static void ImGuiEndFrame(GLFWwindow* handle)
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Render();
    int viewportWidth, viewportHeight;
    glfwGetFramebufferSize(handle, &viewportWidth, &viewportHeight);
    glViewport(0, 0, viewportWidth, viewportHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

static void GetMonitorResolution(size_t& width, size_t& height)
{    
    const GLFWvidmode* mode{ glfwGetVideoMode(glfwGetPrimaryMonitor()) };
    width = static_cast<size_t>(mode->width);
    height = static_cast<size_t>(mode->height);
}

Window::Window(const size_t width, const size_t height)
{
    if (!glfwInit())
    {
        throw std::runtime_error{ "GLFW-Initialisierung fehlgeschlagen." };
    }

    glfwDefaultWindowHints();
    size_t finalWidth {width}, finalHeight {height};
    if (width == 0 || height == 0) { GetMonitorResolution(finalWidth, finalHeight); }
    handle = glfwCreateWindow(finalWidth, finalHeight, "E. Bondarev, BLL", nullptr, nullptr);
    if (width == 0 || height == 0) { glfwMaximizeWindow(handle); }
    glfwMakeContextCurrent(handle);
    glfwSwapInterval(1);
    glfwMaximizeWindow(handle);

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error{ "GLEW-Initialisierung fehlgeschlagen." };
    }

    ImGuiInit(handle);
}

Window::~Window()
{
    ImGuiShutdown();
    glfwDestroyWindow(handle);
    glfwTerminate();
}

bool Window::IsRunning() const
{
    return !glfwWindowShouldClose(handle);
}

void Window::BeginFrame()
{
    glfwPollEvents();
    ImGuiBeginFrame();
}

void Window::EndFrame()
{
    ImGuiEndFrame(handle);
    glfwSwapBuffers(handle);
}
