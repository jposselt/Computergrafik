#pragma once
#include <glm/glm.hpp>

namespace Constants {

	/* Axes vectors */
	const glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	/* Scaling of rotation axis to radius */
	const float axisScale = 3.0f;

	/* Y-offset step size */
	const double yStepSize = 0.2;

	/* Axis tilt step size in degrees */
	const double tiltStepSize = 1.0;

	/* Speed factor step size */
	const double speedStepSize = 0.5;

	/* Degrees in full circle */
	const double degreeCircle = 360.0;
	
	namespace Sun {
		const double radius = 3.0;
		const double distance = 0.0;
		const double orbitSpeed = 0.0;
		const double rotationSpeed = 0.0;
		const double tilt = 0.0; // degree
		const double offset = 0.0;
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 0.0f);
	}

	namespace Planet_1 {

		const double radius = 1.5;
		const double distance = 5.0;
		const double orbitSpeed = 30.0 / 1000.0;    // 30° per second;
		const double rotationSpeed = 40.0 / 1000.0; // 40° per second
		const double tilt = 0.0; // degree
		const double offset = 0.0;
		glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);

		namespace Moons {
			//const double radius = ;
			//const double distance = ;
			//const double orbitSpeed = ;
			//const double offset = ;
		}
	}

	namespace Planet_2 {

		const double radius = 2.0;
		const double distance = 10.0;
		const double orbitSpeed = 15.0 / 1000.0;    // 15° per second
		const double rotationSpeed = 30.0 / 1000.0; // 30° per second
		const double tilt = 45.0; // degree
		const double offset = 0.0;
		glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);

		namespace Moons {

		}
	}
}