#pragma once
#include "BaseNPC.h"

class ShopHeadless : public BaseNPC
{
public:
	ShopHeadless();
	~ShopHeadless();

	ShopHeadless(const ShopHeadless& _Other) = delete;
	ShopHeadless(ShopHeadless&& _Other) noexcept = delete;
	ShopHeadless& operator=(const ShopHeadless& _Other) = delete;
	ShopHeadless& operator=(ShopHeadless&& _Other) noexcept = delete;

	void CallUseEvent() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SpriteLoad() override;
	void PlayBehavior() override;
	void ResetBehavior() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> HeadRender = nullptr;
	std::shared_ptr<ContentMinimapRender> MinimapImageRender = nullptr;
	std::shared_ptr<class FieldNoteActor> NoteActor = nullptr;
	std::shared_ptr<class NPC_TalkBox> NpcTalkBox = nullptr;
	std::shared_ptr<GameEngineCollision> TalkEventCol = nullptr;

	std::vector<std::function<void()>> TalkScripts;

	std::shared_ptr<GameEngineCollision> ItemPlatform0 = nullptr;
	std::shared_ptr<GameEngineCollision> ItemPlatform1 = nullptr;
	std::shared_ptr<GameEngineCollision> ItemPlatform2 = nullptr;
	std::shared_ptr<GameEngineCollision> ItemPlatform3 = nullptr;

	std::shared_ptr<class HeadlessGear> SwitchGear = nullptr;
	 
	int TalkScriptNumber = -1;
	int BubbleScriptNumber = -1;

	float BubbleTalkTime = -13.0f;

	void CreateTalkScript();
	void PlayNextScript();
	void TalkEndCallback();

};

