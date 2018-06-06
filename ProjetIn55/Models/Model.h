#pragma once

/**
 * Class Model.
 *
 * Is a Renderable (Need to render itself using OpenGL)
 *
 * Create two subclass (We really need these ? I don't think but...):
 * 	- ModelTextured
 * 	- ModelColored
 *
 * A model is composed of several Meshes.
 */

#include <GL/glew.h>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Core/Renderable.h"
#include "Mesh.h"

#include "../Core/Bone.h"

namespace IN
{
	class Model: public Renderable
	{
	private:
		std::vector<Mesh> meshes;

		const aiScene* mScene;

		std::vector<aiNode*> ai_nodes;
		std::vector<aiNodeAnim*> ai_nodes_anim;

		aiMatrix4x4 m_globalInverseTransform;

		std::vector<Bone> bones;

		bool mAnim;
		Skeleton mSkeleton;

		std::vector<Animation> animations;
		
		/**
		 * Method to create all meshes from the content of the loaded file.
		 * These Meshes compose the model.
		 */
		Mesh createMeshes(aiMesh* mesh, aiMaterial* material);

		void recursiveNodeProcess(aiNode* node);
		void AnimNodeProcess(const aiScene* scene);

	public:
		Model();
		Model(std::string file);
		~Model();

		bool create(std::string file);

		virtual void render(ShaderProgram* shader) override;

		Bone* FindBone(std::string name);

		aiNode* FindAiNode(std::string name);

		aiNodeAnim* FindAiNodeAnim(std::string name);

		int FindBoneIDByName(std::string name);

		void BoneProcess(const aiScene* scene);

		void UpdateSkeleton();

		void AddAnimation(Animation& in_anim);

		Animation* FindAnimation(std::string anim_to_find);

		void PlayAnimation(Animation& anim, bool loop = false, bool reset_to_start = false);
		void PlayAnimation(std::string name_anim);
		
		void StopAnimating();
	};
}