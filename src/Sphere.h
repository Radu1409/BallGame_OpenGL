#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 (M_PI / 2.0)
#endif

typedef unsigned int GLuint;

class Sphere {
public:
    //Sphere(float radius, unsigned int rings, unsigned int sectors, Shader& shaderProgram);
    Sphere(float radius, unsigned int rings, unsigned int sectors);
    ~Sphere();

    //void setLightColor(const glm::vec3& color);
    void draw();

private:
    void generateSphere();

    float radius;
    unsigned int rings;
    unsigned int sectors;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    //Shader& shaderProgram;

    GLuint vbo, vao, ebo;
};
#endif
