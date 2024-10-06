#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Core.h "

const char *vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n\n"
"layout(location = 1) in vec3 aColor;\n\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0); \n"
"vertexColor = vec4(aColor, 1.0);\n"
"}\n";

const char* fragShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"FragColor = vertexColor;\n"
"}\n";

GLfloat vertices[] =
{
    -0.5f, -0.5f, 0.0f,     0.5f, 0.0f, 0.5f,
     0.0f, -0.5f, 0.0f,     0.5f, 0.0f, 0.5f,
     0.5f, -0.5f, 0.0f,     0.5f, 0.0f, 0.5f,
     0.25f, 0.0f, 0.0f,     0.5f, 0.0f, 0.5f,
    -0.25f, 0.0f, 0.0f,     0.5f, 0.0f, 0.5f,
     0.0f,  0.5f, 0.0f,     0.5f, 0.0f, 0.5f
};
GLuint indices[] =
{
    0,  4,  1,
    1,  2,  3,
    3,  4,  5
};
int main(int argc, char** argv)
{
    GLFWwindow* window = Local::Init();

    Local::Shader vertexShader = Local::Shader::Shader(GL_VERTEX_SHADER);
    vertexShader.ShaderSource(1, &vertexShaderSource, NULL);
    vertexShader.Compile();

    Local::Shader fragShader = Local::Shader::Shader(GL_FRAGMENT_SHADER);
    fragShader.ShaderSource(1, &fragShaderSource, NULL);
    fragShader.Compile();

    Local::ShaderProgram shaderProgram = Local::ShaderProgram::ShaderProgram();
    shaderProgram.attachShader(vertexShader.ID);
    shaderProgram.attachShader(fragShader.ID);
    shaderProgram.Link();
    
    shaderProgram.Use();

    vertexShader.Delete();
    fragShader.Delete();


    Local::VAO VAO = Local::VAO::VAO();
    Local::VBO VBO = Local::VBO::VBO();
    Local::EBO EBO = Local::EBO::EBO();

    VAO.Bind();

    VBO.Bind();
    VBO.BufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);

    EBO.Bind();
    EBO.BufferData(sizeof(indices), indices, GL_STATIC_DRAW);

    VAO.VertexAttrib(0, 3, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    VAO.VertexAttrib(1, 3, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(GLfloat)));

    VBO.Unbind();
    VAO.Unbind();
    
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();
        VAO.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    }
    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    shaderProgram.Delete();
    return 0;
}