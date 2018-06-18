#pragma once
#include <glm/glm.hpp>

/// <summary>
/// Collection of constants
/// </summary>
namespace Constants {

	/* Shaders */
	const std::string simpleVertexShader = "shader/simple.vert";
	const std::string simpleFragmentShader = "shader/simple.frag";
	const std::string vertexShader = "shader/flat.vert";
	const std::string fragmentShader = "shader/flat.frag";
	//const std::string vertexShader = "shader/gouraud.vert";
	//const std::string fragmentShader = "shader/gouraud.frag";
	//const std::string vertexShader = "shader/phong.vert";
	//const std::string fragmentShader = "shader/phong.frag";

	/* Initial viewpoint */
	inline glm::vec3 const &eye() {
		static glm::vec3 eye = glm::vec3(0.0f, 0.0f, 30.0f);
		return eye;
	}

	inline glm::vec3 const &center() {
		static glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
		return center;
	}

	inline glm::vec3 const &up() {
		static glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		return up;
	}

	/* */
	const float zNear = 0.1f;
	const float zFar = 100.0f;

	/* Clear color */
	inline glm::vec4 const &clearColor() {
		static glm::vec4 clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return clearColor;
	}

	/* Global lighting settings */
	inline glm::vec3 const &directLight() {
		static glm::vec3 directLight = glm::vec3(1.0f, 1.0f, 1.0f); // white light
		return directLight;
	}

	inline glm::vec3 const &ambientLight() {
		static glm::vec3 ambientLight = glm::vec3(0.0f, 0.0f, 0.0f); // no ambient light
		return ambientLight;
	}
	
	inline glm::vec4 const &lightDirection() {
		static glm::vec4 lightDirection = glm::vec4(1.0, 0.0, 0.0, 0.0);
		return lightDirection;
	}

	/* Number of stacks and slices for spheres */
	const unsigned int stacks = 60;
	const unsigned int slices = 60;

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
	
	/* Constants for the central body */
	namespace Sun {
		const double radius = 2.0;
		const double distance = 0.0;
		const double orbitSpeed = 0.0;
		const double rotationSpeed = 0.0;
		const double tilt = 0.0; // degree
		const double offset = 0.0;
		const double startAngle = 0.0;
		inline glm::vec3 const &color() {
			static glm::vec3 color = glm::vec3(1.0f, 1.0f, 0.0f);
			return color;
		}
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
		inline glm::vec3 const &color() {
			static glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
			return color;
		}

		/* Constants for the first planets moons */
		namespace Moons {
			const unsigned int nUpper = 0;
			const unsigned int nLower = 0;
			const unsigned int nCenter = 3;
			const double radius = 0.5;
			const double distance = 2.0;
			const double orbitSpeed = 50.0 / 1000.0; // 50° per second
			const double rotationSpeed = 0.0;
			const double tilt = 0.0; // degree
			const double offset = 0.0;
			inline glm::vec3 const &color() {
				static glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.0f);
				return color;
			}
		}
	}

	/* Constants for the second planet */
	namespace Planet_2 {
		const double radius = 1.5;
		const double distance = 17.0;
		const double orbitSpeed = 15.0 / 1000.0;    // 15° per second
		const double rotationSpeed = 30.0 / 1000.0; // 30° per second
		const double tilt = 45.0; // degree
		const double offset = 0.0;
		const double startAngle = 180.0;
		inline glm::vec3 const &color() {
			static glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
			return color;
		}

		/* Constants for the second planets moons */
		namespace Moons {
			const unsigned int nUpper = 4;
			const unsigned int nLower = 4;
			const unsigned int nCenter = 2;
			const double radius = 0.5;
			const double distance = 3.0;
			const double orbitSpeed = 20.0 / 1000.0; // 20° per second
			const double rotationSpeed = 0.0;
			const double tilt = 0.0; // degree
			const double centerOffset = 0.0;
			const double upperOffset = 2.5;
			const double lowerOffset = -2.5;
			inline glm::vec3 const &color() {
				static glm::vec3 color = glm::vec3(0.5f, 0.0f, 1.0f);
				return color;
			}
		}
	}
}