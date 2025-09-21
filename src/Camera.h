#pragma once

#include "Include.h"

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f));
    
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    
    void processKeyboard(int key, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
    
    glm::vec3 position;
    
private:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float fov;
    
    void updateCameraVectors();
};