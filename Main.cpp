#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Sphere.h"
#include "Camera.h"
#include "Logger.h"
#include "Table.h"

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Sphere Example", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 800, 600);

    glEnable(GL_DEPTH_TEST);

    // Initialize camera
    Camera camera(800, 600, glm::vec3(0.5f, 0.5f, 30.0f));

    // Initialize shader
    Shader shaderProgram("default.vert", "default.frag");

    // Create sphere
    //Sphere mySphere(1.0f, 20, 16);
    //Sphere mySphere(1.0f, 40, 32);  // Mărim numărul de meridiane și paralele

    Sphere mySphere(8.0f, 80, 64);  // Mărește raza sferei

    // Create table
    Table myTable(10.0f);

    // Înainte de bucla while
    shaderProgram.Activate();

    // Setează valorile pentru iluminare
    shaderProgram.SetVector3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f)); // Culoarea luminii
    shaderProgram.SetVector3("lightPosition", glm::vec3(-100.0f, 1.0f, 1.0f)); // Poziția luminii

    Logger::getInstance().log("Acesta este un mesaj de info.", Logger::LogLevel::INFO);
    Logger::getInstance().log("Acesta este un mesaj de warning.", Logger::LogLevel::WARNING);
    Logger::getInstance().log("Acesta este un mesaj de eroare.", Logger::LogLevel::ERROR);  

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 1.0f, 100.0f);

        shaderProgram.Activate();
        shaderProgram.SetVector3("sphereColor", glm::vec3(1.0f, 0.0f, 0.0f));  // Setați culoarea sferei
        
        camera.Matrix(shaderProgram, "camMatrix");

        // Draw the sphere
        mySphere.draw();

        // Draw the table
        //myTable.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

