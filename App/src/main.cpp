#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Core.h"

// Simple vertex and fragment shaders
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec4 vertexColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = vec4(aColor, 1.0);
}
)";

const char* fragShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec4 vertexColor;

void main() {
    FragColor = vertexColor;
}
)";




// Error checking helper
void checkOpenGLError(const std::string& location) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error at " << location << ": " << error << std::endl;
    }
}

int main() {
    // Initialize GLFW and create window
    GLFWwindow* window = Local::Init();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Compile vertex shader
    Local::Shader vertexShader = Local::Shader(GL_VERTEX_SHADER);
    vertexShader.ShaderSource(1, &vertexShaderSource, nullptr);
    vertexShader.Compile();

    // Compile fragment shader
    Local::Shader fragShader = Local::Shader(GL_FRAGMENT_SHADER);
    fragShader.ShaderSource(1, &fragShaderSource, nullptr);
    fragShader.Compile();

    // Create shader program
    Local::ShaderProgram shaderProgram = Local::ShaderProgram::ShaderProgram();
    shaderProgram.attachShader(vertexShader.ID);
    shaderProgram.attachShader(fragShader.ID);
    shaderProgram.Link();

    shaderProgram.Use();
    // Delete shaders after linking
    vertexShader.Delete();
    fragShader.Delete();

    Local::Box rect = Local::Box::Box({ 1.0f,0.1f }, { -0.5f, -0.05f });
    Local::Box rect2 = Local::Box::Box({ 0.1f, 1.0f }, { -0.05f, -0.5f });
    Local::Box rect3 = Local::Box::Box({ 0.1f, 0.45f }, { -0.5f, 0.05f });
    Local::Box rect4 = Local::Box::Box({ 0.1f, 0.45f }, { 0.4f, -0.5f });
    Local::Box rect5 = Local::Box::Box({ 0.45f, 0.1f }, { 0.05f, 0.4f });
    Local::Box rect6 = Local::Box::Box({ 0.45f, 0.1f }, { -0.5f, -0.5f });
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        rect.Draw();
        rect2.Draw();
        rect3.Draw();
        rect4.Draw();
        rect5.Draw();
        rect6.Draw();
        checkOpenGLError("Drawing rect");

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up

    shaderProgram.Delete();

    glfwTerminate();
    return 0;
}
