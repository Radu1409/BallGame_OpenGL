#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // Citim codul sursă din fișiere
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Asigurăm că ifstream poate arunca excepții
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Deschidem fișierele
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // Citim conținutul fișierelor în fluxuri
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Închidem fișierele
        vShaderFile.close();
        fShaderFile.close();

        // Convertim fluxurile în șiruri
        //vertexCode = vShaderStream.str();
        //fragmentCode = fShaderStream.str();

        vertexCode = readShaderFile(vertexPath);
        fragmentCode = readShaderFile(fragmentPath);

    }
    catch (std::ifstream::failure& e) {
        std::cout << "Eroare la citirea shader-ului" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    std::cout << vShaderCode << " --- " << fShaderCode << std::endl;
    // Compilăm shader-urile
    unsigned int vertex, fragment;

    

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Program Shader
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // Ștergem shader-urile, deoarece acestea sunt deja incluse în program
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

std::string Shader::readShaderFile(const char* filePath) {
    std::ifstream shaderFile(filePath, std::ios::in | std::ios::binary);
    if (shaderFile) {
        std::ostringstream contents;
        contents << shaderFile.rdbuf();
        shaderFile.close();
        std::string result = contents.str();

        // Verificăm și eliminăm caracterele BOM (Byte Order Mark)
        if (!result.empty() && result[0] == '\xEF' && result[1] == '\xBB' && result[2] == '\xBF') {
            result.erase(0, 3);
        }

        return result;
    }

    // Dacă întâmpinăm o problemă la citirea fișierului, puteți trata eroarea aici
    throw std::runtime_error("Eroare la citirea shader-ului");
}

void Shader::Activate() {
    glUseProgram(ID);

    GLint linkSuccess;
    glGetProgramiv(ID, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess) {
        GLchar infoLog[512];
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Eroare la linkarea programului shader:\n" << infoLog << std::endl;
    }
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

void Shader::SetInt(const char* name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetFloat(const char* name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVector3(const char* name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
}


// Adăugăm o metodă pentru a seta poziția luminii
void Shader::SetLightPosition(const glm::vec3& position) const {
    SetVector3("lightPosition", position);
}


void Shader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "Eroare de compilare a shader-ului de tip " << type << "\n" << infoLog << "\n";
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "Eroare la legarea programului shader-ului de tip " << type << "\n" << infoLog << "\n";
        }
    }

}
