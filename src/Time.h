#pragma once

struct Time
{
public:
	static void Update();
	static const float& DeltaTime();

	Time(Time& other) = delete;
	void operator=(const Time&) = delete;
private:
	static float deltaTime;
	static float lastFrame;
	static float currentFrame;

	Time() = default;
	~Time() = default;
};