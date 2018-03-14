#include "stdafx.h"
#include "iostream"
#include "GLFW\glfw3.h"
#include "vector"

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

class Map
{
public:
	unsigned int length_x;
	unsigned int length_y;
	std::vector<std::vector<bool>> map;

	Map(unsigned int x, unsigned int y)
	{
		length_x = x;
		length_y = y;

		for (int i = 0; i < x; i++)
		{
			map.push_back(std::vector<bool>(y));
			for (int j = 0; j<y; j++)
				map[i].push_back(false);
		}

		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
				std::cout << map[i][j] << " ";
			std::cout << "\n";
		}

	}
private:
};

int main()
{
	Map *map = new Map(3, 10);

	getchar();

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
