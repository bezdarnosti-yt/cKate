#include "Input.h"
#include "Graphics.h"
#include <stdexcept>

void processInput(GLFWwindow* _window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Input* Input::instance = nullptr;

Input::Input() {
    auto windowInstance = Window::getInstance();
    if (!windowInstance || !windowInstance->window) {
        throw std::runtime_error("Failed to get valid window instance");
    }
    window = windowInstance->window;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
}

void Input::loop() {
    if (!window) return;
    processInput(window);
}

void processInput(GLFWwindow* _window) {
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
    
    auto graphics = Graphics::getInstance();
    if (graphics) {
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
            graphics->camera.processKeyboard(GLFW_KEY_W, 0.016f);
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
            graphics->camera.processKeyboard(GLFW_KEY_S, 0.016f);
        if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
            graphics->camera.processKeyboard(GLFW_KEY_A, 0.016f);
        if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
            graphics->camera.processKeyboard(GLFW_KEY_D, 0.016f);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static float lastX = 800.0f;
    static float lastY = 450.0f;
    static bool firstMouse = true;
    
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    auto graphics = Graphics::getInstance();
    if (graphics) {
        graphics->camera.processMouseMovement(xoffset, yoffset);
    }
}