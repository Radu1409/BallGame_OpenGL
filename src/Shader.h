#ifndef SHADER_H
#define SHADER_H


#include <string>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef unsigned int GLuint;

class Shader {
public:
    // Program ID
    GLuint ID;

    // Constructor citind și construind shader-urile
    Shader(const char* vertexPath, const char* fragmentPath);

    // Folosim programul
    void Activate();

    void Delete();

    // Setăm uniforma în shader
    void SetInt(const char* name, int value) const;
    void SetFloat(const char* name, float value) const;
    void SetMatrix4(const char* name, const glm::mat4& matrix) const;

    void SetVector3(const char* name, const glm::vec3& value) const;
    void SetLightPosition(const glm::vec3& position) const;

private:
    // Verificăm erorile de compilare sau legare a shader-ului
    void checkCompileErrors(GLuint shader, std::string type);

    std::string readShaderFile(const char* filePath);

};

#endif // SHADER_H
