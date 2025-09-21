#include "Graphics.h"

Graphics* Graphics::instance = nullptr;

Graphics::Graphics() {

}

void Graphics::loop() {
    static int frameCount = 0;
    if (frameCount++ % 60 == 0) {
        spdlog::info("Camera pos: {:.1f}, {:.1f}, {:.1f}", camera.position.x, camera.position.y, camera.position.z);
    }
    
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();
    
    cube.shader.use();
    cube.shader.setMat4("model", model);
    cube.shader.setMat4("view", view);
    cube.shader.setMat4("projection", projection);
    cube.draw();
}