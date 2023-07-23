#pragma once
#include "BaseNPC.h"

class ShopCollector : public BaseNPC
{
public:
	ShopCollector();
	~ShopCollector();

	ShopCollector(const ShopCollector& _Other) = delete;
	ShopCollector(ShopCollector&& _Other) noexcept = delete;
	ShopCollector& operator=(const ShopCollector& _Other) = delete;
	ShopCollector& operator=(ShopCollector&& _Other) noexcept = delete;

	void CallUseEvent() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SpriteLoad() override;

private:
	std::shared_ptr<class FieldNoteActor> NoteActor = nullptr;
	std::shared_ptr<class NPC_TalkBox> NpcTalkBox = nullptr;
	std::shared_ptr<GameEngineCollision> TalkEventCol = nullptr;

	std::vector<std::function<void()>> TalkScripts;

	std::shared_ptr<GameEngineCollision> ItemPlatform0 = nullptr;
	std::shared_ptr<GameEngineCollision> ItemPlatform1 = nullptr;
	std::shared_ptr<GameEngineCollision> ItemPlatform2 = nullptr;
	std::shared_ptr<GameEngineCollision> ItemPlatform3 = nullptr;

	int TalkScriptNumber = -1;
	int BubbleScriptNumber = -1;

	float BubbleTalkTime = -13.0f;

	void CreateTalkScript();
	void PlayNextScript();
	void TalkEndCallback();

};

