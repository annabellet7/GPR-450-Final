#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gorp
{
	class Transform
	{
	public:
		glm::mat4 transformLocal;
		glm::mat4 transformGlobal;
		glm::mat4 transformLocalInv;
		glm::mat4 transformGlobalInv;

		void setGlobal(glm::mat4 local, glm::vec3 pos, glm::quat rotation, glm::vec3 scale);
		void setLocalInverse();
		void setGlobalInverse();
		void setLocalBasedOnGlobal();
		void setHierarchyBasedOnLocal();
	};
}
