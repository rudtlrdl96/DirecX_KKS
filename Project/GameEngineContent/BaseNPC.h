#pragma once
#include "BaseContentActor.h"

class NPCMetaData
{
public:
	UINT Index = 0;
	LevelArea Grade = LevelArea::None;
	std::string Name = "";
	std::string TalkboxNameTag = "";
	std::string PreviewName = "";

	float4 CenterPos = float4::Zero;
};

class BaseNPC : public BaseContentActor
{
public:
	BaseNPC();
	~BaseNPC();

	BaseNPC(const BaseNPC& _Other) = delete;
	BaseNPC(BaseNPC&& _Other) noexcept = delete;
	BaseNPC& operator=(const BaseNPC& _Other) = delete;
	BaseNPC& operator=(BaseNPC&& _Other) noexcept = delete;

	virtual void ResetNPC() {}

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static NPCMetaData LoadBin(GameEngineSerializer& _LoadSerializer);

protected:
	std::shared_ptr<ContentSpriteRenderer> MainRender = nullptr;
	ColorBuffer Buffer = ColorBuffer();

	void Start() override;
	void ShowGUI() override;

	virtual void SpriteLoad() = 0;

private:
	NPCMetaData Data = NPCMetaData();
};

