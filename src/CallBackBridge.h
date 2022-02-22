#pragma once
#include "Camera.h"

struct CallBackBridge
{
	//Window resize callback function.
	void SetWindowResizeCallback(GLFWwindow* window);
	void SetMouseCallbacks(GLFWwindow* window, Camera& camera);
};