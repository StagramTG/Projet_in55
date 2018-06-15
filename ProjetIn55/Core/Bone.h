#ifndef BONE_H
#define BONE_H

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Animation.h"
#include "../Globals.h"

#include <string>
#include <vector>

#include <assimp/scene.h>

namespace IN
{
	class Mesh;
	class Skeleton;
	/*class Animation;*/

	static aiMatrix4x4 GLMMat4ToAi(glm::mat4 mat)
	{
		return aiMatrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
			mat[1][0], mat[1][1], mat[1][2], mat[1][3],
			mat[2][0], mat[2][1], mat[2][2], mat[2][3],
			mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	}

	static glm::mat4 AiToGLMMat4(aiMatrix4x4& in_mat)
	{
		glm::mat4 tmp;
		tmp[0][0] = in_mat.a1;
		tmp[1][0] = in_mat.b1;
		tmp[2][0] = in_mat.c1;
		tmp[3][0] = in_mat.d1;

		tmp[0][1] = in_mat.a2;
		tmp[1][1] = in_mat.b2;
		tmp[2][1] = in_mat.c2;
		tmp[3][1] = in_mat.d2;

		tmp[0][2] = in_mat.a3;
		tmp[1][2] = in_mat.b3;
		tmp[2][2] = in_mat.c3;
		tmp[3][2] = in_mat.d3;

		tmp[0][3] = in_mat.a4;
		tmp[1][3] = in_mat.b4;
		tmp[2][3] = in_mat.c4;
		tmp[3][3] = in_mat.d4;
		return tmp;
	}

	class Bone
	{

	private:
		std::string name;
		unsigned int id;
		Mesh* mesh;    //The mesh the bone is going to affect
		aiNode* node;  //Corresponding aiNode 
		aiNodeAnim* animNode;   //Corresponding aiNodeAnim
		Bone* parent_bone;
		glm::mat4 parent_transforms;    //Concatenation of all transforms
		Skeleton* parent_skeleton;

		//Keyframe Data
		glm::vec3 pos;
		glm::quat rot;
		glm::vec3 scale;
		glm::vec3 p1;
		glm::vec3 p2;

	public:
		
		glm::mat4 offset_matrix;

		unsigned int FindPosition(float time);
		glm::vec3 CalcInterpolatedPosition(float time);
		unsigned int FindRotation(float time);
		glm::quat CalcInterpolatedRotation(float time);

		Bone() { name = ""; id = -2; }

		Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat);
		Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat);

		void UpdateKeyframeTransform(float time);

		glm::mat4 GetParentTransforms();

		Skeleton* GetParentSkeleton();
		void SetParentSkeleton(Skeleton* in_sk);
		std::string GetName();
		void SetName(std::string in_name);
		aiNode* GetNode();
		void SetNode(aiNode * in_node);
		void SetAnimNode(aiNodeAnim * in_nodeAnim);
		void SetParentBone(Bone* in_pbone);
	};

	class Skeleton
	{

	private:
		std::vector<Bone> m_bones;
		glm::mat4 m_globalInverseTransform;

		float time;

		float start_time;
		float end_time;

		Animation* active_animation;
		Animation* idle_animation;

		bool anim_play;
		bool anim_loop;

	public:

		std::vector<glm::mat4> m_boneMats;

		Skeleton()
		{
			time = 0;
			start_time = 0;
			end_time = 0;
			active_animation = nullptr;

			anim_loop = false;
		}

		Skeleton(std::vector<Bone> in_bones, glm::mat4 in_globalInverseTransform)
		{
			Init(in_bones, in_globalInverseTransform);
		}

		void Init(std::vector<Bone> in_bones, glm::mat4 in_globalInverseTransform)
		{
			m_bones = in_bones;
			m_globalInverseTransform = in_globalInverseTransform;

			time = 0;
			start_time = 0;
			end_time = 0;
			active_animation = nullptr;
			idle_animation = nullptr;

			anim_loop = false;

			for (int i = 0; i < (signed)m_bones.size(); ++i)
			{
				m_bones.at(i).SetParentSkeleton(this);
			}
		}

		void Init(std::vector<Bone> in_bones, aiMatrix4x4 in_globalInverseTransform)
		{
			Init(in_bones, AiToGLMMat4(in_globalInverseTransform));
		}

		Bone* FindBone(std::string name)
		{
			for (int i = 0; i < (signed)m_bones.size(); ++i)
			{
				if (strcmp(m_bones.at(i).GetName().c_str(), name.c_str()) == 0)
				{
					return &m_bones.at(i);
				}
			}
			return nullptr;
		}

		void PlayAnimation(Animation& anim, bool loop, bool reset_to_start)
		{
			if (active_animation != nullptr)
			{
				if (anim.GetPriority() < active_animation->GetPriority())
				{
					active_animation = &anim;
				}
				else
					return;
			}
			else
			{
				active_animation = &anim;
			}

			start_time = active_animation->GetStartTime();
			end_time = active_animation->GetEndTime();

			anim_play = true;
			anim_loop = loop;

			if (reset_to_start)
			{
				time = active_animation->GetStartTime();
			}
		}

		void StopAnimating()
		{
			time = end_time;
			active_animation = nullptr;
			anim_play = false;
		}

		void SetIdleAnimation(Animation* in_anim)
		{
			idle_animation = in_anim;
		}

		void UpdateBoneMatsVector()
		{
			if (m_bones.size() == 0)
				return;

			m_boneMats.clear();

			for (int i = 0; i < 100; ++i)
			{
				if (i >(signed)m_bones.size() - 1)
				{
					m_boneMats.push_back(glm::mat4(1.0));
				}
				else
				{
					glm::mat4 concatenated_transformation = (m_bones.at(i).GetParentTransforms() * AiToGLMMat4(m_bones.at(i).GetNode()->mTransformation));
					m_boneMats.push_back(m_globalInverseTransform * concatenated_transformation* m_bones.at(i).offset_matrix);
				}
			}
		}

		void Update()
		{
			UpdateBoneMatsVector();

			if (!anim_play)
			{
				return;
			}
			
			time += GLOBALS::deltaTime;

			if (time < start_time)
				time = start_time;

			if (time > end_time)
			{
				if (anim_loop)
				{
					time = start_time;
				}
				else
				{
					StopAnimating();
				}
			}

			for (int i = 0; i < (signed)m_bones.size(); ++i)
			{
				m_bones.at(i).UpdateKeyframeTransform(time);
			}
		}
	};
}
#endif

