#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <stack>
namespace gorp
{
	class HierarchyNode
	{
	public:
		std::string name;
		int parentIndex;
		int selfIndex;

		/*void setGlobal(glm::mat4 local, glm::vec3 pos, glm::quat rotation, glm::vec3 scale);
		void setLocalInverse();
		void setGlobalInverse();
		void setLocalBasedOnGlobal();
		void setHierarchyBasedOnLocal();*/
		void setNode(std::string name, int parent, int self);
		int GetNode();
	};
}
