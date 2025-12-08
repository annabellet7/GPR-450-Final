/*
*	Author: Eric Winebrenner
*/

#include "model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <assimp/scene.h>
#include <glm/glm.hpp>

#include <map>
#include <string>
#include <vector>



namespace ew {
	ew::Mesh processAiMesh(aiMesh* aiMesh);

	std::vector<VertexBoneData> vertex_to_bones;
	std::vector<int> mesh_base_vertex;
	std::map<std::string, int> bone_name_to_index_map;

	Model::Model(const std::string& filePath)
	{
		Assimp::Importer importer;
		const aiScene* aiScene = importer.ReadFile(filePath, aiProcess_Triangulate);
		for (size_t i = 0; i < aiScene->mNumMeshes; i++)
		{
			aiMesh* aiMesh = aiScene->mMeshes[i];
			m_meshes.push_back(processAiMesh(aiMesh));
		}
	}

	void Model::draw()
	{
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			m_meshes[i].draw();
		}
	}

	glm::vec3 convertAIVec3(const aiVector3D& v) {
		return glm::vec3(v.x, v.y, v.z);
	}

	int get_bone_id(const aiBone* aiBone)
	{
		int bone_id = 0;
		std::string bone_name(aiBone->mName.C_Str());

		if (bone_name_to_index_map.find(bone_name) == bone_name_to_index_map.end())
		{
			bone_id = bone_name_to_index_map.size();
			bone_name_to_index_map[bone_name] = bone_id;
		}
		else
		{
			bone_id = bone_name_to_index_map[bone_name];
		}

		return bone_id;
	}

	void parse_single_bone(int index, aiBone* aiBone)
	{
		int bone_id = get_bone_id(aiBone);

		
		/*if (bond_id = m_BoneInfo.size())
		{
			BoneInfo bi(aiBone->mOffsetMatrix);
			m_BoneInfo.push_back(bi);
		}*/

		for (int i = 0; i < aiBone->mNumWeights; i++)
		{
			const aiVertexWeight& vw = aiBone->mWeights[i];
			int global_vertex_id = mesh_base_vertex[index] + aiBone->mWeights[i].mVertexId;

			assert(global_vertex_id < vertex_to_bones.size());
			vertex_to_bones[global_vertex_id].AddBoneData(bone_id, vw.mWeight);
		}
	}

	void parse_mesh_bones(aiMesh* aiMesh)
	{
		for (int i = 0; i < aiMesh->mNumBones; i++)
		{
			parse_single_bone(i, aiMesh->mBones[i]);
		}
	}

	//Utility functions local to this file
	ew::Mesh processAiMesh(aiMesh* aiMesh) {
		ew::MeshData meshData;
		for (size_t i = 0; i < aiMesh->mNumVertices; i++)
		{
			ew::Vertex vertex;
			vertex.pos = convertAIVec3(aiMesh->mVertices[i]);
			if (aiMesh->HasNormals()) {
				vertex.normal = convertAIVec3(aiMesh->mNormals[i]);
			}
			if (aiMesh->HasTextureCoords(0)) {
				vertex.uv = glm::vec2(convertAIVec3(aiMesh->mTextureCoords[0][i]));
			}
			meshData.vertices.push_back(vertex);
		}
		//Convert faces to indices
		for (size_t i = 0; i < aiMesh->mNumFaces; i++)
		{
			for (size_t j = 0; j < aiMesh->mFaces[i].mNumIndices; j++)
			{
				meshData.indices.push_back(aiMesh->mFaces[i].mIndices[j]);
			}
		}

		parse_mesh_bones(aiMesh);

		return ew::Mesh(meshData);
	}

}
