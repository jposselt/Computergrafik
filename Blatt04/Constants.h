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

	/* Maximum axis tilt (degrees) */
	const double maxTilt = 360.0;

	/* Minimum axis tilt (degrees) */
	const double minTilt = 0.0;

	/* Initial time scale factor */
	const double initialTimeScaleFactor = 1.0;

	/* Time scale factor step size */
	const double timeScaleStepSize = 0.5;

	/* Degrees in full circle */
	const double degreeCircle = 360.0;
	
	/* Constants for the central body */
	namespace Sun {
		const double radius = 2.0;
		const double distance = 0.0;
		const double orbitSpeed = 0.0;
		const double rotationSpeed = 0.0;
		const double tilt = 0.0; // degree
		const double offset = 0.0;
		const double startAngle = 0.0;
		const glm::vec3 color = glm::vec3(1.0f, 1.0f, 0.0f);
	}

	/* Constants for the first planet */
	namespace Planet_1 {
		const double radius = 1.0;
		const double distance = 7.0;
		const double orbitSpeed = 30.0 / 1000.0;    // 30° per second;
		const double rotationSpeed = 40.0 / 1000.0; // 40° per second
		const double tilt = 0.0; // degree
		const double offset = 0.0;
		const double startAngle = 0.0;
		const glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);

		/* Constants for the first planets moons */
		namespace Moons {
			const unsigned int nUpper = 0;
			const unsigned int nLower = 0;
			const unsigned int nCenter = 3;
			const double radius = 0.5;
			const double distance = 1.0;
			const double orbitSpeed = 20.0 / 1000.0; // 20° per second
			const double offset = 0.0;
			const glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.0f);
		}
	}

	/* Constants for the second planet */
	namespace Planet_2 {
		const double radius = 1.5;
		const double distance = 15.0;
		const double orbitSpeed = 15.0 / 1000.0;    // 15° per second
		const double rotationSpeed = 30.0 / 1000.0; // 30° per second
		const double tilt = 45.0; // degree
		const double offset = 0.0;
		const double startAngle = 180.0;
		const glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);

		/* Constants for the second planets moons */
		namespace Moons {
			const unsigned int nUpper = 4;
			const unsigned int nLower = 4;
			const unsigned int nCenter = 2;
			const double radius = 0.5;
			const double distance = 1.0;
			const double orbitSpeed = 20.0 / 1000.0; // 20° per second
			const double offset = 2.0;
			const glm::vec3 color = glm::vec3(0.5f, 0.0f, 1.0f);
		}
	}
}