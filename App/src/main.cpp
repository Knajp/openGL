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

double NormalizeYCoordinate(double coordinate) { return 1 - (2 * coordinate) / 800; }
double NormalizeXCoordinate(double coordinate) { return (2 * coordinate) / 800 - 1; }


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

    Local::Box rect = Local::Box::Box({ 2.0f, 0.3f }, { -1.0f, 0.7f }, {0.5f, 0.5f, 0.5f});
    Local::Box rect2 = Local::Box::Box({ 0.5f, 1.7f }, { -1.0f, -1.0f }, { 0.7f, 0.7f, 0.7f });

    Local::Box button1 = Local::Box::Box({ 0.25f, 0.25f }, { -0.3f, 0.2f }, { 0.5f, 0.5f, 0.5f }, "1");
    Local::Box button2 = Local::Box::Box({ 0.25f, 0.25f }, {  0.0f, 0.2f }, { 0.5f, 0.5f, 0.5f }, "2");
    Local::Box button3 = Local::Box::Box({ 0.25f, 0.25f }, {  0.3f, 0.2f }, { 0.5f, 0.5f, 0.5f }, "3");
    Local::Box button4 = Local::Box::Box({ 0.25f, 0.25f }, {  0.6f, 0.2f }, { 0.5f, 0.5f, 0.5f }, "+");

    Local::Box button5 = Local::Box::Box({ 0.25f, 0.25f }, { -0.3f, -0.1f }, { 0.5f, 0.5f, 0.5f }, "4");
    Local::Box button6 = Local::Box::Box({ 0.25f, 0.25f }, {  0.0f, -0.1f }, { 0.5f, 0.5f, 0.5f }, "5");
    Local::Box button7 = Local::Box::Box({ 0.25f, 0.25f }, {  0.3f, -0.1f }, { 0.5f, 0.5f, 0.5f }, "6");
    Local::Box button8 = Local::Box::Box({ 0.25f, 0.25f }, {  0.6f, -0.1f }, { 0.5f, 0.5f, 0.5f }, "-");

    Local::Box button9 = Local::Box::Box({ 0.25f, 0.25f }, { -0.3f, -0.4f }, { 0.5f, 0.5f, 0.5f }," 7");
    Local::Box button10 = Local::Box::Box({ 0.25f, 0.25f }, { 0.0f, -0.4f }, { 0.5f, 0.5f, 0.5f }, "8");
    Local::Box button11 = Local::Box::Box({ 0.25f, 0.25f }, { 0.3f, -0.4f }, { 0.5f, 0.5f, 0.5f }, "9");
    Local::Box button12 = Local::Box::Box({ 0.25f, 0.25f }, { 0.6f, -0.4f }, { 0.5f, 0.5f, 0.5f }, "*");

    Local::Box button13 = Local::Box::Box({ 0.25f, 0.25f }, { -0.3f, -0.7f }, { 0.5f, 0.5f, 0.5f },"C");
    Local::Box button14 = Local::Box::Box({ 0.25f, 0.25f }, { 0.0f, -0.7f }, { 0.5f, 0.5f, 0.5f }, "0");
    Local::Box button15 = Local::Box::Box({ 0.25f, 0.25f }, { 0.3f, -0.7f }, { 0.5f, 0.5f, 0.5f }, "=");
    Local::Box button16 = Local::Box::Box({ 0.25f, 0.25f }, { 0.6f, -0.7f }, { 0.5f, 0.5f, 0.5f }, "/");

    Local::Box buttons[] = { button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12, button13, button14, button15, button16 };
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        rect.Draw();
        rect2.Draw();

        button1.Draw();
        button2.Draw();
        button3.Draw();
        button4.Draw();

        button5.Draw();
        button6.Draw();
        button7.Draw();
        button8.Draw();

        button9.Draw();
        button10.Draw();
        button11.Draw();
        button12.Draw();

        button13.Draw();
        button14.Draw();
        button15.Draw();
        button16.Draw();
        checkOpenGLError("Drawing rect");
        
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            double xPos;
            double yPos;
            glfwGetCursorPos(window, &xPos, &yPos);

            xPos = NormalizeXCoordinate(xPos);
            yPos = NormalizeYCoordinate(yPos);
            
            for (auto button : buttons)
            {
                
                
                if ((xPos >= button.pos.X && xPos <= button.pos.X + button.size.X) && (yPos >= button.pos.Y && yPos <= button.pos.Y + button.size.Y))
                {
                    std::cout << button.Name << "\n";
                }
            }
        }
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up

    shaderProgram.Delete();

    glfwTerminate();
    return 0;
}
