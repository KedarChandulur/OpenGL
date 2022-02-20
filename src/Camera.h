#ifndef CAMERA_H
#define CAMERA_H

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h>

enum class CameraMoveDirection : GLshort
{
	None = 0,
	Forward = -1, //-1 because forward vec(z value) is negative for opengl coord system.
	Backward = 1, //1 because backward vec(z value) is positive for opengl coord system.
	Left = -2,
	Right = 2
};

enum class ProjectionType : GLubyte
{
	Perspective = 0U,
	Orthographic = 1U,
};

struct Transform
{
	glm::vec3 position = glm::vec3(0.0f);
	//glm::vec3 scale;
};

struct EulerAngles
{						//Rotate through
	float pitch = 0.0f;	//x-axis
	float yaw = -90.0f; //y-axis
	//float roll;			//z-axis
};

struct CameraSettings
{
	ProjectionType projection = ProjectionType::Perspective;
	float aspectRatio = 1.778f;
	float fov = 45.0f;
	float near = 0.1f;
	float far = 100.0f;
	float moveSpeed = 2.5f;
};

struct CameraConstraints
{
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
};

class Camera
{
public:
	virtual ~Camera() = default;

	Camera() { UpdateCameraVectors(); };
	Camera(glm::vec3 position = glm::vec3(0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
	Camera(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, float upX = 0.0f, float upY = 0.1f, float upZ = 0.0f, float yaw = -90.0f, float pitch = 0.0f);

	void ProcessInput(GLFWwindow* window);

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix() const;

	Transform transform;
	EulerAngles eulerAngles;
	CameraSettings settings;
	CameraConstraints cameraConstraints;
private:
	void ProcessCameraMovement(CameraMoveDirection cameraMoveDirection = CameraMoveDirection::None);
	void UpdateCameraVectors();
	void ProcessFOV(float yoffset);
	void ProcessCameraRotation(float xoffset, float yoffset, float& mouseSens, GLboolean constrainPitch = true);

	glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif