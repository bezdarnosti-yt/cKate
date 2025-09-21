#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <imgui_internal.h>

void init_imgui();
void init_glfw();
void loop();
void glfw_render();
void imgui_render();
void shutdown();
void create_windows();

void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const int EDITOR_WIDTH = 1600;
const int EDITOR_HEIGHT = 900;

GLFWwindow* window = nullptr;

ImGuiWindowFlags window_flags = 
        ImGuiWindowFlags_MenuBar | 
        ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;

int main(int, char**){
    spdlog::info("Welcome to cKate!");

    init_glfw();
    init_imgui();
    loop();
    shutdown();

    return 0;
}

void init_imgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void init_glfw() {
    if (!glfwInit()) {
        spdlog::error("GLFW INIT ERROR");
        return;
    } else {
        spdlog::info("GLFW OK");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    glfwSetErrorCallback(error_callback);

    window = glfwCreateWindow(EDITOR_WIDTH, EDITOR_HEIGHT, "cKate", NULL, NULL);
    if (!window) {
        spdlog::error("WINDOW CREATE ERROR");
        shutdown();
        return;
    } else {
        spdlog::info("WINDOW OK");
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("GLAD INIT ERROR");
        shutdown();
        return;
    } else {
        spdlog::info("GLAD OK");
    }

    glViewport(0, 0, EDITOR_WIDTH, EDITOR_HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    printf("%s\n", glGetString(GL_VERSION));
}

void loop() {
    while(!glfwWindowShouldClose(window)) {
        glfw_render();

        glfwPollEvents();

        imgui_render();

        glfwSwapBuffers(window);
    }
}

void glfw_render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void imgui_render() {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::Begin("Main Docking Window", nullptr, window_flags);

    ImGuiID dockspace_id = ImGui::GetID("MainDockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    create_windows();

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void shutdown() {
    glfwTerminate();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    spdlog::info("SHUTDOWN COMPLETE");
}

void error_callback(int error, const char* description) {
    spdlog::error("Error: {}, {}", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)width, (float)height);
}

void create_windows() {
    // Top menu bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit")) { shutdown(); }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    
    // Scene Window
    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoCollapse);
    // Ваш код для сцены
    ImGui::End();

    // Hierarchy Window
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoCollapse);
    // Ваш код для иерархии
    ImGui::End();

    // Browser Window
    ImGui::Begin("Browser", nullptr, ImGuiWindowFlags_NoCollapse);
    // Ваш код для браузера
    ImGui::End();

    // Console Window
    ImGui::Begin("Console", nullptr, ImGuiWindowFlags_NoCollapse);
    // Ваш код для консоли
    ImGui::End();

    // Properties Window
    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoCollapse);
    // Ваш код для свойств
    ImGui::End();
}