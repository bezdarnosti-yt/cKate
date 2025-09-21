#pragma once

#include "Window.h"
#include "Input.h"
#include "Graphics.h"
#include "Include.h"

class Application {
public:
    Application();
    void Run();
private:
    Window* c_window = nullptr;
    Input* c_input = nullptr;
    Graphics* c_graphics = nullptr;
};