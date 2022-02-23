#include "Cursor.h"

Cursor::Cursor(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Cursor::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		isVisible = !isVisible;

		if (isVisible)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

const bool& Cursor::IsVisible() const
{
	return isVisible;
}