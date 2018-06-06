#include "Camera.h"

namespace IN
{

	const float SENSITIVITY = 0.1f;

	Camera::Camera() : m_settings()
	{
	}

	Camera::Camera(CameraSettings settings)
	{
		m_settings = settings;
		updateCameraVect();
	}

	Camera::~Camera()
	{
	}

	void Camera::setPosition(glm::vec3 position)
	{
		m_settings.position = position;
		updateCameraVect();
	}

	glm::vec3 Camera::getPosition()
	{
		return m_settings.position;
	}

	void Camera::setTarget(glm::vec3 target)
	{
		m_settings.target = target;

		//Mise � jour de l'orientation selon la nouvelle cible
		m_settings.orientation = glm::normalize(m_settings.target - m_settings.position);

		//Mise � jour des angles
		m_settings.phi = glm::degrees(asin(m_settings.orientation.y));
		m_settings.theta = glm::degrees(acos(m_settings.orientation.z / cos(glm::radians(m_settings.phi))));

		if (m_settings.orientation.z < 0)
			m_settings.theta *= -1;

		m_settings.lateralMovement = glm::normalize(glm::cross(m_settings.orientation, m_settings.verticalAxe));
		m_settings.up = glm::normalize(glm::cross(m_settings.lateralMovement, m_settings.orientation));
	}

	glm::vec3 Camera::getTarget()
	{
		return m_settings.target;
	}

	float Camera::getSensitivity()
	{
		return m_settings.sensitivity;
	}

	void Camera::setSensitivity(float sensitivity)
	{
		m_settings.sensitivity = sensitivity;
	}

	float Camera::getSpeed()
	{
		return m_settings.speed;
	}

	void Camera::setSpeed(float speed)
	{
		m_settings.speed = speed;
	}

	void Camera::move(glm::vec3 move)
	{
		m_settings.position += move;
	}

	void Camera::move(int input)
	{
		// Avanc�e de la cam�ra (touche z)
		if (input == 87)
			m_settings.position += m_settings.orientation * m_settings.speed;


		// Recul de la cam�ra (touche s)
		if (input == 83)
			m_settings.position -= m_settings.orientation * m_settings.speed;


		// D�placement vers la gauche (touche q)
		if (input == 65)
			m_settings.position += m_settings.lateralMovement * m_settings.speed;


		// D�placement vers la droite (touche d)
		if (input == 68)
			m_settings.position -= m_settings.lateralMovement * m_settings.speed;

		m_settings.target = m_settings.position + m_settings.orientation;
	}

	void Camera::move(int x, int y)
	{
		//Mise � jour des angles
		m_settings.phi += y * m_settings.sensitivity;
		m_settings.theta += x * m_settings.sensitivity;


		if (m_settings.phi > 89.0f)
			m_settings.phi = 89.0f;

		else if (m_settings.phi < -89.0f)
			m_settings.phi = -89.0f;

		//Mise � jour orientation
		updateCameraVect();
	}

	void Camera::update()
	{
		m_view = glm::lookAt(
			m_settings.position,
			m_settings.target,
			m_settings.up
		);

		m_projection = glm::perspective(
			glm::radians(m_settings.fov),
			m_settings.aspect,
			m_settings.znear,
			m_settings.zfar
		);
	}

	glm::mat4 Camera::getMatrix()
	{
		return m_projection * m_view;
	}

	void Camera::updateCameraVect()
	{
		m_settings.orientation.x = sin(glm::radians(m_settings.theta)) * cos(glm::radians(m_settings.phi));
		m_settings.orientation.y = sin(glm::radians(m_settings.phi));
		m_settings.orientation.z = cos(glm::radians(m_settings.theta)) * cos(glm::radians(m_settings.phi));
		m_settings.orientation = glm::normalize(m_settings.orientation);

		m_settings.lateralMovement = glm::normalize(glm::cross(m_settings.orientation, m_settings.verticalAxe));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_settings.up = glm::normalize(glm::cross(m_settings.lateralMovement, m_settings.orientation));

		m_settings.target = m_settings.position + m_settings.orientation;
	}
}
