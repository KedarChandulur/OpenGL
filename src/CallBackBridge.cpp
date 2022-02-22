#include "CallBackBridge.h"
#include "Renderer.h"

void CallBackBridge::SetWindowResizeCallback(GLFWwindow* window)
{
	GLCall(glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { GLCall(glViewport(0, 0, width, height)); }));
}

void CallBackBridge::SetMouseCallbacks(GLFWwindow* window, Camera& camera)
{
	static Camera& cameraReference = camera;

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
	{
		GLCall(cameraReference.ProcessMouseScroll(static_cast<float>(yoffset), cameraReference.settings.fov));
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xposIn, double yposIn)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (cameraReference.mouseMoveData.firstMove)
		{
			cameraReference.mouseMoveData.lastPositions.x = xpos;
			cameraReference.mouseMoveData.lastPositions.y = ypos;
			cameraReference.mouseMoveData.firstMove = false;
		}

		cameraReference.mouseMoveData.offsetPositions.x = xpos - cameraReference.mouseMoveData.lastPositions.x;
		// Need to Reverse the logic because y-coordinates go from bottom to top.
		cameraReference.mouseMoveData.offsetPositions.y = cameraReference.mouseMoveData.lastPositions.y - ypos;

		cameraReference.mouseMoveData.lastPositions.x = xpos;
		cameraReference.mouseMoveData.lastPositions.y = ypos;

		GLCall(cameraReference.ProcessMouseMove(cameraReference.mouseMoveData.offsetPositions.x, cameraReference.mouseMoveData.offsetPositions.y));
	});
}