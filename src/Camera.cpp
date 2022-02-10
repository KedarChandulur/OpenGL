#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch) : m_worldUp(worldUp)
{
	transform.position = position;
	eulerAngles.yaw = yaw;
	eulerAngles.pitch = pitch;
	UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : m_worldUp(upX, upY, upZ)
{
	transform.position.x = posX;
	transform.position.y = posY;
	transform.position.z = posZ;

	eulerAngles.yaw = yaw;
	eulerAngles.pitch = pitch;
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(eulerAngles.yaw)) * cos(glm::radians(eulerAngles.pitch));
	front.y = sin(glm::radians(eulerAngles.pitch));
	front.z = sin(glm::radians(eulerAngles.yaw)) * cos(glm::radians(eulerAngles.pitch));

	cameraConstraints.front = glm::normalize(front);
	cameraConstraints.right = glm::normalize(glm::cross(cameraConstraints.front, m_worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cameraConstraints.up = glm::normalize(glm::cross(cameraConstraints.right, cameraConstraints.front));
}

void Camera::ProcessCameraMovement(float deltaTime, CameraMoveDirection cameraMoveDirection)
{
	switch (cameraMoveDirection)
	{
	case CameraMoveDirection::Forward:
		transform.position += cameraConstraints.front * settings.moveSpeed * deltaTime;
		break;
	case CameraMoveDirection::Backward:
		transform.position -= cameraConstraints.front * settings.moveSpeed * deltaTime;
		break;
	case CameraMoveDirection::Left:
		transform.position -= cameraConstraints.right * settings.moveSpeed * deltaTime;
		break;
	case CameraMoveDirection::Right:
		transform.position += cameraConstraints.right * settings.moveSpeed * deltaTime;
		break;
	case CameraMoveDirection::None:
		break;
	}
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessCameraRotation(float xoffset, float yoffset, float& mouseSens, GLboolean constrainPitch)
{
	//xoffset *= mouseSens;
	//yoffset *= mouseSens;
	//eulerAngles.yaw += xoffset;
	//eulerAngles.pitch += yoffset;

	eulerAngles.yaw += (xoffset * mouseSens);
	eulerAngles.pitch += (yoffset * mouseSens);

	if (constrainPitch)
	{
		if (eulerAngles.pitch > 89.0f)
			eulerAngles.pitch = 89.0f;
		if (eulerAngles.pitch < -89.0f)
			eulerAngles.pitch = -89.0f;
	}

	UpdateCameraVectors();
}

void Camera::ProcessFOV(float yoffset)
{
	settings.fov -= yoffset;
	if (settings.fov < 1.0f)
		settings.fov = 1.0f;
	else if (settings.fov > 90.0f)
		settings.fov = 90.0f;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(transform.position, transform.position + cameraConstraints.front, cameraConstraints.up);
}