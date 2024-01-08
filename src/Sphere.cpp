#include "Sphere.h"

#include <cmath>
#include <glad/glad.h>
#include <iostream>

//Sphere::Sphere(float radius, unsigned int rings, unsigned int sectors, Shader& shaderProgram)
//    : radius(radius), rings(rings), sectors(sectors), shaderProgram(shaderProgram) {
//    generateSphere();
//}

Sphere::Sphere(float radius, unsigned int rings, unsigned int sectors)
    : radius(radius), rings(rings), sectors(sectors) {
    generateSphere();

}
Sphere::~Sphere()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

//void Sphere::setLightColor(const glm::vec3& color) {
//    shaderProgram.SetVector3("lightColor", color);
//
//}
void Sphere::draw() {
    //shaderProgram.Activate();
    //setLightColor(glm::vec3(1.0f, 1.0f, 1.0f));  // Setăm culoarea luminii la alb

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Sphere::generateSphere() {
    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);
    int r, s;

    vertices.resize(rings * sectors * 3);
    std::vector<float>::iterator v = vertices.begin();
    for (r = 0; r < rings; r++)
        for (s = 0; s < sectors; s++) {
            float const y = sin(-M_PI_2 + M_PI * r * R);
            float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;
        }

    indices.resize(rings * sectors * 6);
    std::vector<unsigned int>::iterator i = indices.begin();
    for (r = 0; r < rings - 1; r++)
        for (s = 0; s < sectors - 1; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s + 1);
            *i++ = (r + 1) * sectors + (s + 1);

            *i++ = (r + 1) * sectors + (s + 1);
            *i++ = (r + 1) * sectors + s;
            *i++ = r * sectors + s;
        }

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    /*for (auto& s : vertices)
        std::cout << s << " ";*/
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}