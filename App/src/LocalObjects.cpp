#include "LocalObjects.h"



Local::Box::Box(Vec2f size, Vec2f pos)
{

    this->size = size;
    this->pos = pos;



    GLuint localIndices[6] =
    {
        0, 1, 2,
        2, 1, 3
    };

    for (int i = 0; i < 6; i++)
    {
        this->indices[i] = localIndices[i];
    }

    GLfloat localVertices[24] =
    {
        this->pos.X,                this->pos.Y,                 0.0f,      255.0f, 0.0f, 100.0f,
        this->pos.X + this->size.X, this->pos.Y,                 0.0f,      255.0f, 0.0f, 100.0f,
        this->pos.X,                this->pos.Y + this->size.Y,  0.0f,      255.0f, 0.0f, 100.0f,
        this->pos.X + this->size.X, this->pos.Y + this->size.Y,  0.0f,      255.0f, 0.0f, 100.0f
    };

    for (int i = 0; i < 24; i++)
    {
        this->vertices[i] = localVertices[i];
    }

    VAO = Local::VAO::VAO();
    VAO.Bind();

    VBO = Local::VBO::VBO();
    std::cout << "Created VBO\n";
    VBO.Bind();
    std::cout << "Bound VAO\n";
    VBO.BufferData(sizeof(GLfloat) * 24, this->vertices, GL_STATIC_DRAW); // Correct size for vertices (4 vertices * 6 attributes each)
    std::cout << "VBO Buffer Data\n";

    VAO.VertexAttrib(0, 3, GL_FALSE, 6 * sizeof(float), (void*)0);
    VAO.VertexAttrib(1, 3, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    EBO = Local::EBO::EBO();
    std::cout << "Created EBO\n";
    EBO.Bind();
    std::cout << "Bound EBO\n";
    EBO.BufferData(sizeof(GLuint) * 6, this->indices, GL_STATIC_DRAW); // Correct size for indices (6 indices)
    std::cout << "EBO Buffer Data\n";

    VBO.Unbind();
    VAO.Unbind();

}

Local::Box::~Box()
{
}

void Local::Box::Draw()
{
    VAO.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
