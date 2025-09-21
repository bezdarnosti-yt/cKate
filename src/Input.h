#pragma once

#include "Window.h"
#include "Include.h"

class Input {
public:
    // Singleton
    static Input* getInstance() {
        if (instance == nullptr)
            instance = new Input();
        return instance;
    }

    void loop();
private:
    GLFWwindow* window;
    // Singleton
    static Input* instance;
    Input();
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;
};