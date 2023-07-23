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

	void PlayBehavior() override;
	void ResetBehavior() override;

private:
	std::shared_ptr<class ShopCollector_Reroll> RerollBox = nullptr;

	std::shared_ptr<class FieldNoteActor> NoteActor = nullptr;
	std::shared_ptr<class NPC_TalkBox> NpcTalkBox = nullptr;
	std::shared_ptr<GameEngineCollision> TalkEventCol = nullptr;

	std::vector<std::function<void()>> TalkScripts;

	std::vector<std::shared_ptr<GameEngineCollision>> ItemPlatforms;
	std::vector<std::shared_ptr<class ShopItemGear>> ItemGears;
	std::vector<std::shared_ptr<GameEngineFontRenderer>> ItemPrice;

	int TalkScriptNumber = -1;
	int BubbleScriptNumber = -1;

	float BubbleTalkTime = -13.0f;

	int RerollPrice = 40;
	int MaxRerollPrice = 270;

	void CreateTalkScript();
	void PlayNextScript();
	void TalkEndCallback();

	void RerollItem(bool _IsInitReroll);
	void ReleaseItem();

};

