#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <stack>

class HierachyObj
{
public:
	std::string name;
	HierachyObj* parent;
	std::vector <HierachyObj*> children;
	glm::mat4 tranformLocal;
	glm::mat4 tranformGlobal;
	glm::mat4 tranformLocalInv;
	glm::mat4 tranformGlobalInv;

	void setGlobal(glm::mat4 local, glm::vec3 pos, glm::quat rotation, glm::vec3 scale);
	void setLocalBasedOnHierachy();
	void setHierarchyBasedOnLocal();
};