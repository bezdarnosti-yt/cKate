#pragma once

#include "Include.h"
#include "Cube.h"
#include "Camera.h"

class Graphics {
public:
    // Singleton
    static Graphics* getInstance() {
        if (instance == nullptr)
            instance = new Graphics();
        return instance;
    }

    void loop();
    
    Camera camera;
private:
    Cube cube;
    // Singleton
    static Graphics* instance;
    Graphics();
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
};