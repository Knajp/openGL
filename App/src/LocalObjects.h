#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLObjects.h"

struct Vec2f {
	float X;
	float Y;
};
struct Color {
	float R;
	float G;
	float B;
};
namespace Local
{

	class Box 
	{
	public:
		Local::VBO VBO;
		Local::EBO EBO;

		Vec2f pos;
		Vec2f size;
		Color color;

		GLfloat* vertices();
		GLuint* indices();

		Box(Vec2f size, Vec2f pos);
		~Box();

		void Draw();

	};
}