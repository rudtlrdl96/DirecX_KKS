#pragma once

class AttackColMetaData
{
public:
	float4 ColLocalPos;
	float4 ColLocalSize;
};

class AttackFreamMetaData
{
public:
	std::vector<AttackColMetaData> ColMetaDatas;
};

class AttackMetaData
{
public:
	std::string SpriteName = "";

	UINT Start = 0;
	UINT END = 0;

	std::vector<AttackFreamMetaData> Col;

};

