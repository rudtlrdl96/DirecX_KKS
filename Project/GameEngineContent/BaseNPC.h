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
	friend class NPCManager;
public:
	BaseNPC();
	~BaseNPC();

	BaseNPC(const BaseNPC& _Other) = delete;
	BaseNPC(BaseNPC&& _Other) noexcept = delete;
	BaseNPC& operator=(const BaseNPC& _Other) = delete;
	BaseNPC& operator=(BaseNPC&& _Other) noexcept = delete;

	virtual void PlayBehavior() {}
	virtual void ResetBehavior() {}

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static NPCMetaData LoadBin(GameEngineSerializer& _LoadSerializer);

	void ShowGUI() override;


protected:
	std::shared_ptr<ContentSpriteRenderer> MainRender = nullptr;
	ColorBuffer Buffer = ColorBuffer();

	std::map<std::string, std::map<size_t, float>> AnimFramePause;
	std::function<void()> Callback = nullptr;

	void Start() override;
	void Update(float _DeltaTime) override;

	virtual void SpriteLoad() = 0;
	void PlayAnimation(const std::string_view& _AnimationName, bool _IsForce, size_t _Frame = static_cast<size_t>(-1));

private:
	NPCMetaData Data = NPCMetaData();

	std::string CurAnimation = "";

	float AnimTimeCheck = 0.0f;
	UINT CurFrame = static_cast<UINT>(-1);


};

