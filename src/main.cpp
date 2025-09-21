#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

void init_glfw();
void loop();
void glfw_render();
void shutdown();

void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const int EDITOR_WIDTH = 1600;
const int EDITOR_HEIGHT = 900;

GLFWwindow* window = nullptr;

int main(int, char**){
    spdlog::info("Welcome to cKate!");

    init_glfw();
    loop();
    shutdown();

    return 0;
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

        glfwSwapBuffers(window);
    }
}

void glfw_render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void shutdown() {
    glfwTerminate();
    spdlog::info("SHUTDOWN COMPLETE");
}

void error_callback(int error, const char* description) {
    spdlog::error("Error: {}, {}", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}