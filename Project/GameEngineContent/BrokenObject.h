#pragma once
#include "BaseContentActor.h"

class BrokenData
{
public:
	std::string TextureName;

	float4 Pos = float4::Zero;
	float4 Size = float4::Zero;
	float4 Color = float4::Zero;

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	void LoadBin(GameEngineSerializer& _LoadSerializer);

	void ShowGUI();
};

class BOjectMetaData
{
public:
	std::string Name = "";
	size_t Index = static_cast<size_t>(-1);
	LevelArea Grade = LevelArea::None;

	std::vector<BrokenData> BrokenPartDatas;
	float4 Size = float4(100, 100, 0, 0);
	float4 Color = float4::Zero;

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	void LoadBin(GameEngineSerializer& _LoadSerializer);

	void ShowGUI();
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

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static BOjectMetaData LoadBin(GameEngineSerializer& _LoadSerializer);

	void ShowGUI() override;

protected:
	
private:
	BOjectMetaData Data;


};

