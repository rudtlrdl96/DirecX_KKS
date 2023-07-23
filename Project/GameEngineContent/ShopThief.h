#pragma once
#include "BaseNPC.h"


class ShopThief : public BaseNPC
{
public:
	ShopThief();
	~ShopThief();

	ShopThief(const ShopThief& _Other) = delete;
	ShopThief(ShopThief&& _Other) noexcept = delete;
	ShopThief& operator=(const ShopThief& _Other) = delete;
	ShopThief& operator=(ShopThief&& _Other) noexcept = delete;

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

