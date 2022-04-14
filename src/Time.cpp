#include "Time.h"
#include <GLFW/glfw3.h>

void Time::Update()
{
	currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

const float& Time::DeltaTime()
{
	return deltaTime;
}

float Time::deltaTime = 0.0f;
float Time::lastFrame = 0.0f;
float Time::currentFrame = 0.0f;