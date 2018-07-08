#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Constants {

	/* Shaders */
	const std::string simpleVertexShader = "shader/simple.vert";
	const std::string simpleFragmentShader = "shader/simple.frag";
	const std::string flatVertexShader = "shader/flat.vert";
	const std::string flatFragmentShader = "shader/flat.frag";
	const std::string gouraudVertexShader = "shader/gouraud.vert";
	const std::string gouraudFragmentShader = "shader/gouraud.frag";
	const std::string phongVertexShader = "shader/phong.vert";
	const std::string phongFragmentShader = "shader/phong.frag";

	/* Object file */
	const std::string objFile = "obj/A4_testcube2_mitSpitze.obj";
	//const std::string objFile = "obj/Spaceship.obj";
	//const std::string objFile = "obj/stanford_bunny_closed.obj";

	/* Object scaling */
	const float initialObjectScale = 1.0f;
	const float scalingStep = 0.1f;
	const float minSacling = 0.1f;
	const float maxScaling = 10.0f;

	/* Initial viewpoint */
	inline glm::vec3 const &eye() {
		static glm::vec3 eye = glm::vec3(0.0f, 30.0f, 30.0f);
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

	/* Zoom */
	static float initialZoomFactor = 1.0f;
	static float zoomStep = 0.1f;
	static float minZoom = 0.1f;
	static float maxZoom = 3.0f;

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

	/* Manual rotation step */
	const float manualRotationStep = 5.0f;

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

	/* Constants for the central body */
	namespace Sun {
		const double radius = 2.0;
		const double distance = 0.0;
		const double orbitSpeed = 0.0;
		const double rotationSpeed = 0.0;
		const double tilt = 0.0; // degree
		const double offset = 0.0;
		const double startAngle = 0.0;
		const double startRotation = 0.0;
		inline glm::vec3 const &color() {
			static glm::vec3 color = glm::vec3(1.0f, 1.0f, 0.0f);
			return color;
		}
		const std::string texture = "texture/chessboard.jpg";
		inline glm::vec3 const &projCylinderOrigin() {
			static glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);
			return origin;
		}
		inline glm::vec3 const &projCylinderCenterAxis() {
			static glm::vec3 centerAxis = glm::vec3(1.0f, 0.0f, 0.0f);
			return centerAxis;
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
		const double startRotation = 0.0;
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
			const double startRotation = 0.0;
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
		const double startRotation = 0.0;
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
			const double startRotation = 0.0;
			inline glm::vec3 const &color() {
				static glm::vec3 color = glm::vec3(0.5f, 0.0f, 1.0f);
				return color;
			}
		}
	}

	/* Spaceship */
	namespace ship {
		const std::string objFile = "obj/Spaceship.obj";
		const double distance = 12.0;
		const double orbitSpeed = 25.0 / 1000.0;
		const double rotationSpeed = orbitSpeed;
		const double tilt = 0.0; // degree
		const double offset = 0.0;
		const double startAngle = 0.0;
		const double startRotation = 180.0;
		const double scaleFactor = 1.0;
		const double timeScaleFactor = 1.0;
		const double timeScaleStepSize = 0.5;
		const std::string texture = "texture/chessboard.jpg";
	}

}