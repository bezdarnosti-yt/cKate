#pragma once

#include "Include.h"

class Window {
public:
    // Singleton
    static Window* getInstance() {
        if (instance == nullptr)
            instance = new Window();
        return instance;
    }

    GLFWwindow* window;
    void loop();
private:
    // Singleton
    static Window* instance;
    Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
};