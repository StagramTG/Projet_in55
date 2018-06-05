#include "Bone.h"


IN::Bone::Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat)
{
	id = in_id;
	name = in_name;
	offset_matrix = AiToGLMMat4(in_o_mat);

	mesh = in_mesh;

	parent_bone = nullptr;
	node = nullptr;
}

IN::Bone::Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat)
{
	id = in_id;
	name = in_name;
	offset_matrix = in_o_mat;

	mesh = in_mesh;

	parent_bone = nullptr;
	node = nullptr;
}

glm::mat4 IN::Bone::GetParentTransforms()
{
	Bone* b = parent_bone;
	std::vector<glm::mat4> mats;

	while (b != nullptr)
	{
		glm::mat4 tmp_mat = AiToGLMMat4(b->node->mTransformation);
		mats.push_back(tmp_mat);

		b = b->parent_bone;
	}

	glm::mat4 concatenated_transforms;

	for (int i = mats.size() - 1; i >= 0; --i)
	{
		concatenated_transforms *= mats.at(i);
	}

	return concatenated_transforms;
}

IN::Skeleton * IN::Bone::GetParentSkeleton()
{
	return parent_skeleton;
}

void IN::Bone::SetParentSkeleton(Skeleton * in_sk)
{
	parent_skeleton = in_sk;
}

std::string IN::Bone::GetName()
{
	return name;
}

void IN::Bone::SetName(std::string in_name)
{
	name = in_name;
}

aiNode* IN::Bone::GetNode()
{
	return node;
}

void IN::Bone::SetNode(aiNode * in_node)
{
	node = in_node;
}

void IN::Bone::SetAnimNode(aiNodeAnim * in_nodeAnim)
{
	animNode = in_nodeAnim;
}

void IN::Bone::SetParentBone(Bone * in_pbone)
{
	parent_bone = in_pbone;
}

unsigned int IN::Bone::FindPosition(float time)
{
	for (unsigned int i = 0; i < animNode->mNumPositionKeys - 1; ++i)
	{
		if (time < (float)animNode->mPositionKeys[i + 1].mTime)
			return i;
	}
	return 0;
}

unsigned int IN::Bone::FindRotation(float time)
{
	for (unsigned int i = 0; i < animNode->mNumRotationKeys - 1; ++i)
	{
		if (time < (float)animNode->mRotationKeys[i + 1].mTime)
			return i;
	}
	return 0;
}

glm::vec3 IN::Bone::CalcInterpolatedPosition(float time)
{
	if (animNode->mNumPositionKeys == 1)
	{
		aiVector3D assimp_val = animNode->mPositionKeys[0].mValue;
		glm::vec3 val(assimp_val.x, assimp_val.y, assimp_val.z);
		return val;
	}

	unsigned int PositionIndex = FindPosition(time);
	unsigned int NextPositionIndex = (PositionIndex + 1);

	float DeltaTime = (float)(animNode->mPositionKeys[NextPositionIndex].mTime - animNode->mPositionKeys[PositionIndex].mTime);

	float Factor = (time - (float)animNode->mPositionKeys[PositionIndex].mTime) / DeltaTime;

	const aiVector3D StartPosition = animNode->mPositionKeys[PositionIndex].mValue;
	const aiVector3D EndPosition = animNode->mPositionKeys[NextPositionIndex].mValue;

	glm::vec3 p1(StartPosition.x, StartPosition.y, StartPosition.z);
	glm::vec3 p2(EndPosition.x, EndPosition.y, EndPosition.z);

	glm::vec3 val = glm::mix(p1, p2, Factor);

	return val;
}

glm::quat IN::Bone::CalcInterpolatedRotation(float time)
{
	if (animNode->mNumRotationKeys == 1)
	{
		aiQuaternion assimp_val = animNode->mRotationKeys[0].mValue;
		glm::quat val(assimp_val.w, assimp_val.x, assimp_val.y, assimp_val.z);
		return val;
	}

	unsigned int RotationIndex = FindRotation(time);
	unsigned int NextRotationIndex = (RotationIndex + 1);

	float DeltaTime = (float)(animNode->mRotationKeys[NextRotationIndex].mTime - animNode->mRotationKeys[RotationIndex].mTime);
	float Factor = (time - (float)animNode->mRotationKeys[RotationIndex].mTime) / DeltaTime;

	const aiQuaternion& StartRotationQ = animNode->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = animNode->mRotationKeys[NextRotationIndex].mValue;

	glm::quat r1(StartRotationQ.w, StartRotationQ.x, StartRotationQ.y, StartRotationQ.z);
	glm::quat r2(EndRotationQ.w, EndRotationQ.x, EndRotationQ.y, EndRotationQ.z);

	glm::quat val = glm::slerp(r1, r2, Factor);
	return val;
}

void IN::Bone::UpdateKeyframeTransform(float time)
{
	if (animNode == nullptr)
		return;

	pos = CalcInterpolatedPosition(time);
	rot = CalcInterpolatedRotation(time);
	scale = glm::vec3(1.0);

	glm::mat4 mat;
	mat *= glm::translate(glm::mat4(1.0f),pos);
	mat *= glm::mat4_cast(rot);
	mat *= glm::scale(glm::mat4(1.0f), scale);

	node->mTransformation = GLMMat4ToAi(mat);
}