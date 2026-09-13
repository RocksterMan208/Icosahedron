#include"shaders.h"
#include"textures.h"
#include"buffers.h"
#include"settings.hpp"
#include"camera.h"
#include"windowFunctions.hpp"
#include"icosphere.h"

#include<iostream>
#include<glm/glm.hpp>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int subdivisions = 1;

void setGLFWHint()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void compileError(const char* type) // Outputs a specific error, does not stop the code from running, just gives a heads up.
{
    std::cout << "Compilation error: " << type << std::endl;
}

int main()
{
    glfwInit(); // Initialise the GLFW code
    setGLFWHint(); // Condensor code
    

    GLFWwindow* window = glfwCreateWindow(screenW, screenH, title, NULL, NULL);
    if (!window) compileError("Window creation");

    glfwMakeContextCurrent(window);
    if(!gladLoadGL()) compileError("GLAD Initialisation");
    glViewport(0, 0, screenW, screenH);

    Shader shaderProgram("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");

    initImGui(window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Icosahedron test(0);
    Camera camera(screenW, screenH, glm::vec3(0.0f, 0.0f, 0.0f));

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        startImGuiFrame(&camera, &subdivisions);

        waitForEscape(window);
        
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();
        
        if (!mouseToggle(window, GLFW_KEY_X)) camera.ProcessInputs(window);

        if(checkChangeF(subdivisions)) 
        {
            test.generate(subdivisions);
            test.uploadToGL();
        }

        glm::mat4 model = glm::mat4(1.0f);

        test.draw();
        camera.Matrix(fov, 0.1f, 100.0f, shaderProgram, "camMatrix", model);
        
        endImGuiFrame();
        glfwSwapBuffers(window);
    }

    imGuiEnd();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}