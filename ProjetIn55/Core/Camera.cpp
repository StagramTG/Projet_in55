#include "Camera.h"
#include <iostream>

namespace IN
{

	const float SENSITIVITY = 0.01f;

	Camera::Camera() : m_settings()
	{
		m_model = glm::mat4(1.f);
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

		//Mise à jour de l'orientation selon la nouvelle cible
		m_settings.orientation = glm::normalize(m_settings.target - m_settings.position);

		//Mise à jour des angles
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
		//stop la rotation (touche s)
		if (input == 83)
			m_settings.theta = 0.f;

		//rotation vers la gauche (touche q)
		if (input == 65)
			m_settings.theta = -0.2f * m_settings.sensitivity * m_settings.speed;

		//rotation vers la droite (touche d)
		if (input == 68)
			m_settings.theta = 0.2f * m_settings.sensitivity * m_settings.speed;


		// Avancée de la caméra (touche z)
		//if (input == 87)
		//	m_settings.position += m_settings.orientation * m_settings.speed;

		// Recul de la caméra (touche s)
		//	m_settings.position -= m_settings.orientation * m_settings.speed;

		// Déplacement vers la gauche (touche q)
		//m_settings.position += m_settings.lateralMovement * m_settings.speed;

		// Déplacement vers la droite
		//m_settings.position -= m_settings.lateralMovement * m_settings.speed;

		m_settings.target = m_settings.position + m_settings.orientation;
	}

	void Camera::move(int x, int y)
	{
		/*
		//Mise à jour des angles
		m_settings.phi += y * m_settings.sensitivity;
		m_settings.theta += x * m_settings.sensitivity;


		if (m_settings.phi > 89.0f)
			m_settings.phi = 89.0f;

		else if (m_settings.phi < -89.0f)
			m_settings.phi = -89.0f;
			
		//Mise à jour orientation
		updateCameraVect();
		*/
	}

	void Camera::update()
	{
		//ralentis le mouvement de rotation horizontal
		m_settings.theta *= 0.99f;

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

		m_model = glm::rotate(m_model, m_settings.theta, glm::vec3(0.f, 1.f, 0.f));

	}

	glm::mat4 Camera::getMatrix()
	{

		return m_projection * m_view * m_model;
	}

	void Camera::updateCameraVect()
	{

		m_settings.orientation.x = sin(glm::radians(m_settings.theta)) * cos(glm::radians(m_settings.phi));
		m_settings.orientation.y = sin(glm::radians(m_settings.phi));
		m_settings.orientation.z = cos(glm::radians(m_settings.theta)) * cos(glm::radians(m_settings.phi));
		m_settings.orientation = glm::normalize(m_settings.orientation);

		//Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_settings.lateralMovement = glm::normalize(glm::cross(m_settings.orientation, m_settings.verticalAxe)); 
		m_settings.up = glm::normalize(glm::cross(m_settings.lateralMovement, m_settings.orientation));

		m_settings.target = m_settings.position + m_settings.orientation;
	}
}
