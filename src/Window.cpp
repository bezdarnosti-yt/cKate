#include "Window.h"
#include <stdexcept>
#include <algorithm>

Window* Window::instance = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void error_callback(int error, const char* description);

Window::Window() {
    if (!glfwInit()) {
        spdlog::error("GLFW INIT ERROR");
        throw std::runtime_error("Failed to initialize GLFW");
    }
    spdlog::info("GLFW OK");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    glfwSetErrorCallback(error_callback);

    window = glfwCreateWindow(1600, 900, "cKate", NULL, NULL);
    if (!window) {
        spdlog::error("WINDOW CREATE ERROR");
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }
    spdlog::info("WINDOW OK");
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("GLAD INIT ERROR");
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
    spdlog::info("GLAD OK");

    glViewport(0, 0, 1600, 900);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);

    spdlog::info("OpenGL Version: {}", (const char*)glGetString(GL_VERSION));
}

void Window::loop() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void error_callback(int error, const char* description) {
    std::string sanitizedDesc(description ? description : "Unknown error");
    std::replace(sanitizedDesc.begin(), sanitizedDesc.end(), '\n', ' ');
    std::replace(sanitizedDesc.begin(), sanitizedDesc.end(), '\r', ' ');
    spdlog::error("Error: {}, {}", error, sanitizedDesc);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}