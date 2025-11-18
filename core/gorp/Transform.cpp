#include "Transform.h"

namespace gorp
{
	void Transform::setGlobal(glm::mat4 local, glm::vec3 pos, glm::quat rotation, glm::vec3 scale)
	{
		local = glm::mat4(1.0f);
		local = glm::translate(local, pos);
		local *= glm::mat4_cast(rotation);
		local = glm::scale(local, scale);
	}

	void Transform::setLocalInverse()
	{
		transformLocalInv = glm::inverse(transformLocal);
	}

	void Transform::setGlobalInverse()
	{
		transformGlobalInv = glm::inverse(transformGlobal);
	}
}