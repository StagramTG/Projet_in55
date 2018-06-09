#include "Model.h"

int WEIGHTS_PER_VERTEX = 4;

IN::Model::Model()
{
}

IN::Model::Model(std::string file)
{
	// Create the model from file
	create(file);
}

IN::Model::~Model()
{
	meshes.clear();
}

bool IN::Model::create(std::string file)
{
	// Load Model file with assimp
	Assimp::Importer importer;
	importer.ReadFile(file,
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	mScene = importer.GetOrphanedScene();

	recursiveNodeProcess(mScene->mRootNode);
	AnimNodeProcess();
	m_globalInverseTransform = glm::inverse(AiToGLMMat4(mScene->mRootNode->mTransformation));

	// Extract all meshes and build them
	for (size_t i = 0; i < mScene->mNumMeshes; ++i)
	{
		aiMaterial* material = mScene->mMaterials[mScene->mMeshes[i]->mMaterialIndex];

		// Create mesh and push in vector
		Mesh m = createMeshes(mScene->mMeshes[i], material);
		meshes.push_back(m);
	}

	// Extract bones
	BoneProcess(mScene);

	if (meshes.size() != 0)
	{
		mSkeleton = meshes.at(0).GetLoaderSkeleton();

		for ( int i = 1; i < (signed)meshes.size(); ++i)
		{
			meshes.at(i).SetLoaderSkeleton(meshes.at(0).GetLoaderSkeleton());
		}
	}

	// Free memory
	importer.FreeScene();
	return true;
}

void IN::Model::render(ShaderProgram* shader)
{
	UpdateSkeleton();
	for (Mesh mesh : meshes)
	{
		mesh.render(shader);
	}
}

void IN::Model::update()
{
	UpdateSkeleton();
}

IN::Mesh IN::Model::createMeshes(aiMesh* mesh, aiMaterial* material)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	// Extract data in vector of Vertex
	for (size_t i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;

		aiVector3D pos = mesh->mVertices[i];
		vertex.position = glm::vec3(pos.x, pos.y, pos.z);

		if (mesh->HasNormals())
		{
			aiVector3D nor = mesh->mNormals[i];
			vertex.normal = glm::vec3(nor.x, nor.y, nor.z);
		}

		if (mesh->HasTextureCoords(0))
		{
			aiVector3D tex = mesh->mTextureCoords[0][i];
			vertex.uv = glm::vec2(tex.x, tex.y);
		}

		// Push the vertex in vector
		vertices.push_back(vertex);
	}

	// Extract indices
	for (size_t y = 0; y < mesh->mNumFaces; ++y)
	{
		indices.push_back(mesh->mFaces[y].mIndices[0]);
		indices.push_back(mesh->mFaces[y].mIndices[1]);
		indices.push_back(mesh->mFaces[y].mIndices[2]);
	}

	// Extract textures
	size_t textureCount = material->GetTextureCount(aiTextureType_DIFFUSE);
	if (textureCount > 0)
	{
		for (size_t t = 0; t < textureCount; ++t)
		{
			Texture texture;

			aiString texturePath;
			material->GetTexture(aiTextureType_DIFFUSE, t, &texturePath);

			if (!texture.loadFromFile(texturePath.C_Str()))
			{
				// TODO: Put log in case of error
			}
			else
			{
				textures.push_back(texture);
			}
		}
	}

	// Extract Bone IDs and Weights
	int boneArraysSize = mesh->mNumVertices*WEIGHTS_PER_VERTEX;
	std::vector<int> boneIDs;
	boneIDs.resize(boneArraysSize);
	std::vector<float> boneWeights;
	boneWeights.resize(boneArraysSize);
	for (int i = 0; i < (signed)mesh->mNumBones; ++i)
	{
		aiBone* aiBone = mesh->mBones[i];
		for (int j = 0; j < (signed)aiBone->mNumWeights; ++j)
		{
			aiVertexWeight weight = aiBone->mWeights[j];
			unsigned int vertexStart = weight.mVertexId * WEIGHTS_PER_VERTEX;
			for (int k = 0; k < WEIGHTS_PER_VERTEX; k++)
			{
				if (boneWeights.at(vertexStart + k) == 0)
				{
					boneWeights.at(vertexStart + k) = weight.mWeight;
					boneIDs.at(vertexStart + k) = i;
					vertices.at(weight.mVertexId).id[k] = i;
					vertices.at(weight.mVertexId).weight[k] = weight.mWeight;
					break;
				}
			}
		}
	}


	// Create the mesh
	Mesh newMesh;
	newMesh.create(vertices, indices, textures);
	return newMesh;
}

void IN::Model::recursiveNodeProcess(aiNode* node)
{
	ai_nodes.push_back(node);

	for (int i = 0; i < (signed)node->mNumChildren; ++i)
	{
		recursiveNodeProcess(node->mChildren[i]);
	}
}

void IN::Model::AnimNodeProcess()
{
	if (mScene->mNumAnimations == 0)
		return;

	for (int i = 0; i < (signed)mScene->mAnimations[0]->mNumChannels; ++i)
	{
		ai_nodes_anim.push_back(mScene->mAnimations[0]->mChannels[i]);
	}
}

IN::Bone* IN::Model::FindBone(std::string name)
{
	for (int i = 0; i < (signed)bones.size(); ++i)
	{
		if (bones.at(i).GetName() == name)
			return &bones.at(i);
	}
	return nullptr;
}

aiNode* IN::Model::FindAiNode(std::string name)
{
	for (int i = 0; i < (signed)ai_nodes.size(); ++i)
	{
		if (ai_nodes.at(i)->mName.data == name)
			return ai_nodes.at(i);
	}
	return nullptr;
}

aiNodeAnim* IN::Model::FindAiNodeAnim(std::string name)
{
	for (int i = 0; i < (signed)ai_nodes_anim.size(); ++i)
	{
		if (ai_nodes_anim.at(i)->mNodeName.data == name)
			return ai_nodes_anim.at(i);
	}
	return nullptr;
}

int IN::Model::FindBoneIDByName(std::string name)
{
	for (int i = 0; i < (signed)bones.size(); ++i)
	{
		if (bones.at(i).GetName() == name)
			return i;
	}
	return -1;
}

void IN::Model::BoneProcess(const aiScene* scene)
{
	for (int i = 0; i < (signed)scene->mNumMeshes; ++i)
	{
		for (int j = 0; j <(signed)scene->mMeshes[i]->mNumBones; ++j)
		{
			std::string b_name = scene->mMeshes[i]->mBones[j]->mName.data;
			glm::mat4 b_mat = glm::transpose(AiToGLMMat4(scene->mMeshes[i]->mBones[j]->mOffsetMatrix));

			Bone bone(&meshes.at(i), i, b_name, b_mat);

			bone.SetNode(FindAiNode(b_name));
			bone.SetAnimNode(FindAiNodeAnim(b_name));

			bones.push_back(bone);
		}
	}

	for (int i = 0; i < (signed)bones.size(); ++i)
	{
		std::string b_name = bones.at(i).GetName();
		std::string parent_name = FindAiNode(b_name)->mParent->mName.data;

		Bone* p_bone = FindBone(parent_name);

		bones.at(i).SetParentBone(p_bone);
	}

	if (meshes.size() > 0)
	{
		meshes.at(0).GetLoaderSkeleton()->Init(bones, m_globalInverseTransform);
	}
}

void IN::Model::UpdateSkeleton()
{
	mSkeleton->Update();
}

void IN::Model::AddAnimation(Animation& in_anim)
{
	animations.push_back(in_anim);
}

IN::Animation* IN::Model::FindAnimation(std::string anim_to_find)
{
	for (int i = 0; i < (signed)animations.size(); ++i)
	{
		if (animations.at(i).GetName() == anim_to_find)
		{
			return &animations.at(i);
		}
	}
	return nullptr;
}

void IN::Model::PlayAnimation(Animation& anim, bool loop, bool reset_to_start)
{
	mSkeleton->PlayAnimation(anim, loop, reset_to_start);
}

void IN::Model::PlayAnimation(std::string name_anim)
{
	for (Animation anim : animations)
	{
		if (anim.GetName() == name_anim)
		{
			mSkeleton->PlayAnimation(anim, false, false);
			break;
		}
	}
}

void IN::Model::StopAnimating()
{
	mSkeleton->StopAnimating();
}
