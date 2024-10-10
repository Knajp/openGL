#include "GLObjects.h"

Local::VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

Local::VAO::~VAO()
{

}

void Local::VAO::Bind()
{
	glBindVertexArray(ID);
}
void Local::VAO::Unbind()
{
	glBindVertexArray(0);
}

void Local::VAO::VertexAttrib(GLuint i, GLint si, GLboolean n, GLsizei st, const GLvoid* p)
{
	glVertexAttribPointer(i, si, GL_FLOAT, n, st, p);
	glEnableVertexAttribArray(i);
}

void Local::VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
	this->~VAO();
}

Local::VBO::VBO()
{
	glGenBuffers(1, &ID);
}

Local::VBO::~VBO()
{

}

void Local::VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void Local::VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Local::VBO::BufferData( GLsizeiptr s, const GLvoid* d, GLenum u)
{
	glBufferData(GL_ARRAY_BUFFER, s, d, u);
}

void Local::VBO::Delete()
{
	glDeleteBuffers(1, &ID);
	this->~VBO();
}

GLFWwindow* Local::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;

    }
    glViewport(0, 0, 800, 800);

    return window;
}

Local::EBO::EBO()
{
    glGenBuffers(1, &ID);
}

Local::EBO::~EBO()
{

}

void Local::EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void Local::EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Local::EBO::BufferData(GLsizeiptr s, const GLvoid* d, GLenum u)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s, d, u);
}

void Local::EBO::Delete()
{
    glDeleteBuffers(1, &ID);
    this->~EBO();
}

Local::Shader::Shader(GLenum type)
{
    this->ID = glCreateShader(type);
}

Local::Shader::~Shader()
{

}

void Local::Shader::ShaderSource(GLsizei s, const GLchar** str, const GLint* l)
{
    glShaderSource(ID, s, str, l);
}

void Local::Shader::Compile()
{
    glCompileShader(ID);
}

void Local::Shader::Delete()
{
    glDeleteShader(ID);
    this->~Shader();
}

Local::ShaderProgram::ShaderProgram()
{
    this->ID = glCreateProgram();
}

Local::ShaderProgram::~ShaderProgram()
{
}

void Local::ShaderProgram::attachShader(GLuint shader)
{
    glAttachShader(ID, shader);
}

void Local::ShaderProgram::Link()
{
    glLinkProgram(ID);
}

void Local::ShaderProgram::Use()
{
    glUseProgram(ID);
}

void Local::ShaderProgram::Delete()
{
    glDeleteProgram(ID);
    this->~ShaderProgram();
}
