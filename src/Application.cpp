#include "Application.h"
#include <stdexcept>
#include <chrono>
#include <thread>

Application::Application() {
    c_window = Window::getInstance();
    if (!c_window) throw std::runtime_error("Failed to initialize Window");
    
    c_input = Input::getInstance();
    if (!c_input) throw std::runtime_error("Failed to initialize Input");
    
    c_graphics = Graphics::getInstance();
    if (!c_graphics) throw std::runtime_error("Failed to initialize Graphics");
}

void Application::Run() {
    spdlog::info("Welcome to cKate!");
    const auto targetFrameTime = std::chrono::microseconds(16667); // ~60 FPS
    auto lastTime = std::chrono::high_resolution_clock::now();
    
    while(!glfwWindowShouldClose(c_window->window)) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = currentTime - lastTime;
        
        c_window->loop();
        c_input->loop();
        c_graphics->loop();
        glfwPollEvents();
        
        if (deltaTime < targetFrameTime) {
            std::this_thread::sleep_for(targetFrameTime - deltaTime);
        }
        lastTime = std::chrono::high_resolution_clock::now();
    }
}