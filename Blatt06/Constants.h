#pragma once

#include <glm/glm.hpp>

namespace Constants {

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
}