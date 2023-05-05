#pragma once
#include "BaseContentActor.h"
#include "TilemapData.h"

class SObject_DESC
{
public:
	std::string Name = "";
	size_t Index = 0;
	LevelArea Grade = LevelArea::None;

	float4 Pos = float4::Zero;
	float4 Rot = float4::Zero;
	float4 Scale = float4::One;

	float4 Size = float4(100, 100, 0, 0);
	float4 Color = float4::Zero;
};

class StaticObject : public BaseContentActor
{	
public:
	StaticObject();
	~StaticObject();

	StaticObject(const StaticObject& _Other) = delete;
	StaticObject(StaticObject&& _Other) noexcept = delete;
	StaticObject& operator=(const StaticObject& _Other) = delete;
	StaticObject& operator=(StaticObject&& _Other) noexcept = delete;

	void Init(const SObject_DESC& _Desc);

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static SObject_DESC LoadBin(GameEngineSerializer& _LoadSerializer);

protected:
	void Start() override;

private:
	SObject_DESC Desc = SObject_DESC();

	std::shared_ptr<GameEngineSpriteRenderer> ImageRender = nullptr;

	ColorBuffer Buffer;

#if _DEBUG
	static std::shared_ptr<StaticObject> FocusStaticObject;
#endif

};