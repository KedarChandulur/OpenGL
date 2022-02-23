#pragma once

#include "I_InputHelper.h"

struct Cursor : I_InputHelper
{
	virtual ~Cursor() = default;
	Cursor(GLFWwindow* window);

	void ProcessInput(GLFWwindow* window) override;

	const bool& IsVisible() const;
private:
	bool isVisible = false;
};