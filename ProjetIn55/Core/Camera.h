#pragma once

#include <glm\gtc\matrix_transform.hpp>
#include "CameraSettings.h"

namespace IN
{
	class Camera
	{
	protected:
		CameraSettings m_settings;

		glm::mat4 m_view;
		glm::mat4 m_projection;

	public:
		Camera();
		Camera(CameraSettings settings);
		~Camera();

		void setPosition(glm::vec3 position);
		glm::vec3 getPosition();

		void setTarget(glm::vec3 target);
		glm::vec3 getTarget();

		float getSensitivity();
		void setSensitivity(float sensitivity);

		float getSpeed();
		void setSpeed(float vitesse);

		void move(glm::vec3 move);
		//Changement position caméra avec clavier directionnel
		void move(int input);
		//Changement orientation caméra avec mouvement souris
		void move(int x, int y);

		void update();
		glm::mat4 getMatrix();

		void updateCameraVect();
	};
}
