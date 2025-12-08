/*
*	Author: Eric Winebrenner
*/

#pragma once
#include <glm/glm.hpp>
#include <vector>

#include <map>
#include <string>


#define MAX_NUMBER_OF_BONES_PER_VERTEX 4

namespace ew {

	struct VertexBoneData
	{
		int BoneIDs[MAX_NUMBER_OF_BONES_PER_VERTEX] = { 0 };
		float Weights[MAX_NUMBER_OF_BONES_PER_VERTEX] = { 0.0f };

		VertexBoneData()
		{

		}

		void AddBoneData(int BoneID, float Weight)
		{
			for (int i = 0; i < MAX_NUMBER_OF_BONES_PER_VERTEX; i++)
			{
				if (Weights[i] == 0)
				{
					BoneIDs[i] = BoneID;
					Weights[i] = Weight;
					return;
				}
			}
			assert(0);
		}
	};

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;
		std::vector<VertexBoneData> bones;
		std::map<std::string, int> boneNameToIndexMap;
	};

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};

	enum class DrawMode {
		TRIANGLES = 0,
		POINTS = 1
	};

	class Mesh {
	public:
		Mesh() {};
		Mesh(const MeshData& meshData);
		void load(const MeshData& meshData);
		void draw(DrawMode drawMode = DrawMode::TRIANGLES)const;
		inline int getNumVertices()const { return m_numVertices; }
		inline int getNumIndices()const { return m_numIndices; }
	private:
		bool m_initialized = false;
		unsigned int m_vao = 0;
		unsigned int m_vbo = 0;
		unsigned int m_ebo = 0;
		unsigned int m_numVertices = 0;
		unsigned int m_numIndices = 0;
	};
}