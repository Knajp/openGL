#ifndef GL_OBJECTS_H
#define GL_OBJECTS_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
namespace Local
{
	class VAO
	{
	public:
		GLuint ID;

		VAO();
		~VAO();

		void Bind();
		void Unbind();

		void VertexAttrib(GLuint i, GLint si, GLboolean n, GLsizei st, const GLvoid* p );

		void Delete();
	};

	class VBO
	{
	public:
		GLuint ID;

		VBO();
		~VBO();

		void Bind();
		void Unbind();

		void BufferData(GLsizeiptr s, const GLvoid* d, GLenum u);

		void Delete();
	};

	class EBO
	{
	public:
		GLuint ID;

		EBO();
		~EBO();

		void Bind();
		void Unbind();

		void BufferData(GLsizeiptr s, const GLvoid* d, GLenum u);

		void Delete();
	};
	class Shader
	{
	public:
		GLuint ID;

		Shader(GLenum type);
		~Shader();

		void ShaderSource(GLsizei s, const GLchar** str, const GLint* l);
		void Compile();

		void Delete();
	};
	class ShaderProgram
	{
	public:

		GLuint ID;

		ShaderProgram();
		~ShaderProgram();

		void attachShader(GLuint shader);
		void Link();

		void Use();

		void Delete();
	};
	GLFWwindow* Init();
}
#endif