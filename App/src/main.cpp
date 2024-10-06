#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


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
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }   
    glViewport(0, 0, 800, 600);

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    
    glUseProgram(shaderProgram);
  

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);




    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);


        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    return 0;
}