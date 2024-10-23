#include "LocalObjects.h"



Local::Box::Box(Vec2f size, Vec2f pos, Color color)
{

    this->size = size;
    this->pos = pos;
    this->color = color;


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
        this->pos.X,                this->pos.Y,                 0.0f,      this->color.R, this->color.G, this->color.B,
        this->pos.X + this->size.X, this->pos.Y,                 0.0f,      this->color.R, this->color.G, this->color.B,
        this->pos.X,                this->pos.Y + this->size.Y,  0.0f,      this->color.R, this->color.G, this->color.B,
        this->pos.X + this->size.X, this->pos.Y + this->size.Y,  0.0f,      this->color.R, this->color.G, this->color.B
    };

    for (int i = 0; i < 24; i++)
    {
        this->vertices[i] = localVertices[i];
    }

    VAO = Local::VAO::VAO();
    VAO.Bind();

    VBO = Local::VBO::VBO();

    VBO.Bind();
    VBO.BufferData(sizeof(GLfloat) * 24, this->vertices, GL_STATIC_DRAW); // Correct size for vertices (4 vertices * 6 attributes each)

    VAO.VertexAttrib(0, 3, GL_FALSE, 6 * sizeof(float), (void*)0);
    VAO.VertexAttrib(1, 3, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    EBO = Local::EBO::EBO();
    EBO.Bind();

    EBO.BufferData(sizeof(GLuint) * 6, this->indices, GL_STATIC_DRAW); // Correct size for indices (6 indices)


    VBO.Unbind();
    VAO.Unbind();

}
Local::Box::Box(Vec2f size, Vec2f pos, Color color, std::string Name)
{
    this->size = size;
    this->pos = pos;
    this->color = color;
    this->Name = Name;

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
        this->pos.X,                this->pos.Y,                 0.0f,      this->color.R, this->color.G, this->color.B,
        this->pos.X + this->size.X, this->pos.Y,                 0.0f,      this->color.R, this->color.G, this->color.B,
        this->pos.X,                this->pos.Y + this->size.Y,  0.0f,      this->color.R, this->color.G, this->color.B,
        this->pos.X + this->size.X, this->pos.Y + this->size.Y,  0.0f,      this->color.R, this->color.G, this->color.B
    };

    for (int i = 0; i < 24; i++)
    {
        this->vertices[i] = localVertices[i];
    }

    VAO = Local::VAO::VAO();
    VAO.Bind();

    VBO = Local::VBO::VBO();

    VBO.Bind();
    VBO.BufferData(sizeof(GLfloat) * 24, this->vertices, GL_STATIC_DRAW); // Correct size for vertices (4 vertices * 6 attributes each)

    VAO.VertexAttrib(0, 3, GL_FALSE, 6 * sizeof(float), (void*)0);
    VAO.VertexAttrib(1, 3, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    EBO = Local::EBO::EBO();
    EBO.Bind();

    EBO.BufferData(sizeof(GLuint) * 6, this->indices, GL_STATIC_DRAW); // Correct size for indices (6 indices)


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
