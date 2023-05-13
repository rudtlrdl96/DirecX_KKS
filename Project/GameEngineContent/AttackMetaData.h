#pragma once

class ColMetaData
{
public:
	UINT Frame = 0;

	float4 LocalCenter = float4::Zero;
	float4 LocalSize = float4::Zero;
};

class AnimationColMetaData
{
public:
	std::string SpriteName = "";
	std::string AnimationName = "";
	
	UINT AnimStart = 0;
	UINT AnimEnd = 0;

	std::vector<ColMetaData> BodyColDatas;
	std::vector<std::vector<ColMetaData>> AttackColDatas;
};

