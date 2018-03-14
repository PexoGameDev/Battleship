#include "stdafx.h"
#include "iostream"
#include "GLFW\glfw3.h"

int main()
{

	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1920,1080, "Battleship", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
    return 0;
}


class Ship
{
public:
	unsigned int position_x;
	unsigned int position_y;
	unsigned int length;
	int direction;

	Ship(unsigned int x, unsigned int y, int direction, unsigned int length)
	{
		position_x = x;
		position_y = y;
		direction = direction;
		length = length;
	}
private:

};