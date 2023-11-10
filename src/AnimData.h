#pragma once

#ifndef AnimData_h
#define AnimData_h

#include<glm/glm.hpp>

struct BoneInfo
{
	/*id is index in finalBoneMatrices*/
	int id;

	/*offset matrix transforms vertex from model space to bone space*/
	glm::mat4 offset;

};

#endif /* AnimData_h */