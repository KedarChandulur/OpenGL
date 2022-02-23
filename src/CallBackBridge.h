#pragma once
#include "Camera.h"

struct CallBackBridge
{
	//Window resize callback function.
	void SetWindowResizeCallback(GLFWwindow* window);
	//Mouse Callbacks for Camera specifically.
	void SetMouseCallbacks(GLFWwindow* window, Camera& camera);
};