#pragma once

#include <glm/glm.hpp>

namespace Constants {

	/* Axes vectors */
	inline glm::vec3 const &xAxis() {
		static glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		return xAxis;
	}

	inline glm::vec3 const &yAxis() {
		static glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		return yAxis;
	}

	inline glm::vec3 const &zAxis() {
		static glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		return zAxis;
	}

	/* Default colors */
	inline glm::vec3 const &defaultColor() {
		static glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);
		return color;
	}
	inline glm::vec3 const &defaultVNColor() {
		static glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
		return color;
	}
	inline glm::vec3 const &defaultFNColor() {
		static glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
		return color;
	}

	/* Default material properties */
	inline glm::vec3 const &defaultMaterial() {
		static glm::vec3 mat = glm::vec3(0.5f, 0.5f, 0.0f);
		return mat;
	}
	const float defaultShininess = 64;

	/* Number of edges for circle */
	const unsigned int edges = 360;

	/* Number of stacks and slices for spheres */
	const unsigned int stacks = 30;
	const unsigned int slices = 30;

	/* Default radius */
	const double radius = 1.0;

	/* Scaling of rotation axis to radius */
	const float axisScale = 2.0f;

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

}