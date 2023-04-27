#pragma once
#include "BaseContentActor.h"

class SObject_DESC
{
public:
	std::string Name = "";
	size_t Index = 0;
	LevelType Grade = LevelType::None;

	float4 Pos = float4::Zero;
	float4 Size = float4(100, 100, 0, 0);
	float4 Color = float4::Null;
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

protected:
	void Start() override;

private:
	SObject_DESC Desc = SObject_DESC();

	std::shared_ptr<GameEngineSpriteRenderer> ImageRender = nullptr;

#if _DEBUG
	static std::shared_ptr<StaticObject> FocusStaticObject;
#endif

};