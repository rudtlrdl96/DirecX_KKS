#pragma once
#include "BaseContentActor.h"

class BrokenData
{
public:
	std::string TextureName;

	float4 Pos = float4::Zero;
	float4 Size = float4::Zero;
	float4 Color = float4::Zero;
};

class BOjectMetaData
{
public:
	std::string Name = "";
	size_t Index = 0;
	LevelArea Grade = LevelArea::None;

	std::vector<std::string> BrokenPartName;

	float4 Pos = float4::Zero;
	float4 Size = float4(100, 100, 0, 0);
	float4 Color = float4::Zero;
};

class BrokenObject : public BaseContentActor
{

public:
	BrokenObject();
	~BrokenObject();

	BrokenObject(const BrokenObject& _Other) = delete;
	BrokenObject(BrokenObject&& _Other) noexcept = delete;
	BrokenObject& operator=(const BrokenObject& _Other) = delete;
	BrokenObject& operator=(BrokenObject&& _Other) noexcept = delete;

protected:
	
private:


};

