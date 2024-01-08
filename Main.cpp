//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <Logger.h>
//
//int main()
//{
//	// Initialize GLFW
//	glfwInit();
//
//	// Tell GLFW what version of OpenGL we are using 
//	// In this case we are using OpenGL 3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	// Tell GLFW we are using the CORE profile
//	// So that means we only have the modern functions
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
//	// Vertex Shader source code
//	const char* vertexShaderSource = "#version 330 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"void main()\n"
//		"{\n"
//		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		"}\0";
//	//Fragment Shader source code
//	const char* fragmentShaderSource = "#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"void main()\n"
//		"{\n"
//		"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
//		"}\n\0";
//
//	
//	GLfloat vertices[] =
//	{
//		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
//		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
//		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
//	};
//
//	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
//	GLFWwindow* window = glfwCreateWindow(800, 600, "Project OpenGL", NULL, NULL);
//	// Error check if the window fails to create
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	// Introduce the window into the current context
//	glfwMakeContextCurrent(window);
//
//
//	//Load GLAD so it configures OpenGL
//	gladLoadGL();
//	// Specify the viewport of OpenGL in the Window
//	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
//	glViewport(0, 0, 800, 600);
//
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//	GLuint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//
//	GLuint VAO, VBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//	// Specify the color of the background
//	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//	// Clean the back buffer and assign the new color to it
//	glClear(GL_COLOR_BUFFER_BIT);
//	// Swap the back buffer with the front buffer
//	glfwSwapBuffers(window);
//
//
//
//	// Main while loop
//	while (!glfwWindowShouldClose(window))
//	{
//		// Specify the color of the background
//		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//		// Clean the back buffer and assign the new color to it
//		glClear(GL_COLOR_BUFFER_BIT);
//		// Tell OpenGL which Shader Program we want to use
//		glUseProgram(shaderProgram);
//		// Bind the VAO so OpenGL knows to use it
//		glBindVertexArray(VAO);
//		// Draw the triangle using the GL_TRIANGLES primitive
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		// Swap the back buffer with the front buffer
//		glfwSwapBuffers(window);
//		// Take care of all GLFW events
//		glfwPollEvents();
//	}
//
//	/*Logger::getInstance().log("Acesta este un mesaj de info.", Logger::LogLevel::INFO);
//	Logger::getInstance().log("Acesta este un mesaj de warning.", Logger::LogLevel::WARNING);
//	Logger::getInstance().log("Acesta este un mesaj de eroare.", Logger::LogLevel::ERROR);*/
//
//	// Delete window before ending the program
//	glfwDestroyWindow(window);
//	// Terminate GLFW before ending the program
//	glfwTerminate();
//	return 0;
//}
//
//
//


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

