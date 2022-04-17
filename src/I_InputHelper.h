#pragma once
#include <GLFW/glfw3.h>

struct I_InputHelper
{
	virtual ~I_InputHelper() = default;
	virtual void ProcessInput(GLFWwindow* window) = 0;
};