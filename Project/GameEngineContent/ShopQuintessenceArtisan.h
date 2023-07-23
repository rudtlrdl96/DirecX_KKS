#pragma once
#include "BaseNPC.h"

class ShopQuintessenceArtisan : public BaseNPC
{
public:
	ShopQuintessenceArtisan();
	~ShopQuintessenceArtisan();

	ShopQuintessenceArtisan(const ShopQuintessenceArtisan& _Other) = delete;
	ShopQuintessenceArtisan(ShopQuintessenceArtisan&& _Other) noexcept = delete;
	ShopQuintessenceArtisan& operator=(const ShopQuintessenceArtisan& _Other) = delete;
	ShopQuintessenceArtisan& operator=(ShopQuintessenceArtisan&& _Other) noexcept = delete;

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

