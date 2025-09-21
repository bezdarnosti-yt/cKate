#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        spdlog::error("SHADER FILE NOT READ: {}", e.what());
        throw std::runtime_error("Failed to read shader files");
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    checkCompileErrors(m_id, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(m_id);
}

void Shader::use() const {
    glUseProgram(m_id);
}

void Shader::setBool(const std::string& name, bool value) const {
    int location = glGetUniformLocation(m_id, name.c_str());
    if (location != -1) glUniform1i(location, (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    int location = glGetUniformLocation(m_id, name.c_str());
    if (location != -1) glUniform1i(location, value);
}

void Shader::setFloat(const std::string& name, float value) const {
    int location = glGetUniformLocation(m_id, name.c_str());
    if (location != -1) glUniform1f(location, value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    int location = glGetUniformLocation(m_id, name.c_str());
    if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    int location = glGetUniformLocation(m_id, name.c_str());
    if (location != -1) glUniform3fv(location, 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
    int location = glGetUniformLocation(m_id, name.c_str());
    if (location != -1) glUniform3f(location, x, y, z);
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::string sanitizedLog(infoLog);
            std::replace(sanitizedLog.begin(), sanitizedLog.end(), '\n', ' ');
            std::replace(sanitizedLog.begin(), sanitizedLog.end(), '\r', ' ');
            spdlog::error("SHADER COMPILATION ERROR {} : {}", type, sanitizedLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::string sanitizedLog(infoLog);
            std::replace(sanitizedLog.begin(), sanitizedLog.end(), '\n', ' ');
            std::replace(sanitizedLog.begin(), sanitizedLog.end(), '\r', ' ');
            spdlog::error("SHADER LINKING ERROR {} : {}", type, sanitizedLog);
        }
    }
}
