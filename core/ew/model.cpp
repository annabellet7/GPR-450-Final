/*
*	Author: Eric Winebrenner
*/

#include "model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <assimp/scene.h>
#include <glm/glm.hpp>




namespace ew {
	std::vector<ew::Mesh> processAiMesh(const aiScene* aiScene);

	std::vector<VertexBoneData> vertex_to_bones;
	std::vector<int> mesh_base_vertex;
	std::map<std::string, int> bone_name_to_index_map;

	Model::Model(const std::string& filePath)
	{
		Assimp::Importer importer;
		const aiScene* aiScene = importer.ReadFile(filePath, aiProcess_Triangulate);
		int totalVerts = 0;

		/*for (int i = 0; i < aiScene->mNumMeshes; i++)
		{
			aiMesh* mesh = aiScene->mMeshes[i];
			totalVerts += mesh->mNumVertices;
		}
		vertex_to_bones.resize(totalVerts);*/

		m_meshes = processAiMesh(aiScene);
		//m_meshes.push_back(processAiMesh(aiMesh, aiScene, totalVerts));
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
			int global_vertex_id = mesh_base_vertex[index] + vw.mVertexId;

			assert(global_vertex_id < vertex_to_bones.size());
			vertex_to_bones[global_vertex_id].AddBoneData(bone_id, vw.mWeight);
		}
	}

	void parse_mesh_bones(aiMesh* aiMesh, int index)
	{
		for (int i = 0; i < aiMesh->mNumBones; i++)
		{
			parse_single_bone(index, aiMesh->mBones[i]);
		}
	}

	//Utility functions local to this file
	std::vector<ew::Mesh> processAiMesh(const aiScene* aiScene) {
		ew::MeshData meshData;
		std::vector<ew::Mesh> meshes;

		mesh_base_vertex.resize(aiScene->mNumMeshes);
		int totalVerts = 0;

		for (size_t k = 0; k < aiScene->mNumMeshes; k++)
		{
			aiMesh* aiMesh = aiScene->mMeshes[k];
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

			mesh_base_vertex[k] = totalVerts;
			totalVerts += aiMesh->mNumVertices;
			vertex_to_bones.resize(totalVerts);

			if (aiMesh->HasBones())
			{
				parse_mesh_bones(aiMesh, k);
			}
			//m_meshes.push_back(processAiMesh(aiMesh, aiScene, totalVerts));

			meshes.push_back(meshData);
		}

		return meshes;
	}

}
