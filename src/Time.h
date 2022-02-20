#pragma once

struct Time
{
public:
	static void Update();
	static const float& GetDeltaTime();
private:
	static float deltaTime;
	static float lastFrame;
	static float currentFrame;
};