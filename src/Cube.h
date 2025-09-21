#pragma once

#include "Shader.h"
#include "Include.h"

class Cube {
public:
    Cube();
    ~Cube();

    void draw() const;
    void setModelMatrix(const glm::mat4& model);
    glm::mat4 getModelMatrix() const;

    Shader shader;
private:
    unsigned int m_VAO = 0, m_VBO = 0;
    glm::mat4 m_model;
    static const float vertices[];

    void setupMesh();
};