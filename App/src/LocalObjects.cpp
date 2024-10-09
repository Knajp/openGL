#include "LocalObjects.h"



GLfloat* Local::Box::vertices()
{
    static GLfloat vertices[] =
    {
        this->pos.X,                this->pos.Y,                 0.0f, this->color.R, this->color.G, this->color.B, // Bottom-left
        this->pos.X + this->size.X, this->pos.Y,                 0.0f, this->color.R, this->color.G, this->color.B, // Bottom-right
        this->pos.X,                this->pos.Y + this->size.Y,  0.0f, this->color.R, this->color.G, this->color.B, // Top-left
        this->pos.X + this->size.X, this->pos.Y + this->size.Y,  0.0f, this->color.R, this->color.G, this->color.B, // Top-right
    };
    return vertices;
}

GLuint* Local::Box::indices()
{
    static GLuint indices[] =
    {
        0, 1, 2, // First triangle
        2, 1, 3  // Second triangle
    };
    return indices;
}

Local::Box::Box(Vec2f size, Vec2f pos)
{

    VBO = Local::VBO::VBO();
    std::cout << "Created VBO\n";
    VBO.Bind();
    std::cout << "Bound VAO\n";
    VBO.BufferData(sizeof(GLfloat) * 24, vertices(), GL_STATIC_DRAW); // Correct size for vertices (4 vertices * 6 attributes each)
    std::cout << "VBO Buffer Data\n";

    EBO = Local::EBO::EBO();
    std::cout << "Created EBO\n";
    EBO.Bind();
    std::cout << "Bound EBO\n";
    EBO.BufferData(sizeof(GLuint) * 6, indices(), GL_STATIC_DRAW); // Correct size for indices (6 indices)
    std::cout << "EBO Buffer Data\n";


}

Local::Box::~Box()
{
}

void Local::Box::Draw()
{
	VBO.Bind();
	EBO.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
